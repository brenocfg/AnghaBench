#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {unsigned long start; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  select_chip; void* get_features; void* set_features; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  cmdfunc; int /*<<< orphan*/  dev_ready; } ;
struct TYPE_5__ {int /*<<< orphan*/  algo; int /*<<< orphan*/  mode; } ;
struct nand_chip {TYPE_3__ legacy; TYPE_2__ ecc; int /*<<< orphan*/  bbt_options; } ;
struct TYPE_4__ {struct device* parent; } ;
struct mtd_info {char* name; int oobsize; int erasesize; int writesize; TYPE_1__ dev; } ;
struct mpc5121_nfc_prv {scalar_t__ irq; int /*<<< orphan*/  irq_waitq; struct clk* clk; int /*<<< orphan*/  regs; struct device* dev; struct nand_chip chip; } ;
struct device_node {int dummy; } ;
struct clk {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  NAND_BBT_USE_FLASH ; 
 int /*<<< orphan*/  NAND_ECC_HAMMING ; 
 int /*<<< orphan*/  NAND_ECC_SOFT ; 
 int NFC_BIG_ENDIAN ; 
 int NFC_BLS_UNLOCKED ; 
 int /*<<< orphan*/  NFC_CONFIG ; 
 int /*<<< orphan*/  NFC_CONFIG1 ; 
 int NFC_FULL_PAGE_INT ; 
 int NFC_INT_MASK ; 
 int NFC_PPB_128 ; 
 int NFC_PPB_256 ; 
 int NFC_PPB_32 ; 
 int NFC_PPB_64 ; 
 int NFC_RESET ; 
 int /*<<< orphan*/  NFC_RESET_TIMEOUT ; 
 int /*<<< orphan*/  NFC_SPAS ; 
 int /*<<< orphan*/  NFC_UNLOCKEND_BLK0 ; 
 int /*<<< orphan*/  NFC_UNLOCKSTART_BLK0 ; 
 int NFC_WPC_UNLOCK ; 
 int /*<<< orphan*/  NFC_WRPROT ; 
 scalar_t__ NO_IRQ ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  SPRN_SVR ; 
 int ads5121_chipselect_init (struct mtd_info*) ; 
 int /*<<< orphan*/  ads5121_select_chip ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct mtd_info*) ; 
 struct clk* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,unsigned long,unsigned long) ; 
 struct mpc5121_nfc_prv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mtd_info*) ; 
 int /*<<< orphan*/  devm_request_mem_region (struct device*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc5121_nfc_command ; 
 int /*<<< orphan*/  mpc5121_nfc_dev_ready ; 
 int /*<<< orphan*/  mpc5121_nfc_free (struct device*,struct mtd_info*) ; 
 int /*<<< orphan*/  mpc5121_nfc_irq ; 
 int /*<<< orphan*/  mpc5121_nfc_read_buf ; 
 int /*<<< orphan*/  mpc5121_nfc_read_byte ; 
 int mpc5121_nfc_read_hw_config (struct mtd_info*) ; 
 int /*<<< orphan*/  mpc5121_nfc_select_chip ; 
 int /*<<< orphan*/  mpc5121_nfc_write_buf ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* nand_get_set_features_notsupp ; 
 int nand_scan (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_set_controller_data (struct nand_chip*,struct mpc5121_nfc_prv*) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,struct device_node*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int nfc_read (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_set (struct mtd_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfc_write (struct mtd_info*,int /*<<< orphan*/ ,int) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 scalar_t__ of_machine_is_compatible (char*) ; 
 unsigned long resource_size (struct resource*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mpc5121_nfc_probe(struct platform_device *op)
{
	struct device_node *dn = op->dev.of_node;
	struct clk *clk;
	struct device *dev = &op->dev;
	struct mpc5121_nfc_prv *prv;
	struct resource res;
	struct mtd_info *mtd;
	struct nand_chip *chip;
	unsigned long regs_paddr, regs_size;
	const __be32 *chips_no;
	int resettime = 0;
	int retval = 0;
	int rev, len;

	/*
	 * Check SoC revision. This driver supports only NFC
	 * in MPC5121 revision 2 and MPC5123 revision 3.
	 */
	rev = (mfspr(SPRN_SVR) >> 4) & 0xF;
	if ((rev != 2) && (rev != 3)) {
		dev_err(dev, "SoC revision %u is not supported!\n", rev);
		return -ENXIO;
	}

	prv = devm_kzalloc(dev, sizeof(*prv), GFP_KERNEL);
	if (!prv)
		return -ENOMEM;

	chip = &prv->chip;
	mtd = nand_to_mtd(chip);

	mtd->dev.parent = dev;
	nand_set_controller_data(chip, prv);
	nand_set_flash_node(chip, dn);
	prv->dev = dev;

	/* Read NFC configuration from Reset Config Word */
	retval = mpc5121_nfc_read_hw_config(mtd);
	if (retval) {
		dev_err(dev, "Unable to read NFC config!\n");
		return retval;
	}

	prv->irq = irq_of_parse_and_map(dn, 0);
	if (prv->irq == NO_IRQ) {
		dev_err(dev, "Error mapping IRQ!\n");
		return -EINVAL;
	}

	retval = of_address_to_resource(dn, 0, &res);
	if (retval) {
		dev_err(dev, "Error parsing memory region!\n");
		return retval;
	}

	chips_no = of_get_property(dn, "chips", &len);
	if (!chips_no || len != sizeof(*chips_no)) {
		dev_err(dev, "Invalid/missing 'chips' property!\n");
		return -EINVAL;
	}

	regs_paddr = res.start;
	regs_size = resource_size(&res);

	if (!devm_request_mem_region(dev, regs_paddr, regs_size, DRV_NAME)) {
		dev_err(dev, "Error requesting memory region!\n");
		return -EBUSY;
	}

	prv->regs = devm_ioremap(dev, regs_paddr, regs_size);
	if (!prv->regs) {
		dev_err(dev, "Error mapping memory region!\n");
		return -ENOMEM;
	}

	mtd->name = "MPC5121 NAND";
	chip->legacy.dev_ready = mpc5121_nfc_dev_ready;
	chip->legacy.cmdfunc = mpc5121_nfc_command;
	chip->legacy.read_byte = mpc5121_nfc_read_byte;
	chip->legacy.read_buf = mpc5121_nfc_read_buf;
	chip->legacy.write_buf = mpc5121_nfc_write_buf;
	chip->legacy.select_chip = mpc5121_nfc_select_chip;
	chip->legacy.set_features = nand_get_set_features_notsupp;
	chip->legacy.get_features = nand_get_set_features_notsupp;
	chip->bbt_options = NAND_BBT_USE_FLASH;
	chip->ecc.mode = NAND_ECC_SOFT;
	chip->ecc.algo = NAND_ECC_HAMMING;

	/* Support external chip-select logic on ADS5121 board */
	if (of_machine_is_compatible("fsl,mpc5121ads")) {
		retval = ads5121_chipselect_init(mtd);
		if (retval) {
			dev_err(dev, "Chipselect init error!\n");
			return retval;
		}

		chip->legacy.select_chip = ads5121_select_chip;
	}

	/* Enable NFC clock */
	clk = devm_clk_get(dev, "ipg");
	if (IS_ERR(clk)) {
		dev_err(dev, "Unable to acquire NFC clock!\n");
		retval = PTR_ERR(clk);
		goto error;
	}
	retval = clk_prepare_enable(clk);
	if (retval) {
		dev_err(dev, "Unable to enable NFC clock!\n");
		goto error;
	}
	prv->clk = clk;

	/* Reset NAND Flash controller */
	nfc_set(mtd, NFC_CONFIG1, NFC_RESET);
	while (nfc_read(mtd, NFC_CONFIG1) & NFC_RESET) {
		if (resettime++ >= NFC_RESET_TIMEOUT) {
			dev_err(dev, "Timeout while resetting NFC!\n");
			retval = -EINVAL;
			goto error;
		}

		udelay(1);
	}

	/* Enable write to NFC memory */
	nfc_write(mtd, NFC_CONFIG, NFC_BLS_UNLOCKED);

	/* Enable write to all NAND pages */
	nfc_write(mtd, NFC_UNLOCKSTART_BLK0, 0x0000);
	nfc_write(mtd, NFC_UNLOCKEND_BLK0, 0xFFFF);
	nfc_write(mtd, NFC_WRPROT, NFC_WPC_UNLOCK);

	/*
	 * Setup NFC:
	 *	- Big Endian transfers,
	 *	- Interrupt after full page read/write.
	 */
	nfc_write(mtd, NFC_CONFIG1, NFC_BIG_ENDIAN | NFC_INT_MASK |
							NFC_FULL_PAGE_INT);

	/* Set spare area size */
	nfc_write(mtd, NFC_SPAS, mtd->oobsize >> 1);

	init_waitqueue_head(&prv->irq_waitq);
	retval = devm_request_irq(dev, prv->irq, &mpc5121_nfc_irq, 0, DRV_NAME,
									mtd);
	if (retval) {
		dev_err(dev, "Error requesting IRQ!\n");
		goto error;
	}

	/* Detect NAND chips */
	retval = nand_scan(chip, be32_to_cpup(chips_no));
	if (retval) {
		dev_err(dev, "NAND Flash not found !\n");
		goto error;
	}

	/* Set erase block size */
	switch (mtd->erasesize / mtd->writesize) {
	case 32:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_32);
		break;

	case 64:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_64);
		break;

	case 128:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_128);
		break;

	case 256:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_256);
		break;

	default:
		dev_err(dev, "Unsupported NAND flash!\n");
		retval = -ENXIO;
		goto error;
	}

	dev_set_drvdata(dev, mtd);

	/* Register device in MTD */
	retval = mtd_device_register(mtd, NULL, 0);
	if (retval) {
		dev_err(dev, "Error adding MTD device!\n");
		goto error;
	}

	return 0;
error:
	mpc5121_nfc_free(dev, mtd);
	return retval;
}