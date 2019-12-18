#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct pci_dev {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  IO_ADDR_R; scalar_t__ chip_delay; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  dev_ready; int /*<<< orphan*/  cmd_ctrl; int /*<<< orphan*/  IO_ADDR_W; } ;
struct TYPE_8__ {int /*<<< orphan*/  algo; int /*<<< orphan*/  mode; } ;
struct nand_chip {TYPE_3__ legacy; int /*<<< orphan*/  bbt_options; TYPE_2__ ecc; } ;
struct device_node {int dummy; } ;
struct TYPE_7__ {struct device* parent; } ;
struct TYPE_10__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAND_BBT_USE_FLASH ; 
 int /*<<< orphan*/  NAND_ECC_HAMMING ; 
 int /*<<< orphan*/  NAND_ECC_SOFT ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_PASEMI ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct resource*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nand_chip*) ; 
 struct nand_chip* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpcctl ; 
 scalar_t__ mtd_device_register (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_scan (struct nand_chip*,int) ; 
 TYPE_4__* nand_to_mtd (struct nand_chip*) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pasemi_device_ready ; 
 int /*<<< orphan*/  pasemi_hwcontrol ; 
 TYPE_4__* pasemi_nand_mtd ; 
 int /*<<< orphan*/  pasemi_read_buf ; 
 int /*<<< orphan*/  pasemi_write_buf ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  request_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pasemi_nand_probe(struct platform_device *ofdev)
{
	struct device *dev = &ofdev->dev;
	struct pci_dev *pdev;
	struct device_node *np = dev->of_node;
	struct resource res;
	struct nand_chip *chip;
	int err = 0;

	err = of_address_to_resource(np, 0, &res);

	if (err)
		return -EINVAL;

	/* We only support one device at the moment */
	if (pasemi_nand_mtd)
		return -ENODEV;

	dev_dbg(dev, "pasemi_nand at %pR\n", &res);

	/* Allocate memory for MTD device structure and private data */
	chip = kzalloc(sizeof(struct nand_chip), GFP_KERNEL);
	if (!chip) {
		err = -ENOMEM;
		goto out;
	}

	pasemi_nand_mtd = nand_to_mtd(chip);

	/* Link the private data with the MTD structure */
	pasemi_nand_mtd->dev.parent = dev;

	chip->legacy.IO_ADDR_R = of_iomap(np, 0);
	chip->legacy.IO_ADDR_W = chip->legacy.IO_ADDR_R;

	if (!chip->legacy.IO_ADDR_R) {
		err = -EIO;
		goto out_mtd;
	}

	pdev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa008, NULL);
	if (!pdev) {
		err = -ENODEV;
		goto out_ior;
	}

	lpcctl = pci_resource_start(pdev, 0);
	pci_dev_put(pdev);

	if (!request_region(lpcctl, 4, driver_name)) {
		err = -EBUSY;
		goto out_ior;
	}

	chip->legacy.cmd_ctrl = pasemi_hwcontrol;
	chip->legacy.dev_ready = pasemi_device_ready;
	chip->legacy.read_buf = pasemi_read_buf;
	chip->legacy.write_buf = pasemi_write_buf;
	chip->legacy.chip_delay = 0;
	chip->ecc.mode = NAND_ECC_SOFT;
	chip->ecc.algo = NAND_ECC_HAMMING;

	/* Enable the following for a flash based bad block table */
	chip->bbt_options = NAND_BBT_USE_FLASH;

	/* Scan to find existence of the device */
	err = nand_scan(chip, 1);
	if (err)
		goto out_lpc;

	if (mtd_device_register(pasemi_nand_mtd, NULL, 0)) {
		dev_err(dev, "Unable to register MTD device\n");
		err = -ENODEV;
		goto out_lpc;
	}

	dev_info(dev, "PA Semi NAND flash at %pR, control at I/O %x\n", &res,
		 lpcctl);

	return 0;

 out_lpc:
	release_region(lpcctl, 4);
 out_ior:
	iounmap(chip->legacy.IO_ADDR_R);
 out_mtd:
	kfree(chip);
 out:
	return err;
}