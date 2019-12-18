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

/* Variables and functions */
 int NO_IRQ ; 
 int /*<<< orphan*/  SPR_PICSR ; 
 int ffs (int) ; 
 int mfspr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pic_get_irq(int first)
{
	int hwirq;

	hwirq = ffs(mfspr(SPR_PICSR) >> first);
	if (!hwirq)
		return NO_IRQ;
	else
		hwirq = hwirq + first - 1;

	return hwirq;
}