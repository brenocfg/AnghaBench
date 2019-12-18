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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int bytes; int size; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_info {int writesize; } ;

/* Variables and functions */
 int const BBM_SIZE ; 
 int const METADATA_SIZE ; 
 int /*<<< orphan*/  aux_write (struct nand_chip*,int /*<<< orphan*/  const**,int const,int*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static void raw_write(struct nand_chip *chip, const u8 *buf, const u8 *oob)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	const u8 *oob_orig = oob;
	const int page_size = mtd->writesize;
	const int ecc_size = chip->ecc.bytes;
	const int pkt_size = chip->ecc.size;
	int pos = 0; /* position within physical page */
	int rem = page_size; /* bytes remaining until BBM area */

	if (oob)
		oob += BBM_SIZE;

	aux_write(chip, &oob, METADATA_SIZE, &pos);

	while (rem > pkt_size) {
		aux_write(chip, &buf, pkt_size, &pos);
		aux_write(chip, &oob, ecc_size, &pos);
		rem = page_size - pos;
	}

	aux_write(chip, &buf, rem, &pos);
	aux_write(chip, &oob_orig, BBM_SIZE, &pos);
	aux_write(chip, &buf, pkt_size - rem, &pos);
	aux_write(chip, &oob, ecc_size, &pos);
}