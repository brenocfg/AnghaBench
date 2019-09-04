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
struct TYPE_4__ {int /*<<< orphan*/  dma_gcr; int /*<<< orphan*/  dma_ocp_sysconfig; int /*<<< orphan*/  dma_irqenable_l1; int /*<<< orphan*/  dma_irqenable_l0; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dma_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GCR ; 
 int /*<<< orphan*/  IRQENABLE_L0 ; 
 int /*<<< orphan*/  IRQENABLE_L1 ; 
 int /*<<< orphan*/  OCP_SYSCONFIG ; 
 TYPE_2__ omap_dma_global_context ; 
 TYPE_1__* p ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap_dma_global_context_save(void)
{
	omap_dma_global_context.dma_irqenable_l0 =
		p->dma_read(IRQENABLE_L0, 0);
	omap_dma_global_context.dma_irqenable_l1 =
		p->dma_read(IRQENABLE_L1, 0);
	omap_dma_global_context.dma_ocp_sysconfig =
		p->dma_read(OCP_SYSCONFIG, 0);
	omap_dma_global_context.dma_gcr = p->dma_read(GCR, 0);
}