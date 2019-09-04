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
struct mmp_tdma_chan {int /*<<< orphan*/  status; scalar_t__ reg_base; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_IN_PROGRESS ; 
 scalar_t__ TDCR ; 
 int TDCR_CHANEN ; 
 int readl (scalar_t__) ; 
 struct mmp_tdma_chan* to_mmp_tdma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mmp_tdma_resume_chan(struct dma_chan *chan)
{
	struct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	writel(readl(tdmac->reg_base + TDCR) | TDCR_CHANEN,
					tdmac->reg_base + TDCR);
	tdmac->status = DMA_IN_PROGRESS;

	return 0;
}