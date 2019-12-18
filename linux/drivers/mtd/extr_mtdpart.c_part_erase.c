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
struct mtd_part {scalar_t__ offset; TYPE_1__* parent; } ;
struct mtd_info {int dummy; } ;
struct erase_info {scalar_t__ fail_addr; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int (* _erase ) (TYPE_1__*,struct erase_info*) ;} ;

/* Variables and functions */
 scalar_t__ MTD_FAIL_ADDR_UNKNOWN ; 
 struct mtd_part* mtd_to_part (struct mtd_info*) ; 
 int stub1 (TYPE_1__*,struct erase_info*) ; 

__attribute__((used)) static int part_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	struct mtd_part *part = mtd_to_part(mtd);
	int ret;

	instr->addr += part->offset;
	ret = part->parent->_erase(part->parent, instr);
	if (instr->fail_addr != MTD_FAIL_ADDR_UNKNOWN)
		instr->fail_addr -= part->offset;
	instr->addr -= part->offset;

	return ret;
}