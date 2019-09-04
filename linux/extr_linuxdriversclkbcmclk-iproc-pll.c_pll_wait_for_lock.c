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
typedef  int u32 ;
struct TYPE_2__ {int shift; scalar_t__ offset; } ;
struct iproc_pll_ctrl {TYPE_1__ status; } ;
struct iproc_pll {scalar_t__ status_base; struct iproc_pll_ctrl* ctrl; } ;

/* Variables and functions */
 int EIO ; 
 int LOCK_DELAY ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pll_wait_for_lock(struct iproc_pll *pll)
{
	int i;
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;

	for (i = 0; i < LOCK_DELAY; i++) {
		u32 val = readl(pll->status_base + ctrl->status.offset);

		if (val & (1 << ctrl->status.shift))
			return 0;
		udelay(10);
	}

	return -EIO;
}