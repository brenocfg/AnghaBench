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
struct spinand_device {int /*<<< orphan*/  lock; } ;
struct nand_pos {int dummy; } ;
struct nand_device {int dummy; } ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 struct nand_device* mtd_to_nanddev (struct mtd_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct spinand_device* nand_to_spinand (struct nand_device*) ; 
 int nanddev_markbad (struct nand_device*,struct nand_pos*) ; 
 int /*<<< orphan*/  nanddev_offs_to_pos (struct nand_device*,int /*<<< orphan*/ ,struct nand_pos*) ; 

__attribute__((used)) static int spinand_mtd_block_markbad(struct mtd_info *mtd, loff_t offs)
{
	struct nand_device *nand = mtd_to_nanddev(mtd);
	struct spinand_device *spinand = nand_to_spinand(nand);
	struct nand_pos pos;
	int ret;

	nanddev_offs_to_pos(nand, offs, &pos);
	mutex_lock(&spinand->lock);
	ret = nanddev_markbad(nand, &pos);
	mutex_unlock(&spinand->lock);

	return ret;
}