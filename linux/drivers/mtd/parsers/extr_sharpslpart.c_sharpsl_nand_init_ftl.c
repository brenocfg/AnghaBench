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
typedef  int /*<<< orphan*/  u8 ;
struct sharpsl_ftl {unsigned int logmax; unsigned int* log2phy; } ;
struct mtd_info {int erasesize; int /*<<< orphan*/  oobsize; } ;
typedef  int loff_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SHARPSL_FTL_PART_SIZE ; 
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 unsigned int* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mtd_block_isbad (struct mtd_info*,int) ; 
 unsigned int mtd_div_by_eb (int /*<<< orphan*/ ,struct mtd_info*) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,unsigned int,unsigned int) ; 
 unsigned int sharpsl_nand_get_logical_num (int /*<<< orphan*/ *) ; 
 scalar_t__ sharpsl_nand_read_oob (struct mtd_info*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sharpsl_nand_init_ftl(struct mtd_info *mtd, struct sharpsl_ftl *ftl)
{
	unsigned int block_num, log_num, phymax;
	loff_t block_adr;
	u8 *oob;
	int i, ret;

	oob = kzalloc(mtd->oobsize, GFP_KERNEL);
	if (!oob)
		return -ENOMEM;

	phymax = mtd_div_by_eb(SHARPSL_FTL_PART_SIZE, mtd);

	/* FTL reserves 5% of the blocks + 1 spare  */
	ftl->logmax = ((phymax * 95) / 100) - 1;

	ftl->log2phy = kmalloc_array(ftl->logmax, sizeof(*ftl->log2phy),
				     GFP_KERNEL);
	if (!ftl->log2phy) {
		ret = -ENOMEM;
		goto exit;
	}

	/* initialize ftl->log2phy */
	for (i = 0; i < ftl->logmax; i++)
		ftl->log2phy[i] = UINT_MAX;

	/* create physical-logical table */
	for (block_num = 0; block_num < phymax; block_num++) {
		block_adr = (loff_t)block_num * mtd->erasesize;

		if (mtd_block_isbad(mtd, block_adr))
			continue;

		if (sharpsl_nand_read_oob(mtd, block_adr, oob))
			continue;

		/* get logical block */
		log_num = sharpsl_nand_get_logical_num(oob);

		/* cut-off errors and skip the out-of-range values */
		if (log_num > 0 && log_num < ftl->logmax) {
			if (ftl->log2phy[log_num] == UINT_MAX)
				ftl->log2phy[log_num] = block_num;
		}
	}

	pr_info("Sharp SL FTL: %d blocks used (%d logical, %d reserved)\n",
		phymax, ftl->logmax, phymax - ftl->logmax);

	ret = 0;
exit:
	kfree(oob);
	return ret;
}