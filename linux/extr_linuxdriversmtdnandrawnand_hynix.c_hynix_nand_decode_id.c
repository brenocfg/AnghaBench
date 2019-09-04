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
struct nand_chip {TYPE_1__ id; } ;
struct mtd_info {int writesize; int erasesize; } ;

/* Variables and functions */
 int SZ_128K ; 
 int SZ_1M ; 
 int SZ_256K ; 
 int SZ_512K ; 
 int /*<<< orphan*/  hynix_nand_extract_ecc_requirements (struct nand_chip*,int) ; 
 int /*<<< orphan*/  hynix_nand_extract_oobsize (struct nand_chip*,int) ; 
 int /*<<< orphan*/  hynix_nand_extract_scrambling_requirements (struct nand_chip*,int) ; 
 int hynix_nand_has_valid_jedecid (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_decode_ext_id (struct nand_chip*) ; 
 scalar_t__ nand_is_slc (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static void hynix_nand_decode_id(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	bool valid_jedecid;
	u8 tmp;

	/*
	 * Exclude all SLC NANDs from this advanced detection scheme.
	 * According to the ranges defined in several datasheets, it might
	 * appear that even SLC NANDs could fall in this extended ID scheme.
	 * If that the case rework the test to let SLC NANDs go through the
	 * detection process.
	 */
	if (chip->id.len < 6 || nand_is_slc(chip)) {
		nand_decode_ext_id(chip);
		return;
	}

	/* Extract pagesize */
	mtd->writesize = 2048 << (chip->id.data[3] & 0x03);

	tmp = (chip->id.data[3] >> 4) & 0x3;
	/*
	 * When bit7 is set that means we start counting at 1MiB, otherwise
	 * we start counting at 128KiB and shift this value the content of
	 * ID[3][4:5].
	 * The only exception is when ID[3][4:5] == 3 and ID[3][7] == 0, in
	 * this case the erasesize is set to 768KiB.
	 */
	if (chip->id.data[3] & 0x80)
		mtd->erasesize = SZ_1M << tmp;
	else if (tmp == 3)
		mtd->erasesize = SZ_512K + SZ_256K;
	else
		mtd->erasesize = SZ_128K << tmp;

	/*
	 * Modern Toggle DDR NANDs have a valid JEDECID even though they are
	 * not exposing a valid JEDEC parameter table.
	 * These NANDs use a different NAND ID scheme.
	 */
	valid_jedecid = hynix_nand_has_valid_jedecid(chip);

	hynix_nand_extract_oobsize(chip, valid_jedecid);
	hynix_nand_extract_ecc_requirements(chip, valid_jedecid);
	hynix_nand_extract_scrambling_requirements(chip, valid_jedecid);
}