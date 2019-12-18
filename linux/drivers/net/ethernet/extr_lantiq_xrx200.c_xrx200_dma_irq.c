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
struct xrx200_chan {int /*<<< orphan*/  napi; int /*<<< orphan*/  dma; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ltq_dma_ack_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ltq_dma_disable_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t xrx200_dma_irq(int irq, void *ptr)
{
	struct xrx200_chan *ch = ptr;

	ltq_dma_disable_irq(&ch->dma);
	ltq_dma_ack_irq(&ch->dma);

	napi_schedule(&ch->napi);

	return IRQ_HANDLED;
}