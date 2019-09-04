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
struct TYPE_2__ {int len; int* data; } ;
struct nand_chip {int ecc_step_ds; int ecc_strength_ds; TYPE_1__ id; } ;
struct mtd_info {int oobsize; int writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  nand_decode_ext_id (struct nand_chip*) ; 
 scalar_t__ nand_is_slc (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static void toshiba_nand_decode_id(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	nand_decode_ext_id(chip);

	/*
	 * Toshiba 24nm raw SLC (i.e., not BENAND) have 32B OOB per
	 * 512B page. For Toshiba SLC, we decode the 5th/6th byte as
	 * follows:
	 * - ID byte 6, bits[2:0]: 100b -> 43nm, 101b -> 32nm,
	 *                         110b -> 24nm
	 * - ID byte 5, bit[7]:    1 -> BENAND, 0 -> raw SLC
	 */
	if (chip->id.len >= 6 && nand_is_slc(chip) &&
	    (chip->id.data[5] & 0x7) == 0x6 /* 24nm */ &&
	    !(chip->id.data[4] & 0x80) /* !BENAND */)
		mtd->oobsize = 32 * mtd->writesize >> 9;

	/*
	 * Extract ECC requirements from 6th id byte.
	 * For Toshiba SLC, ecc requrements are as follows:
	 *  - 43nm: 1 bit ECC for each 512Byte is required.
	 *  - 32nm: 4 bit ECC for each 512Byte is required.
	 *  - 24nm: 8 bit ECC for each 512Byte is required.
	 */
	if (chip->id.len >= 6 && nand_is_slc(chip)) {
		chip->ecc_step_ds = 512;
		switch (chip->id.data[5] & 0x7) {
		case 0x4:
			chip->ecc_strength_ds = 1;
			break;
		case 0x5:
			chip->ecc_strength_ds = 4;
			break;
		case 0x6:
			chip->ecc_strength_ds = 8;
			break;
		default:
			WARN(1, "Could not get ECC info");
			chip->ecc_step_ds = 0;
			break;
		}
	}
}