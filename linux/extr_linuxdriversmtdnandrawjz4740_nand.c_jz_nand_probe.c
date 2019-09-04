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
typedef  int /*<<< orphan*/  uint8_t ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_5__ {int size; int bytes; int strength; int /*<<< orphan*/  options; int /*<<< orphan*/  mode; int /*<<< orphan*/  correct; int /*<<< orphan*/  calculate; int /*<<< orphan*/  hwctl; } ;
struct nand_chip {int chip_delay; int /*<<< orphan*/  dev_ready; TYPE_3__ dummy_controller; int /*<<< orphan*/  select_chip; int /*<<< orphan*/  cmd_ctrl; TYPE_2__ ecc; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct mtd_info {char* name; TYPE_1__ dev; } ;
struct jz_nand_platform_data {size_t* banks; int /*<<< orphan*/  num_partitions; int /*<<< orphan*/ * partitions; } ;
struct jz_nand {unsigned char* banks; scalar_t__ base; int /*<<< orphan*/  mem; scalar_t__* bank_base; int /*<<< orphan*/ * bank_mem; scalar_t__ busy_gpio; struct nand_chip chip; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 size_t JZ_NAND_NUM_BANKS ; 
 scalar_t__ JZ_REG_NAND_CTRL ; 
 int /*<<< orphan*/  NAND_ECC_GENERIC_ERASED_CHECK ; 
 int /*<<< orphan*/  NAND_ECC_HW_OOB_FIRST ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct jz_nand_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned char) ; 
 scalar_t__ devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz_nand_calculate_ecc_rs ; 
 int /*<<< orphan*/  jz_nand_cmd_ctrl ; 
 int /*<<< orphan*/  jz_nand_controller_ops ; 
 int /*<<< orphan*/  jz_nand_correct_ecc_rs ; 
 scalar_t__ jz_nand_detect_bank (struct platform_device*,struct jz_nand*,unsigned char,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jz_nand_dev_ready ; 
 int /*<<< orphan*/  jz_nand_hwctl ; 
 int jz_nand_ioremap_resource (struct platform_device*,char*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  jz_nand_iounmap_resource (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  jz_nand_select_chip ; 
 int /*<<< orphan*/  kfree (struct jz_nand*) ; 
 struct jz_nand* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_cleanup (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct jz_nand*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int jz_nand_probe(struct platform_device *pdev)
{
	int ret;
	struct jz_nand *nand;
	struct nand_chip *chip;
	struct mtd_info *mtd;
	struct jz_nand_platform_data *pdata = dev_get_platdata(&pdev->dev);
	size_t chipnr, bank_idx;
	uint8_t nand_maf_id = 0, nand_dev_id = 0;

	nand = kzalloc(sizeof(*nand), GFP_KERNEL);
	if (!nand)
		return -ENOMEM;

	ret = jz_nand_ioremap_resource(pdev, "mmio", &nand->mem, &nand->base);
	if (ret)
		goto err_free;

	nand->busy_gpio = devm_gpiod_get_optional(&pdev->dev, "busy", GPIOD_IN);
	if (IS_ERR(nand->busy_gpio)) {
		ret = PTR_ERR(nand->busy_gpio);
		dev_err(&pdev->dev, "Failed to request busy gpio %d\n",
		    ret);
		goto err_iounmap_mmio;
	}

	chip		= &nand->chip;
	mtd		= nand_to_mtd(chip);
	mtd->dev.parent = &pdev->dev;
	mtd->name	= "jz4740-nand";

	chip->ecc.hwctl		= jz_nand_hwctl;
	chip->ecc.calculate	= jz_nand_calculate_ecc_rs;
	chip->ecc.correct	= jz_nand_correct_ecc_rs;
	chip->ecc.mode		= NAND_ECC_HW_OOB_FIRST;
	chip->ecc.size		= 512;
	chip->ecc.bytes		= 9;
	chip->ecc.strength	= 4;
	chip->ecc.options	= NAND_ECC_GENERIC_ERASED_CHECK;

	chip->chip_delay = 50;
	chip->cmd_ctrl = jz_nand_cmd_ctrl;
	chip->select_chip = jz_nand_select_chip;
	chip->dummy_controller.ops = &jz_nand_controller_ops;

	if (nand->busy_gpio)
		chip->dev_ready = jz_nand_dev_ready;

	platform_set_drvdata(pdev, nand);

	/* We are going to autodetect NAND chips in the banks specified in the
	 * platform data. Although nand_scan_ident() can detect multiple chips,
	 * it requires those chips to be numbered consecuitively, which is not
	 * always the case for external memory banks. And a fixed chip-to-bank
	 * mapping is not practical either, since for example Dingoo units
	 * produced at different times have NAND chips in different banks.
	 */
	chipnr = 0;
	for (bank_idx = 0; bank_idx < JZ_NAND_NUM_BANKS; bank_idx++) {
		unsigned char bank;

		/* If there is no platform data, look for NAND in bank 1,
		 * which is the most likely bank since it is the only one
		 * that can be booted from.
		 */
		bank = pdata ? pdata->banks[bank_idx] : bank_idx ^ 1;
		if (bank == 0)
			break;
		if (bank > JZ_NAND_NUM_BANKS) {
			dev_warn(&pdev->dev,
				"Skipping non-existing bank: %d\n", bank);
			continue;
		}
		/* The detection routine will directly or indirectly call
		 * jz_nand_select_chip(), so nand->banks has to contain the
		 * bank we're checking.
		 */
		nand->banks[chipnr] = bank;
		if (jz_nand_detect_bank(pdev, nand, bank, chipnr,
					&nand_maf_id, &nand_dev_id) == 0)
			chipnr++;
		else
			nand->banks[chipnr] = 0;
	}
	if (chipnr == 0) {
		dev_err(&pdev->dev, "No NAND chips found\n");
		goto err_iounmap_mmio;
	}

	ret = mtd_device_register(mtd, pdata ? pdata->partitions : NULL,
				  pdata ? pdata->num_partitions : 0);

	if (ret) {
		dev_err(&pdev->dev, "Failed to add mtd device\n");
		goto err_cleanup_nand;
	}

	dev_info(&pdev->dev, "Successfully registered JZ4740 NAND driver\n");

	return 0;

err_cleanup_nand:
	nand_cleanup(chip);
	while (chipnr--) {
		unsigned char bank = nand->banks[chipnr];
		jz_nand_iounmap_resource(nand->bank_mem[bank - 1],
					 nand->bank_base[bank - 1]);
	}
	writel(0, nand->base + JZ_REG_NAND_CTRL);
err_iounmap_mmio:
	jz_nand_iounmap_resource(nand->mem, nand->base);
err_free:
	kfree(nand);
	return ret;
}