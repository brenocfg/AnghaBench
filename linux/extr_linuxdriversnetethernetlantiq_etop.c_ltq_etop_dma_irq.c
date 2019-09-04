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
struct ltq_etop_priv {TYPE_1__* ch; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int LTQ_DMA_CH0_INT ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
ltq_etop_dma_irq(int irq, void *_priv)
{
	struct ltq_etop_priv *priv = _priv;
	int ch = irq - LTQ_DMA_CH0_INT;

	napi_schedule(&priv->ch[ch].napi);
	return IRQ_HANDLED;
}