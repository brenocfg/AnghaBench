#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/ * ops; } ;
struct sunxi_nfc {int /*<<< orphan*/  chips; TYPE_2__ controller; int /*<<< orphan*/  assigned_cs; } ;
struct sunxi_nand_chip_sel {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  mode; } ;
struct nand_chip {int chip_delay; int /*<<< orphan*/  setup_data_interface; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  cmd_ctrl; int /*<<< orphan*/  select_chip; TYPE_3__ ecc; TYPE_2__* controller; } ;
struct sunxi_nand_chip {int nsels; int selected; int /*<<< orphan*/  node; struct nand_chip nand; TYPE_1__* sels; } ;
struct TYPE_8__ {struct device* parent; } ;
struct mtd_info {TYPE_4__ dev; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int cs; int rb; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAND_ECC_HW ; 
 int NFC_MAX_CS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct sunxi_nand_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release (struct mtd_info*) ; 
 int nand_scan (struct mtd_info*,int) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,struct device_node*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  of_get_property (struct device_node*,char*,int*) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int*) ; 
 int /*<<< orphan*/  sunxi_nand_controller_ops ; 
 int /*<<< orphan*/  sunxi_nfc_cmd_ctrl ; 
 int /*<<< orphan*/  sunxi_nfc_read_buf ; 
 int /*<<< orphan*/  sunxi_nfc_read_byte ; 
 int /*<<< orphan*/  sunxi_nfc_select_chip ; 
 int /*<<< orphan*/  sunxi_nfc_setup_data_interface ; 
 int /*<<< orphan*/  sunxi_nfc_write_buf ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sunxi_nand_chip_init(struct device *dev, struct sunxi_nfc *nfc,
				struct device_node *np)
{
	struct sunxi_nand_chip *chip;
	struct mtd_info *mtd;
	struct nand_chip *nand;
	int nsels;
	int ret;
	int i;
	u32 tmp;

	if (!of_get_property(np, "reg", &nsels))
		return -EINVAL;

	nsels /= sizeof(u32);
	if (!nsels) {
		dev_err(dev, "invalid reg property size\n");
		return -EINVAL;
	}

	chip = devm_kzalloc(dev,
			    sizeof(*chip) +
			    (nsels * sizeof(struct sunxi_nand_chip_sel)),
			    GFP_KERNEL);
	if (!chip) {
		dev_err(dev, "could not allocate chip\n");
		return -ENOMEM;
	}

	chip->nsels = nsels;
	chip->selected = -1;

	for (i = 0; i < nsels; i++) {
		ret = of_property_read_u32_index(np, "reg", i, &tmp);
		if (ret) {
			dev_err(dev, "could not retrieve reg property: %d\n",
				ret);
			return ret;
		}

		if (tmp > NFC_MAX_CS) {
			dev_err(dev,
				"invalid reg value: %u (max CS = 7)\n",
				tmp);
			return -EINVAL;
		}

		if (test_and_set_bit(tmp, &nfc->assigned_cs)) {
			dev_err(dev, "CS %d already assigned\n", tmp);
			return -EINVAL;
		}

		chip->sels[i].cs = tmp;

		if (!of_property_read_u32_index(np, "allwinner,rb", i, &tmp) &&
		    tmp < 2)
			chip->sels[i].rb = tmp;
		else
			chip->sels[i].rb = -1;
	}

	nand = &chip->nand;
	/* Default tR value specified in the ONFI spec (chapter 4.15.1) */
	nand->chip_delay = 200;
	nand->controller = &nfc->controller;
	nand->controller->ops = &sunxi_nand_controller_ops;

	/*
	 * Set the ECC mode to the default value in case nothing is specified
	 * in the DT.
	 */
	nand->ecc.mode = NAND_ECC_HW;
	nand_set_flash_node(nand, np);
	nand->select_chip = sunxi_nfc_select_chip;
	nand->cmd_ctrl = sunxi_nfc_cmd_ctrl;
	nand->read_buf = sunxi_nfc_read_buf;
	nand->write_buf = sunxi_nfc_write_buf;
	nand->read_byte = sunxi_nfc_read_byte;
	nand->setup_data_interface = sunxi_nfc_setup_data_interface;

	mtd = nand_to_mtd(nand);
	mtd->dev.parent = dev;

	ret = nand_scan(mtd, nsels);
	if (ret)
		return ret;

	ret = mtd_device_register(mtd, NULL, 0);
	if (ret) {
		dev_err(dev, "failed to register mtd device: %d\n", ret);
		nand_release(mtd);
		return ret;
	}

	list_add_tail(&chip->node, &nfc->chips);

	return 0;
}