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
typedef  int u64 ;
struct sh_flctl {int page_size; int /*<<< orphan*/  flcmncr_base; scalar_t__ hwecc; void* erase_ADRCNT; void* rw_ADRCNT; } ;
struct TYPE_2__ {int size; int bytes; int strength; int /*<<< orphan*/  algo; int /*<<< orphan*/  mode; int /*<<< orphan*/  write_page; int /*<<< orphan*/  read_page; } ;
struct nand_chip {int options; TYPE_1__ ecc; int /*<<< orphan*/ * badblock_pattern; int /*<<< orphan*/  base; } ;
struct mtd_info {int writesize; } ;

/* Variables and functions */
 void* ADRCNT2_E ; 
 void* ADRCNT_1 ; 
 void* ADRCNT_2 ; 
 void* ADRCNT_3 ; 
 void* ADRCNT_4 ; 
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  NAND_ECC_HAMMING ; 
 int /*<<< orphan*/  NAND_ECC_HW ; 
 int /*<<< orphan*/  NAND_ECC_SOFT ; 
 int /*<<< orphan*/  SEL_16BIT ; 
 int /*<<< orphan*/  _4ECCEN ; 
 int /*<<< orphan*/  flctl_4secc_largepage ; 
 int /*<<< orphan*/  flctl_4secc_oob_largepage_ops ; 
 int /*<<< orphan*/  flctl_4secc_oob_smallpage_ops ; 
 int /*<<< orphan*/  flctl_4secc_smallpage ; 
 int /*<<< orphan*/  flctl_read_page_hwecc ; 
 int /*<<< orphan*/  flctl_write_page_hwecc ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 struct sh_flctl* mtd_to_flctl (struct mtd_info*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int nanddev_target_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flctl_chip_attach_chip(struct nand_chip *chip)
{
	u64 targetsize = nanddev_target_size(&chip->base);
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct sh_flctl *flctl = mtd_to_flctl(mtd);

	/*
	 * NAND_BUSWIDTH_16 may have been set by nand_scan_ident().
	 * Add the SEL_16BIT flag in flctl->flcmncr_base.
	 */
	if (chip->options & NAND_BUSWIDTH_16)
		flctl->flcmncr_base |= SEL_16BIT;

	if (mtd->writesize == 512) {
		flctl->page_size = 0;
		if (targetsize > (32 << 20)) {
			/* big than 32MB */
			flctl->rw_ADRCNT = ADRCNT_4;
			flctl->erase_ADRCNT = ADRCNT_3;
		} else if (targetsize > (2 << 16)) {
			/* big than 128KB */
			flctl->rw_ADRCNT = ADRCNT_3;
			flctl->erase_ADRCNT = ADRCNT_2;
		} else {
			flctl->rw_ADRCNT = ADRCNT_2;
			flctl->erase_ADRCNT = ADRCNT_1;
		}
	} else {
		flctl->page_size = 1;
		if (targetsize > (128 << 20)) {
			/* big than 128MB */
			flctl->rw_ADRCNT = ADRCNT2_E;
			flctl->erase_ADRCNT = ADRCNT_3;
		} else if (targetsize > (8 << 16)) {
			/* big than 512KB */
			flctl->rw_ADRCNT = ADRCNT_4;
			flctl->erase_ADRCNT = ADRCNT_2;
		} else {
			flctl->rw_ADRCNT = ADRCNT_3;
			flctl->erase_ADRCNT = ADRCNT_1;
		}
	}

	if (flctl->hwecc) {
		if (mtd->writesize == 512) {
			mtd_set_ooblayout(mtd, &flctl_4secc_oob_smallpage_ops);
			chip->badblock_pattern = &flctl_4secc_smallpage;
		} else {
			mtd_set_ooblayout(mtd, &flctl_4secc_oob_largepage_ops);
			chip->badblock_pattern = &flctl_4secc_largepage;
		}

		chip->ecc.size = 512;
		chip->ecc.bytes = 10;
		chip->ecc.strength = 4;
		chip->ecc.read_page = flctl_read_page_hwecc;
		chip->ecc.write_page = flctl_write_page_hwecc;
		chip->ecc.mode = NAND_ECC_HW;

		/* 4 symbols ECC enabled */
		flctl->flcmncr_base |= _4ECCEN;
	} else {
		chip->ecc.mode = NAND_ECC_SOFT;
		chip->ecc.algo = NAND_ECC_HAMMING;
	}

	return 0;
}