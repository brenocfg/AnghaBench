#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ slave_id; } ;
struct sh_dmae_slave {TYPE_1__ shdma_slave; } ;
struct dma_chan {struct sh_dmae_slave* private; } ;

/* Variables and functions */

__attribute__((used)) static bool usbhsf_dma_filter(struct dma_chan *chan, void *param)
{
	struct sh_dmae_slave *slave = param;

	/*
	 * FIXME
	 *
	 * usbhs doesn't recognize id = 0 as valid DMA
	 */
	if (0 == slave->shdma_slave.slave_id)
		return false;

	chan->private = slave;

	return true;
}