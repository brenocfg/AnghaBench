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
struct xlgmac_pdata {unsigned int channel_count; int queue_index; int /*<<< orphan*/  dev_irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_irq; int /*<<< orphan*/  dma_irq_name; struct xlgmac_pdata* channel_head; int /*<<< orphan*/  per_channel_irq; struct net_device* netdev; } ;
struct xlgmac_channel {unsigned int channel_count; int queue_index; int /*<<< orphan*/  dev_irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_irq; int /*<<< orphan*/  dma_irq_name; struct xlgmac_channel* channel_head; int /*<<< orphan*/  per_channel_irq; struct net_device* netdev; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xlgmac_pdata*) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  netdev_alert (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 char* netdev_name (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/  xlgmac_dma_isr ; 
 int /*<<< orphan*/  xlgmac_isr ; 

__attribute__((used)) static int xlgmac_request_irqs(struct xlgmac_pdata *pdata)
{
	struct net_device *netdev = pdata->netdev;
	struct xlgmac_channel *channel;
	unsigned int i;
	int ret;

	ret = devm_request_irq(pdata->dev, pdata->dev_irq, xlgmac_isr,
			       IRQF_SHARED, netdev->name, pdata);
	if (ret) {
		netdev_alert(netdev, "error requesting irq %d\n",
			     pdata->dev_irq);
		return ret;
	}

	if (!pdata->per_channel_irq)
		return 0;

	channel = pdata->channel_head;
	for (i = 0; i < pdata->channel_count; i++, channel++) {
		snprintf(channel->dma_irq_name,
			 sizeof(channel->dma_irq_name) - 1,
			 "%s-TxRx-%u", netdev_name(netdev),
			 channel->queue_index);

		ret = devm_request_irq(pdata->dev, channel->dma_irq,
				       xlgmac_dma_isr, 0,
				       channel->dma_irq_name, channel);
		if (ret) {
			netdev_alert(netdev, "error requesting irq %d\n",
				     channel->dma_irq);
			goto err_irq;
		}
	}

	return 0;

err_irq:
	/* Using an unsigned int, 'i' will go to UINT_MAX and exit */
	for (i--, channel--; i < pdata->channel_count; i--, channel--)
		devm_free_irq(pdata->dev, channel->dma_irq, channel);

	devm_free_irq(pdata->dev, pdata->dev_irq, pdata);

	return ret;
}