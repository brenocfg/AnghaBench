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
struct nand_pos {int dummy; } ;
struct nand_device {TYPE_2__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  badblocks; } ;
struct mtd_info {TYPE_1__ ecc_stats; } ;
struct TYPE_4__ {int (* markbad ) (struct nand_device*,struct nand_pos const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_BBT_BLOCK_WORN ; 
 int /*<<< orphan*/  nanddev_bbt_is_initialized (struct nand_device*) ; 
 unsigned int nanddev_bbt_pos_to_entry (struct nand_device*,struct nand_pos const*) ; 
 int nanddev_bbt_set_block_status (struct nand_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int nanddev_bbt_update (struct nand_device*) ; 
 scalar_t__ nanddev_isbad (struct nand_device*,struct nand_pos const*) ; 
 int /*<<< orphan*/  nanddev_pos_to_offs (struct nand_device*,struct nand_pos const*) ; 
 struct mtd_info* nanddev_to_mtd (struct nand_device*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct nand_device*,struct nand_pos const*) ; 

int nanddev_markbad(struct nand_device *nand, const struct nand_pos *pos)
{
	struct mtd_info *mtd = nanddev_to_mtd(nand);
	unsigned int entry;
	int ret = 0;

	if (nanddev_isbad(nand, pos))
		return 0;

	ret = nand->ops->markbad(nand, pos);
	if (ret)
		pr_warn("failed to write BBM to block @%llx (err = %d)\n",
			nanddev_pos_to_offs(nand, pos), ret);

	if (!nanddev_bbt_is_initialized(nand))
		goto out;

	entry = nanddev_bbt_pos_to_entry(nand, pos);
	ret = nanddev_bbt_set_block_status(nand, entry, NAND_BBT_BLOCK_WORN);
	if (ret)
		goto out;

	ret = nanddev_bbt_update(nand);

out:
	if (!ret)
		mtd->ecc_stats.badblocks++;

	return ret;
}