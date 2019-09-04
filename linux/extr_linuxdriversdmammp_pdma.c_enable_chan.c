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
struct mmp_pdma_phy {int idx; int base; TYPE_1__* vchan; } ;
struct TYPE_2__ {scalar_t__ byte_align; int /*<<< orphan*/  drcmr; } ;

/* Variables and functions */
 int DALGN ; 
 int DCSR ; 
 int DCSR_RUN ; 
 int DRCMR (int /*<<< orphan*/ ) ; 
 int DRCMR_MAPVLD ; 
 int readl (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void enable_chan(struct mmp_pdma_phy *phy)
{
	u32 reg, dalgn;

	if (!phy->vchan)
		return;

	reg = DRCMR(phy->vchan->drcmr);
	writel(DRCMR_MAPVLD | phy->idx, phy->base + reg);

	dalgn = readl(phy->base + DALGN);
	if (phy->vchan->byte_align)
		dalgn |= 1 << phy->idx;
	else
		dalgn &= ~(1 << phy->idx);
	writel(dalgn, phy->base + DALGN);

	reg = (phy->idx << 2) + DCSR;
	writel(readl(phy->base + reg) | DCSR_RUN, phy->base + reg);
}