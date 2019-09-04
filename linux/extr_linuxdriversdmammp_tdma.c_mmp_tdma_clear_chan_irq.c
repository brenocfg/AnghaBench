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
struct mmp_tdma_chan {scalar_t__ reg_base; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ TDISR ; 
 int TDISR_COMP ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mmp_tdma_clear_chan_irq(struct mmp_tdma_chan *tdmac)
{
	u32 reg = readl(tdmac->reg_base + TDISR);

	if (reg & TDISR_COMP) {
		/* clear irq */
		reg &= ~TDISR_COMP;
		writel(reg, tdmac->reg_base + TDISR);

		return 0;
	}
	return -EAGAIN;
}