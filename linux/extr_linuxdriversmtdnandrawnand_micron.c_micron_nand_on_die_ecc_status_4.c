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
struct TYPE_5__ {unsigned int steps; unsigned int size; int bytes; unsigned int strength; } ;
struct nand_chip {int* oob_poi; TYPE_2__ ecc; } ;
struct TYPE_6__ {unsigned int corrected; int /*<<< orphan*/  failed; } ;
struct mtd_info {int oobsize; int writesize; TYPE_3__ ecc_stats; } ;
struct TYPE_4__ {int* rawbuf; } ;
struct micron_nand {TYPE_1__ ecc; } ;

/* Variables and functions */
 int EINVAL ; 
 int NAND_ECC_STATUS_WRITE_RECOMMENDED ; 
 int NAND_STATUS_FAIL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ hweight8 (int) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  micron_nand_on_die_ecc_setup (struct nand_chip*,int) ; 
 struct micron_nand* nand_get_manufacturer_data (struct nand_chip*) ; 
 int nand_read_data_op (struct nand_chip*,int*,int,int) ; 
 int nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int*,int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int micron_nand_on_die_ecc_status_4(struct nand_chip *chip, u8 status,
					   void *buf, int page,
					   int oob_required)
{
	struct micron_nand *micron = nand_get_manufacturer_data(chip);
	struct mtd_info *mtd = nand_to_mtd(chip);
	unsigned int step, max_bitflips = 0;
	int ret;

	if (!(status & NAND_ECC_STATUS_WRITE_RECOMMENDED)) {
		if (status & NAND_STATUS_FAIL)
			mtd->ecc_stats.failed++;

		return 0;
	}

	/*
	 * The internal ECC doesn't tell us the number of bitflips that have
	 * been corrected, but tells us if it recommends to rewrite the block.
	 * If it's the case, we need to read the page in raw mode and compare
	 * its content to the corrected version to extract the actual number of
	 * bitflips.
	 * But before we do that, we must make sure we have all OOB bytes read
	 * in non-raw mode, even if the user did not request those bytes.
	 */
	if (!oob_required) {
		ret = nand_read_data_op(chip, chip->oob_poi, mtd->oobsize,
					false);
		if (ret)
			return ret;
	}

	micron_nand_on_die_ecc_setup(chip, false);

	ret = nand_read_page_op(chip, page, 0, micron->ecc.rawbuf,
				mtd->writesize + mtd->oobsize);
	if (ret)
		return ret;

	for (step = 0; step < chip->ecc.steps; step++) {
		unsigned int offs, i, nbitflips = 0;
		u8 *rawbuf, *corrbuf;

		offs = step * chip->ecc.size;
		rawbuf = micron->ecc.rawbuf + offs;
		corrbuf = buf + offs;

		for (i = 0; i < chip->ecc.size; i++)
			nbitflips += hweight8(corrbuf[i] ^ rawbuf[i]);

		offs = (step * 16) + 4;
		rawbuf = micron->ecc.rawbuf + mtd->writesize + offs;
		corrbuf = chip->oob_poi + offs;

		for (i = 0; i < chip->ecc.bytes + 4; i++)
			nbitflips += hweight8(corrbuf[i] ^ rawbuf[i]);

		if (WARN_ON(nbitflips > chip->ecc.strength))
			return -EINVAL;

		max_bitflips = max(nbitflips, max_bitflips);
		mtd->ecc_stats.corrected += nbitflips;
	}

	return max_bitflips;
}