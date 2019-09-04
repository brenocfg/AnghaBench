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
struct nand_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* erase ) (struct nand_device*,struct nand_pos const*) ;} ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ nanddev_isbad (struct nand_device*,struct nand_pos const*) ; 
 scalar_t__ nanddev_isreserved (struct nand_device*,struct nand_pos const*) ; 
 int /*<<< orphan*/  nanddev_pos_to_offs (struct nand_device*,struct nand_pos const*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct nand_device*,struct nand_pos const*) ; 

int nanddev_erase(struct nand_device *nand, const struct nand_pos *pos)
{
	if (nanddev_isbad(nand, pos) || nanddev_isreserved(nand, pos)) {
		pr_warn("attempt to erase a bad/reserved block @%llx\n",
			nanddev_pos_to_offs(nand, pos));
		return -EIO;
	}

	return nand->ops->erase(nand, pos);
}