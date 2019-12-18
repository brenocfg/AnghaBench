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
struct nand_pos {int dummy; } ;
struct TYPE_2__ {scalar_t__ max_bad_eraseblocks_per_lun; } ;
struct nand_device {TYPE_1__ memorg; } ;
struct mtd_info {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int ENOTSUPP ; 
 struct nand_device* mtd_to_nanddev (struct mtd_info*) ; 
 int /*<<< orphan*/  nanddev_offs_to_pos (struct nand_device*,scalar_t__,struct nand_pos*) ; 
 scalar_t__ nanddev_pos_cmp (struct nand_pos*,struct nand_pos*) ; 
 int /*<<< orphan*/  nanddev_pos_next_lun (struct nand_device*,struct nand_pos*) ; 

int nanddev_mtd_max_bad_blocks(struct mtd_info *mtd, loff_t offs, size_t len)
{
	struct nand_device *nand = mtd_to_nanddev(mtd);
	struct nand_pos pos, end;
	unsigned int max_bb = 0;

	if (!nand->memorg.max_bad_eraseblocks_per_lun)
		return -ENOTSUPP;

	nanddev_offs_to_pos(nand, offs, &pos);
	nanddev_offs_to_pos(nand, offs + len, &end);

	for (nanddev_offs_to_pos(nand, offs, &pos);
	     nanddev_pos_cmp(&pos, &end) < 0;
	     nanddev_pos_next_lun(nand, &pos))
		max_bb += nand->memorg.max_bad_eraseblocks_per_lun;

	return max_bb;
}