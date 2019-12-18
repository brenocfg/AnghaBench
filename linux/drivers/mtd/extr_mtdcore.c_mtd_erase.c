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
struct mtd_info {int (* _erase ) (struct mtd_info*,struct erase_info*) ;scalar_t__ size; int flags; int /*<<< orphan*/  erasesize; } ;
struct erase_info {scalar_t__ addr; scalar_t__ len; int /*<<< orphan*/  fail_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int EROFS ; 
 int /*<<< orphan*/  MTD_FAIL_ADDR_UNKNOWN ; 
 int MTD_WRITEABLE ; 
 int /*<<< orphan*/  ledtrig_mtd_activity () ; 
 int stub1 (struct mtd_info*,struct erase_info*) ; 

int mtd_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	instr->fail_addr = MTD_FAIL_ADDR_UNKNOWN;

	if (!mtd->erasesize || !mtd->_erase)
		return -ENOTSUPP;

	if (instr->addr >= mtd->size || instr->len > mtd->size - instr->addr)
		return -EINVAL;
	if (!(mtd->flags & MTD_WRITEABLE))
		return -EROFS;

	if (!instr->len)
		return 0;

	ledtrig_mtd_activity();
	return mtd->_erase(mtd, instr);
}