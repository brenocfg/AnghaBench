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
struct mic_dma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  mic_dma_ack_interrupt (struct mic_dma_chan*) ; 

__attribute__((used)) static irqreturn_t mic_dma_intr_handler(int irq, void *data)
{
	struct mic_dma_chan *ch = ((struct mic_dma_chan *)data);

	mic_dma_ack_interrupt(ch);
	return IRQ_WAKE_THREAD;
}