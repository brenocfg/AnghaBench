#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  dma_chan_link_map ;
struct TYPE_4__ {int next_lch; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int (* dma_read ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* dma_write ) (int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CCR ; 
 int /*<<< orphan*/  CDAC ; 
 int /*<<< orphan*/  CLNK_CTRL ; 
 int /*<<< orphan*/  CPC ; 
 int /*<<< orphan*/  DMA_ERRATA_IFRAME_BUFFERING ; 
 int /*<<< orphan*/  DMA_ERRATA_PARALLEL_CHANNELS ; 
 scalar_t__ IS_DMA_ERRATA (int /*<<< orphan*/ ) ; 
 int MAX_LOGICAL_DMA_CH_COUNT ; 
 int /*<<< orphan*/  OMAP_DMA_ACTIVE ; 
 int OMAP_DMA_CCR_BUFFERING_DISABLE ; 
 int OMAP_DMA_CCR_EN ; 
 TYPE_2__* dma_chan ; 
 scalar_t__ dma_omap15xx () ; 
 int /*<<< orphan*/  enable_lnk (int) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap_dma_in_1510_mode () ; 
 int /*<<< orphan*/  omap_enable_channel_irq (int) ; 
 TYPE_1__* p ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ,int) ; 
 int stub4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ,int) ; 

void omap_start_dma(int lch)
{
	u32 l;

	/*
	 * The CPC/CDAC register needs to be initialized to zero
	 * before starting dma transfer.
	 */
	if (dma_omap15xx())
		p->dma_write(0, CPC, lch);
	else
		p->dma_write(0, CDAC, lch);

	if (!omap_dma_in_1510_mode() && dma_chan[lch].next_lch != -1) {
		int next_lch, cur_lch;
		char dma_chan_link_map[MAX_LOGICAL_DMA_CH_COUNT];

		/* Set the link register of the first channel */
		enable_lnk(lch);

		memset(dma_chan_link_map, 0, sizeof(dma_chan_link_map));
		dma_chan_link_map[lch] = 1;

		cur_lch = dma_chan[lch].next_lch;
		do {
			next_lch = dma_chan[cur_lch].next_lch;

			/* The loop case: we've been here already */
			if (dma_chan_link_map[cur_lch])
				break;
			/* Mark the current channel */
			dma_chan_link_map[cur_lch] = 1;

			enable_lnk(cur_lch);
			omap_enable_channel_irq(cur_lch);

			cur_lch = next_lch;
		} while (next_lch != -1);
	} else if (IS_DMA_ERRATA(DMA_ERRATA_PARALLEL_CHANNELS))
		p->dma_write(lch, CLNK_CTRL, lch);

	omap_enable_channel_irq(lch);

	l = p->dma_read(CCR, lch);

	if (IS_DMA_ERRATA(DMA_ERRATA_IFRAME_BUFFERING))
			l |= OMAP_DMA_CCR_BUFFERING_DISABLE;
	l |= OMAP_DMA_CCR_EN;

	/*
	 * As dma_write() uses IO accessors which are weakly ordered, there
	 * is no guarantee that data in coherent DMA memory will be visible
	 * to the DMA device.  Add a memory barrier here to ensure that any
	 * such data is visible prior to enabling DMA.
	 */
	mb();
	p->dma_write(l, CCR, lch);

	dma_chan[lch].flags |= OMAP_DMA_ACTIVE;
}