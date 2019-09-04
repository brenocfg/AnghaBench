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
struct TYPE_4__ {int next_lch; int next_linked_ch; } ;
struct TYPE_3__ {int (* dma_read ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* dma_write ) (int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLNK_CTRL ; 
 TYPE_2__* dma_chan ; 
 scalar_t__ dma_omap1 () ; 
 scalar_t__ dma_omap2plus () ; 
 TYPE_1__* p ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void enable_lnk(int lch)
{
	u32 l;

	l = p->dma_read(CLNK_CTRL, lch);

	if (dma_omap1())
		l &= ~(1 << 14);

	/* Set the ENABLE_LNK bits */
	if (dma_chan[lch].next_lch != -1)
		l = dma_chan[lch].next_lch | (1 << 15);

#ifndef CONFIG_ARCH_OMAP1
	if (dma_omap2plus())
		if (dma_chan[lch].next_linked_ch != -1)
			l = dma_chan[lch].next_linked_ch | (1 << 15);
#endif

	p->dma_write(l, CLNK_CTRL, lch);
}