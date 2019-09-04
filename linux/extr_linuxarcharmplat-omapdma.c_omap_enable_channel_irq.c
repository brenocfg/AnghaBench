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
struct TYPE_4__ {int /*<<< orphan*/  enabled_irqs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dma_write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* dma_read ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CICR ; 
 int /*<<< orphan*/  CSR ; 
 int /*<<< orphan*/  OMAP2_DMA_CSR_CLEAR_MASK ; 
 TYPE_2__* dma_chan ; 
 scalar_t__ dma_omap1 () ; 
 TYPE_1__* p ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void omap_enable_channel_irq(int lch)
{
	/* Clear CSR */
	if (dma_omap1())
		p->dma_read(CSR, lch);
	else
		p->dma_write(OMAP2_DMA_CSR_CLEAR_MASK, CSR, lch);

	/* Enable some nice interrupts. */
	p->dma_write(dma_chan[lch].enabled_irqs, CICR, lch);
}