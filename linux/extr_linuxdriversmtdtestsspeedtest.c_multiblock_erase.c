#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct erase_info {int addr; int len; } ;
typedef  int loff_t ;
struct TYPE_3__ {int erasesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct erase_info*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* mtd ; 
 int mtd_erase (TYPE_1__*,struct erase_info*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int) ; 

__attribute__((used)) static int multiblock_erase(int ebnum, int blocks)
{
	int err;
	struct erase_info ei;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	memset(&ei, 0, sizeof(struct erase_info));
	ei.addr = addr;
	ei.len  = mtd->erasesize * blocks;

	err = mtd_erase(mtd, &ei);
	if (err) {
		pr_err("error %d while erasing EB %d, blocks %d\n",
		       err, ebnum, blocks);
		return err;
	}

	return 0;
}