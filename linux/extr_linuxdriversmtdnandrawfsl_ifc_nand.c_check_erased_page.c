#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int bytes; int size; int steps; int /*<<< orphan*/  strength; } ;
struct nand_chip {TYPE_1__ ecc; int /*<<< orphan*/ * oob_poi; } ;
struct mtd_oob_region {int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {int corrected; int /*<<< orphan*/  failed; } ;
struct mtd_info {TYPE_2__ ecc_stats; } ;

/* Variables and functions */
 int max (int,int) ; 
 int /*<<< orphan*/  mtd_ooblayout_ecc (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_region*) ; 
 int nand_check_erased_ecc_chunk (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int check_erased_page(struct nand_chip *chip, u8 *buf)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	u8 *ecc = chip->oob_poi;
	const int ecc_size = chip->ecc.bytes;
	const int pkt_size = chip->ecc.size;
	int i, res, bitflips = 0;
	struct mtd_oob_region oobregion = { };

	mtd_ooblayout_ecc(mtd, 0, &oobregion);
	ecc += oobregion.offset;

	for (i = 0; i < chip->ecc.steps; ++i) {
		res = nand_check_erased_ecc_chunk(buf, pkt_size, ecc, ecc_size,
						  NULL, 0,
						  chip->ecc.strength);
		if (res < 0)
			mtd->ecc_stats.failed++;
		else
			mtd->ecc_stats.corrected += res;

		bitflips = max(res, bitflips);
		buf += pkt_size;
		ecc += ecc_size;
	}

	return bitflips;
}