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
struct dma_channel {int /*<<< orphan*/  flags; int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 scalar_t__ CHCR ; 
 unsigned long CHCR_IE ; 
 int /*<<< orphan*/  DMA_CONFIGURED ; 
 int /*<<< orphan*/  DMA_TEI_CAPABLE ; 
 unsigned long RS_DUAL ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 
 scalar_t__ dma_base_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sh_dmac_configure_channel(struct dma_channel *chan, unsigned long chcr)
{
	if (!chcr)
		chcr = RS_DUAL | CHCR_IE;

	if (chcr & CHCR_IE) {
		chcr &= ~CHCR_IE;
		chan->flags |= DMA_TEI_CAPABLE;
	} else {
		chan->flags &= ~DMA_TEI_CAPABLE;
	}

	__raw_writel(chcr, (dma_base_addr(chan->chan) + CHCR));

	chan->flags |= DMA_CONFIGURED;
	return 0;
}