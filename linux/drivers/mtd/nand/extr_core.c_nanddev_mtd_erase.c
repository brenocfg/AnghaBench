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
struct nand_pos {int dummy; } ;
struct nand_device {int dummy; } ;
struct mtd_info {int dummy; } ;
struct erase_info {int /*<<< orphan*/  fail_addr; scalar_t__ len; scalar_t__ addr; } ;

/* Variables and functions */
 struct nand_device* mtd_to_nanddev (struct mtd_info*) ; 
 int nanddev_erase (struct nand_device*,struct nand_pos*) ; 
 int /*<<< orphan*/  nanddev_offs_to_pos (struct nand_device*,scalar_t__,struct nand_pos*) ; 
 scalar_t__ nanddev_pos_cmp (struct nand_pos*,struct nand_pos*) ; 
 int /*<<< orphan*/  nanddev_pos_next_eraseblock (struct nand_device*,struct nand_pos*) ; 
 int /*<<< orphan*/  nanddev_pos_to_offs (struct nand_device*,struct nand_pos*) ; 

int nanddev_mtd_erase(struct mtd_info *mtd, struct erase_info *einfo)
{
	struct nand_device *nand = mtd_to_nanddev(mtd);
	struct nand_pos pos, last;
	int ret;

	nanddev_offs_to_pos(nand, einfo->addr, &pos);
	nanddev_offs_to_pos(nand, einfo->addr + einfo->len - 1, &last);
	while (nanddev_pos_cmp(&pos, &last) <= 0) {
		ret = nanddev_erase(nand, &pos);
		if (ret) {
			einfo->fail_addr = nanddev_pos_to_offs(nand, &pos);

			return ret;
		}

		nanddev_pos_next_eraseblock(nand, &pos);
	}

	return 0;
}