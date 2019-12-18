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
struct mvs_info {int id; scalar_t__ regs; scalar_t__ regs_ex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvs_ioremap (struct mvs_info*,int,int) ; 

__attribute__((used)) static int mvs_94xx_ioremap(struct mvs_info *mvi)
{
	if (!mvs_ioremap(mvi, 2, -1)) {
		mvi->regs_ex = mvi->regs + 0x10200;
		mvi->regs += 0x20000;
		if (mvi->id == 1)
			mvi->regs += 0x4000;
		return 0;
	}
	return -1;
}