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
struct TYPE_4__ {int corrected; int /*<<< orphan*/  failed; } ;
struct mtd_info {TYPE_2__ ecc_stats; } ;

/* Variables and functions */
 int BBM_SIZE ; 
 int METADATA_SIZE ; 
 int max (int,int) ; 
 int nand_check_erased_ecc_chunk (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int check_erased_page(struct nand_chip *chip, u8 *buf)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	u8 *meta = chip->oob_poi + BBM_SIZE;
	u8 *ecc = chip->oob_poi + BBM_SIZE + METADATA_SIZE;
	const int ecc_size = chip->ecc.bytes;
	const int pkt_size = chip->ecc.size;
	int i, res, meta_len, bitflips = 0;

	for (i = 0; i < chip->ecc.steps; ++i) {
		meta_len = i ? 0 : METADATA_SIZE;
		res = nand_check_erased_ecc_chunk(buf, pkt_size, ecc, ecc_size,
						  meta, meta_len,
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