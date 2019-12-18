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
struct pxa3xx_nand_platform_data {int /*<<< orphan*/  ecc_strength; int /*<<< orphan*/  ecc_step_size; scalar_t__ flash_bbt; } ;
struct TYPE_6__ {scalar_t__ mode; int /*<<< orphan*/  strength; int /*<<< orphan*/  size; } ;
struct nand_chip {int bbt_options; int options; TYPE_3__ ecc; int /*<<< orphan*/ * bbt_md; int /*<<< orphan*/ * bbt_td; int /*<<< orphan*/  controller; } ;
struct mtd_info {int writesize; char* name; } ;
struct marvell_nfc {int /*<<< orphan*/  dev; TYPE_1__* caps; } ;
struct marvell_nand_chip {int ndcr; int addr_cyc; TYPE_2__* sels; } ;
struct TYPE_5__ {int /*<<< orphan*/  cs; } ;
struct TYPE_4__ {scalar_t__ legacy_of_bindings; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NAND_BBT_NO_OOB_BBM ; 
 int NAND_BBT_USE_FLASH ; 
 int NAND_BUSWIDTH_16 ; 
 scalar_t__ NAND_ECC_HW ; 
 int NAND_NO_SUBPAGE_WRITE ; 
 int NAND_ROW_ADDR_3 ; 
 int NDCR_DWIDTH_C ; 
 int NDCR_DWIDTH_M ; 
 int NDCR_PAGE_SZ (int) ; 
 int NDCR_RA_START ; 
 int /*<<< orphan*/  bbt_main_descr ; 
 int /*<<< orphan*/  bbt_mirror_descr ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct pxa3xx_nand_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 char* devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int marvell_nand_ecc_init (struct mtd_info*,TYPE_3__*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct marvell_nand_chip* to_marvell_nand (struct nand_chip*) ; 
 struct marvell_nfc* to_marvell_nfc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_nand_attach_chip(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct marvell_nand_chip *marvell_nand = to_marvell_nand(chip);
	struct marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	struct pxa3xx_nand_platform_data *pdata = dev_get_platdata(nfc->dev);
	int ret;

	if (pdata && pdata->flash_bbt)
		chip->bbt_options |= NAND_BBT_USE_FLASH;

	if (chip->bbt_options & NAND_BBT_USE_FLASH) {
		/*
		 * We'll use a bad block table stored in-flash and don't
		 * allow writing the bad block marker to the flash.
		 */
		chip->bbt_options |= NAND_BBT_NO_OOB_BBM;
		chip->bbt_td = &bbt_main_descr;
		chip->bbt_md = &bbt_mirror_descr;
	}

	/* Save the chip-specific fields of NDCR */
	marvell_nand->ndcr = NDCR_PAGE_SZ(mtd->writesize);
	if (chip->options & NAND_BUSWIDTH_16)
		marvell_nand->ndcr |= NDCR_DWIDTH_M | NDCR_DWIDTH_C;

	/*
	 * On small page NANDs, only one cycle is needed to pass the
	 * column address.
	 */
	if (mtd->writesize <= 512) {
		marvell_nand->addr_cyc = 1;
	} else {
		marvell_nand->addr_cyc = 2;
		marvell_nand->ndcr |= NDCR_RA_START;
	}

	/*
	 * Now add the number of cycles needed to pass the row
	 * address.
	 *
	 * Addressing a chip using CS 2 or 3 should also need the third row
	 * cycle but due to inconsistance in the documentation and lack of
	 * hardware to test this situation, this case is not supported.
	 */
	if (chip->options & NAND_ROW_ADDR_3)
		marvell_nand->addr_cyc += 3;
	else
		marvell_nand->addr_cyc += 2;

	if (pdata) {
		chip->ecc.size = pdata->ecc_step_size;
		chip->ecc.strength = pdata->ecc_strength;
	}

	ret = marvell_nand_ecc_init(mtd, &chip->ecc);
	if (ret) {
		dev_err(nfc->dev, "ECC init failed: %d\n", ret);
		return ret;
	}

	if (chip->ecc.mode == NAND_ECC_HW) {
		/*
		 * Subpage write not available with hardware ECC, prohibit also
		 * subpage read as in userspace subpage access would still be
		 * allowed and subpage write, if used, would lead to numerous
		 * uncorrectable ECC errors.
		 */
		chip->options |= NAND_NO_SUBPAGE_WRITE;
	}

	if (pdata || nfc->caps->legacy_of_bindings) {
		/*
		 * We keep the MTD name unchanged to avoid breaking platforms
		 * where the MTD cmdline parser is used and the bootloader
		 * has not been updated to use the new naming scheme.
		 */
		mtd->name = "pxa3xx_nand-0";
	} else if (!mtd->name) {
		/*
		 * If the new bindings are used and the bootloader has not been
		 * updated to pass a new mtdparts parameter on the cmdline, you
		 * should define the following property in your NAND node, ie:
		 *
		 *	label = "main-storage";
		 *
		 * This way, mtd->name will be set by the core when
		 * nand_set_flash_node() is called.
		 */
		mtd->name = devm_kasprintf(nfc->dev, GFP_KERNEL,
					   "%s:nand.%d", dev_name(nfc->dev),
					   marvell_nand->sels[0].cs);
		if (!mtd->name) {
			dev_err(nfc->dev, "Failed to allocate mtd->name\n");
			return -ENOMEM;
		}
	}

	return 0;
}