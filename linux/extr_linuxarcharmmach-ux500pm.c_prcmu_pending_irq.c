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
typedef  int u32 ;

/* Variables and functions */
 int PRCMU_GIC_NUMBER_REGS ; 
 scalar_t__ PRCM_ARMITMSK31TO0 ; 
 scalar_t__ PRCM_ARMITVAL31TO0 ; 
 int readl (scalar_t__) ; 

bool prcmu_pending_irq(void)
{
	u32 it, im;
	int i;

	for (i = 0; i < PRCMU_GIC_NUMBER_REGS - 1; i++) {
		it = readl(PRCM_ARMITVAL31TO0 + i * 4);
		im = readl(PRCM_ARMITMSK31TO0 + i * 4);
		if (it & im)
			return true; /* There is a pending interrupt */
	}

	return false;
}