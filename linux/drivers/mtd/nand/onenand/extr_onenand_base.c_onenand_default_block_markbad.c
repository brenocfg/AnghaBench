#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct onenand_chip {int badblockpos; struct bbm_info* bbm; } ;
struct mtd_oob_ops {int ooblen; int /*<<< orphan*/  ooboffs; int /*<<< orphan*/ * oobbuf; int /*<<< orphan*/  mode; } ;
struct mtd_info {scalar_t__ oobsize; struct onenand_chip* priv; } ;
struct bbm_info {int* bbt; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_OPS_PLACE_OOB ; 
 int onenand_block (struct onenand_chip*,int /*<<< orphan*/ ) ; 
 int onenand_write_oob_nolock (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 

__attribute__((used)) static int onenand_default_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	struct onenand_chip *this = mtd->priv;
	struct bbm_info *bbm = this->bbm;
	u_char buf[2] = {0, 0};
	struct mtd_oob_ops ops = {
		.mode = MTD_OPS_PLACE_OOB,
		.ooblen = 2,
		.oobbuf = buf,
		.ooboffs = 0,
	};
	int block;

	/* Get block number */
	block = onenand_block(this, ofs);
        if (bbm->bbt)
                bbm->bbt[block >> 2] |= 0x01 << ((block & 0x03) << 1);

        /* We write two bytes, so we don't have to mess with 16-bit access */
        ofs += mtd->oobsize + (this->badblockpos & ~0x01);
	/* FIXME : What to do when marking SLC block in partition
	 * 	   with MLC erasesize? For now, it is not advisable to
	 *	   create partitions containing both SLC and MLC regions.
	 */
	return onenand_write_oob_nolock(mtd, ofs, &ops);
}