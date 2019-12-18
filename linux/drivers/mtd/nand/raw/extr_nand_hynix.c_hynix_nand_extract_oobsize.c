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
struct nand_memory_organization {int oobsize; int pagesize; } ;
struct TYPE_2__ {int* data; } ;
struct nand_chip {TYPE_1__ id; int /*<<< orphan*/  base; } ;
struct mtd_info {int oobsize; } ;

/* Variables and functions */
 int SZ_8K ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct nand_memory_organization* nanddev_get_memorg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hynix_nand_extract_oobsize(struct nand_chip *chip,
				       bool valid_jedecid)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct nand_memory_organization *memorg;
	u8 oobsize;

	memorg = nanddev_get_memorg(&chip->base);

	oobsize = ((chip->id.data[3] >> 2) & 0x3) |
		  ((chip->id.data[3] >> 4) & 0x4);

	if (valid_jedecid) {
		switch (oobsize) {
		case 0:
			memorg->oobsize = 2048;
			break;
		case 1:
			memorg->oobsize = 1664;
			break;
		case 2:
			memorg->oobsize = 1024;
			break;
		case 3:
			memorg->oobsize = 640;
			break;
		default:
			/*
			 * We should never reach this case, but if that
			 * happens, this probably means Hynix decided to use
			 * a different extended ID format, and we should find
			 * a way to support it.
			 */
			WARN(1, "Invalid OOB size");
			break;
		}
	} else {
		switch (oobsize) {
		case 0:
			memorg->oobsize = 128;
			break;
		case 1:
			memorg->oobsize = 224;
			break;
		case 2:
			memorg->oobsize = 448;
			break;
		case 3:
			memorg->oobsize = 64;
			break;
		case 4:
			memorg->oobsize = 32;
			break;
		case 5:
			memorg->oobsize = 16;
			break;
		case 6:
			memorg->oobsize = 640;
			break;
		default:
			/*
			 * We should never reach this case, but if that
			 * happens, this probably means Hynix decided to use
			 * a different extended ID format, and we should find
			 * a way to support it.
			 */
			WARN(1, "Invalid OOB size");
			break;
		}

		/*
		 * The datasheet of H27UCG8T2BTR mentions that the "Redundant
		 * Area Size" is encoded "per 8KB" (page size). This chip uses
		 * a page size of 16KiB. The datasheet mentions an OOB size of
		 * 1.280 bytes, but the OOB size encoded in the ID bytes (using
		 * the existing logic above) is 640 bytes.
		 * Update the OOB size for this chip by taking the value
		 * determined above and scaling it to the actual page size (so
		 * the actual OOB size for this chip is: 640 * 16k / 8k).
		 */
		if (chip->id.data[1] == 0xde)
			memorg->oobsize *= memorg->pagesize / SZ_8K;
	}

	mtd->oobsize = memorg->oobsize;
}