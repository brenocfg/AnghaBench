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
struct nand_memory_organization {int pagesize; int pages_per_eraseblock; } ;
struct TYPE_2__ {int* data; } ;
struct nand_chip {TYPE_1__ id; int /*<<< orphan*/  base; } ;
struct mtd_info {int erasesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  nand_decode_ext_id (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct nand_memory_organization* nanddev_get_memorg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amd_nand_decode_id(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct nand_memory_organization *memorg;

	memorg = nanddev_get_memorg(&chip->base);

	nand_decode_ext_id(chip);

	/*
	 * Check for Spansion/AMD ID + repeating 5th, 6th byte since
	 * some Spansion chips have erasesize that conflicts with size
	 * listed in nand_ids table.
	 * Data sheet (5 byte ID): Spansion S30ML-P ORNAND (p.39)
	 */
	if (chip->id.data[4] != 0x00 && chip->id.data[5] == 0x00 &&
	    chip->id.data[6] == 0x00 && chip->id.data[7] == 0x00 &&
	    memorg->pagesize == 512) {
		memorg->pages_per_eraseblock = 256;
		memorg->pages_per_eraseblock <<= ((chip->id.data[3] & 0x03) << 1);
		mtd->erasesize = memorg->pages_per_eraseblock *
				 memorg->pagesize;
	}
}