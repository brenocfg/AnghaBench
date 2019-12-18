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
typedef  int u8 ;
struct nand_memory_organization {int pagesize; int oobsize; int pages_per_eraseblock; } ;
struct TYPE_5__ {int len; int* data; } ;
struct TYPE_4__ {int step_size; int strength; } ;
struct TYPE_6__ {TYPE_1__ eccreq; } ;
struct nand_chip {int /*<<< orphan*/  options; TYPE_2__ id; TYPE_3__ base; } ;
struct mtd_info {int writesize; int oobsize; int erasesize; } ;

/* Variables and functions */
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAND_NO_SUBPAGE_WRITE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  nand_decode_ext_id (struct nand_chip*) ; 
 scalar_t__ nand_is_slc (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct nand_memory_organization* nanddev_get_memorg (TYPE_3__*) ; 

__attribute__((used)) static void samsung_nand_decode_id(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct nand_memory_organization *memorg;

	memorg = nanddev_get_memorg(&chip->base);

	/* New Samsung (6 byte ID): Samsung K9GAG08U0F (p.44) */
	if (chip->id.len == 6 && !nand_is_slc(chip) &&
	    chip->id.data[5] != 0x00) {
		u8 extid = chip->id.data[3];

		/* Get pagesize */
		memorg->pagesize = 2048 << (extid & 0x03);
		mtd->writesize = memorg->pagesize;

		extid >>= 2;

		/* Get oobsize */
		switch (((extid >> 2) & 0x4) | (extid & 0x3)) {
		case 1:
			memorg->oobsize = 128;
			break;
		case 2:
			memorg->oobsize = 218;
			break;
		case 3:
			memorg->oobsize = 400;
			break;
		case 4:
			memorg->oobsize = 436;
			break;
		case 5:
			memorg->oobsize = 512;
			break;
		case 6:
			memorg->oobsize = 640;
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

		mtd->oobsize = memorg->oobsize;

		/* Get blocksize */
		extid >>= 2;
		memorg->pages_per_eraseblock = (128 * 1024) <<
					       (((extid >> 1) & 0x04) |
						(extid & 0x03)) /
					       memorg->pagesize;
		mtd->erasesize = (128 * 1024) <<
				 (((extid >> 1) & 0x04) | (extid & 0x03));

		/* Extract ECC requirements from 5th id byte*/
		extid = (chip->id.data[4] >> 4) & 0x07;
		if (extid < 5) {
			chip->base.eccreq.step_size = 512;
			chip->base.eccreq.strength = 1 << extid;
		} else {
			chip->base.eccreq.step_size = 1024;
			switch (extid) {
			case 5:
				chip->base.eccreq.strength = 24;
				break;
			case 6:
				chip->base.eccreq.strength = 40;
				break;
			case 7:
				chip->base.eccreq.strength = 60;
				break;
			default:
				WARN(1, "Could not decode ECC info");
				chip->base.eccreq.step_size = 0;
			}
		}
	} else {
		nand_decode_ext_id(chip);

		if (nand_is_slc(chip)) {
			switch (chip->id.data[1]) {
			/* K9F4G08U0D-S[I|C]B0(T00) */
			case 0xDC:
				chip->base.eccreq.step_size = 512;
				chip->base.eccreq.strength = 1;
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