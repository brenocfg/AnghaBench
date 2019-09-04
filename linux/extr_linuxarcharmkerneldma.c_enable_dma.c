#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int active; TYPE_1__* d_ops; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ dma_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* enable ) (unsigned int,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 TYPE_2__* dma_channel (unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (unsigned int,TYPE_2__*) ; 

void enable_dma (unsigned int chan)
{
	dma_t *dma = dma_channel(chan);

	if (!dma->lock)
		goto free_dma;

	if (dma->active == 0) {
		dma->active = 1;
		dma->d_ops->enable(chan, dma);
	}
	return;

free_dma:
	pr_err("dma%d: trying to enable free DMA\n", chan);
	BUG();
}