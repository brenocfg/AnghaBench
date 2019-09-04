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
struct mtd_part {TYPE_2__* parent; scalar_t__ offset; } ;
struct TYPE_3__ {int /*<<< orphan*/  badblocks; } ;
struct mtd_info {TYPE_1__ ecc_stats; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {int (* _block_markbad ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct mtd_part* mtd_to_part (struct mtd_info*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int part_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	struct mtd_part *part = mtd_to_part(mtd);
	int res;

	ofs += part->offset;
	res = part->parent->_block_markbad(part->parent, ofs);
	if (!res)
		mtd->ecc_stats.badblocks++;
	return res;
}