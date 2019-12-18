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
struct xlgmac_pdata {unsigned int channel_count; int /*<<< orphan*/  dma_irq; int /*<<< orphan*/  dev; struct xlgmac_pdata* channel_head; int /*<<< orphan*/  per_channel_irq; int /*<<< orphan*/  dev_irq; } ;
struct xlgmac_channel {unsigned int channel_count; int /*<<< orphan*/  dma_irq; int /*<<< orphan*/  dev; struct xlgmac_channel* channel_head; int /*<<< orphan*/  per_channel_irq; int /*<<< orphan*/  dev_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xlgmac_pdata*) ; 

__attribute__((used)) static void xlgmac_free_irqs(struct xlgmac_pdata *pdata)
{
	struct xlgmac_channel *channel;
	unsigned int i;

	devm_free_irq(pdata->dev, pdata->dev_irq, pdata);

	if (!pdata->per_channel_irq)
		return;

	channel = pdata->channel_head;
	for (i = 0; i < pdata->channel_count; i++, channel++)
		devm_free_irq(pdata->dev, channel->dma_irq, channel);
}