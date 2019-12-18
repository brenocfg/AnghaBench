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
struct xgbe_prv_data {scalar_t__ dev_irq; scalar_t__ ecc_irq; unsigned int channel_count; scalar_t__ dma_irq; int /*<<< orphan*/  dev; struct xgbe_prv_data** channel; int /*<<< orphan*/  per_channel_irq; TYPE_1__* vdata; } ;
struct xgbe_channel {scalar_t__ dev_irq; scalar_t__ ecc_irq; unsigned int channel_count; scalar_t__ dma_irq; int /*<<< orphan*/  dev; struct xgbe_channel** channel; int /*<<< orphan*/  per_channel_irq; TYPE_1__* vdata; } ;
struct TYPE_2__ {scalar_t__ ecc_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,scalar_t__,struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xgbe_free_irqs(struct xgbe_prv_data *pdata)
{
	struct xgbe_channel *channel;
	unsigned int i;

	devm_free_irq(pdata->dev, pdata->dev_irq, pdata);

	if (pdata->vdata->ecc_support && (pdata->dev_irq != pdata->ecc_irq))
		devm_free_irq(pdata->dev, pdata->ecc_irq, pdata);

	if (!pdata->per_channel_irq)
		return;

	for (i = 0; i < pdata->channel_count; i++) {
		channel = pdata->channel[i];

		irq_set_affinity_hint(channel->dma_irq, NULL);
		devm_free_irq(pdata->dev, channel->dma_irq, channel);
	}
}