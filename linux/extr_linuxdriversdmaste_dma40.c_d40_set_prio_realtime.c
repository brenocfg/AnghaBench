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
struct TYPE_4__ {scalar_t__ dir; int /*<<< orphan*/  dev_type; } ;
struct d40_chan {TYPE_2__ dma_cfg; TYPE_1__* base; } ;
struct TYPE_3__ {int rev; } ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_DEV ; 
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  __d40_set_prio_rt (struct d40_chan*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void d40_set_prio_realtime(struct d40_chan *d40c)
{
	if (d40c->base->rev < 3)
		return;

	if ((d40c->dma_cfg.dir ==  DMA_DEV_TO_MEM) ||
	    (d40c->dma_cfg.dir == DMA_DEV_TO_DEV))
		__d40_set_prio_rt(d40c, d40c->dma_cfg.dev_type, true);

	if ((d40c->dma_cfg.dir ==  DMA_MEM_TO_DEV) ||
	    (d40c->dma_cfg.dir == DMA_DEV_TO_DEV))
		__d40_set_prio_rt(d40c, d40c->dma_cfg.dev_type, false);
}