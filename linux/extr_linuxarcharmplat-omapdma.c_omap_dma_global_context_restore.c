#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dev_id; } ;
struct TYPE_5__ {int dma_gcr; int dma_ocp_sysconfig; int dma_irqenable_l0; int dma_irqenable_l1; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* dma_write ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ROMCODE_BUG ; 
 int /*<<< orphan*/  GCR ; 
 int /*<<< orphan*/  IRQENABLE_L0 ; 
 int /*<<< orphan*/  IRQENABLE_L1 ; 
 int /*<<< orphan*/  IRQSTATUS_L0 ; 
 scalar_t__ IS_DMA_ERRATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCP_SYSCONFIG ; 
 TYPE_3__* dma_chan ; 
 int dma_chan_count ; 
 int /*<<< orphan*/  omap_clear_dma (int) ; 
 TYPE_2__ omap_dma_global_context ; 
 TYPE_1__* p ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap_dma_global_context_restore(void)
{
	int ch;

	p->dma_write(omap_dma_global_context.dma_gcr, GCR, 0);
	p->dma_write(omap_dma_global_context.dma_ocp_sysconfig,
		OCP_SYSCONFIG, 0);
	p->dma_write(omap_dma_global_context.dma_irqenable_l0,
		IRQENABLE_L0, 0);
	p->dma_write(omap_dma_global_context.dma_irqenable_l1,
		IRQENABLE_L1, 0);

	if (IS_DMA_ERRATA(DMA_ROMCODE_BUG))
		p->dma_write(0x3 , IRQSTATUS_L0, 0);

	for (ch = 0; ch < dma_chan_count; ch++)
		if (dma_chan[ch].dev_id != -1)
			omap_clear_dma(ch);
}