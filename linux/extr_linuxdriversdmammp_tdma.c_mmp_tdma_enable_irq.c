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
struct mmp_tdma_chan {scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ TDIMR ; 
 int /*<<< orphan*/  TDIMR_COMP ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mmp_tdma_enable_irq(struct mmp_tdma_chan *tdmac, bool enable)
{
	if (enable)
		writel(TDIMR_COMP, tdmac->reg_base + TDIMR);
	else
		writel(0, tdmac->reg_base + TDIMR);
}