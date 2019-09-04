#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int size; scalar_t__ postpad; scalar_t__ prepad; int /*<<< orphan*/  bytes; } ;
struct nand_chip {int bbt_options; int /*<<< orphan*/ * bbt_md; int /*<<< orphan*/ * bbt_td; TYPE_1__ ecc; } ;
struct mtd_info {int writesize; } ;
struct lpc32xx_nand_host {scalar_t__ data_buf; int /*<<< orphan*/ * ecc_buf; } ;

/* Variables and functions */
 scalar_t__ LPC32XX_DMA_DATA_SIZE ; 
 int /*<<< orphan*/  LPC32XX_SLC_DEV_ECC_BYTES ; 
 int NAND_BBT_USE_FLASH ; 
 int /*<<< orphan*/  bbt_smallpage_main_descr ; 
 int /*<<< orphan*/  bbt_smallpage_mirror_descr ; 
 int /*<<< orphan*/  lpc32xx_ooblayout_ops ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 struct lpc32xx_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int lpc32xx_nand_attach_chip(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct lpc32xx_nand_host *host = nand_get_controller_data(chip);

	/* OOB and ECC CPU and DMA work areas */
	host->ecc_buf = (uint32_t *)(host->data_buf + LPC32XX_DMA_DATA_SIZE);

	/*
	 * Small page FLASH has a unique OOB layout, but large and huge
	 * page FLASH use the standard layout. Small page FLASH uses a
	 * custom BBT marker layout.
	 */
	if (mtd->writesize <= 512)
		mtd_set_ooblayout(mtd, &lpc32xx_ooblayout_ops);

	/* These sizes remain the same regardless of page size */
	chip->ecc.size = 256;
	chip->ecc.bytes = LPC32XX_SLC_DEV_ECC_BYTES;
	chip->ecc.prepad = 0;
	chip->ecc.postpad = 0;

	/*
	 * Use a custom BBT marker setup for small page FLASH that
	 * won't interfere with the ECC layout. Large and huge page
	 * FLASH use the standard layout.
	 */
	if ((chip->bbt_options & NAND_BBT_USE_FLASH) &&
	    mtd->writesize <= 512) {
		chip->bbt_td = &bbt_smallpage_main_descr;
		chip->bbt_md = &bbt_smallpage_mirror_descr;
	}

	return 0;
}