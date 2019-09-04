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
typedef  int u8 ;
struct TYPE_2__ {int len; int* data; } ;
struct nand_chip {int ecc_step_ds; int ecc_strength_ds; int /*<<< orphan*/  options; TYPE_1__ id; } ;
struct mtd_info {int writesize; int oobsize; int erasesize; } ;

/* Variables and functions */
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAND_NO_SUBPAGE_WRITE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  nand_decode_ext_id (struct nand_chip*) ; 
 scalar_t__ nand_is_slc (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static void samsung_nand_decode_id(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	/* New Samsung (6 byte ID): Samsung K9GAG08U0F (p.44) */
	if (chip->id.len == 6 && !nand_is_slc(chip) &&
	    chip->id.data[5] != 0x00) {
		u8 extid = chip->id.data[3];

		/* Get pagesize */
		mtd->writesize = 2048 << (extid & 0x03);

		extid >>= 2;

		/* Get oobsize */
		switch (((extid >> 2) & 0x4) | (extid & 0x3)) {
		case 1:
			mtd->oobsize = 128;
			break;
		case 2:
			mtd->oobsize = 218;
			break;
		case 3:
			mtd->oobsize = 400;
			break;
		case 4:
			mtd->oobsize = 436;
			break;
		case 5:
			mtd->oobsize = 512;
			break;
		case 6:
			mtd->oobsize = 640;
			break;
		default:
			/*
			 * We should never reach this case, but if that
			 * happens, this probably means Samsung decided to use
			 * a different extended ID format, and we should find
			 * a way to support it.
			 */
			WARN(1, "Invalid OOB size value");
			break;
		}

		/* Get blocksize */
		extid >>= 2;
		mtd->erasesize = (128 * 1024) <<
				 (((extid >> 1) & 0x04) | (extid & 0x03));

		/* Extract ECC requirements from 5th id byte*/
		extid = (chip->id.data[4] >> 4) & 0x07;
		if (extid < 5) {
			chip->ecc_step_ds = 512;
			chip->ecc_strength_ds = 1 << extid;
		} else {
			chip->ecc_step_ds = 1024;
			switch (extid) {
			case 5:
				chip->ecc_strength_ds = 24;
				break;
			case 6:
				chip->ecc_strength_ds = 40;
				break;
			case 7:
				chip->ecc_strength_ds = 60;
				break;
			default:
				WARN(1, "Could not decode ECC info");
				chip->ecc_step_ds = 0;
			}
		}
	} else {
		nand_decode_ext_id(chip);

		if (nand_is_slc(chip)) {
			switch (chip->id.data[1]) {
			/* K9F4G08U0D-S[I|C]B0(T00) */
			case 0xDC:
				chip->ecc_step_ds = 512;
				chip->ecc_strength_ds = 1;
				break;

			/* K9F1G08U0E 21nm chips do not support subpage write */
			case 0xF1:
				if (chip->id.len > 4 &&
				    (chip->id.data[4] & GENMASK(1, 0)) == 0x1)
					chip->options |= NAND_NO_SUBPAGE_WRITE;
				break;
			default:
				break;
			}
		}
	}
}