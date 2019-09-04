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
struct dma_info {struct dma_channel* channels; } ;
struct dma_channel {int /*<<< orphan*/  wait_queue; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {TYPE_1__* status; } ;
struct TYPE_3__ {int status; } ;

/* Variables and functions */
 int G2_NR_DMA_CHANNELS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int g2_bytes_remaining (int) ; 
 TYPE_2__* g2_dma ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t g2_dma_interrupt(int irq, void *dev_id)
{
	int i;

	for (i = 0; i < G2_NR_DMA_CHANNELS; i++) {
		if (g2_dma->status[i].status & 0x20000000) {
			unsigned int bytes = g2_bytes_remaining(i);

			if (likely(bytes == 0)) {
				struct dma_info *info = dev_id;
				struct dma_channel *chan = info->channels + i;

				wake_up(&chan->wait_queue);

				return IRQ_HANDLED;
			}
		}
	}

	return IRQ_NONE;
}