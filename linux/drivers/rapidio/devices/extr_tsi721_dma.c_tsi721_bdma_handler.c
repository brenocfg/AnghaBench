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
struct tsi721_bdma_chan {int /*<<< orphan*/  tasklet; scalar_t__ active; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ TSI721_DMAC_INTE ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

void tsi721_bdma_handler(struct tsi721_bdma_chan *bdma_chan)
{
	/* Disable BDMA channel interrupts */
	iowrite32(0, bdma_chan->regs + TSI721_DMAC_INTE);
	if (bdma_chan->active)
		tasklet_hi_schedule(&bdma_chan->tasklet);
}