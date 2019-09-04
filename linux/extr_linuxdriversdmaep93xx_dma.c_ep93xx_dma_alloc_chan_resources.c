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
struct TYPE_4__ {int /*<<< orphan*/  tx_submit; int /*<<< orphan*/  flags; } ;
struct ep93xx_dma_desc {TYPE_2__ txd; int /*<<< orphan*/  tx_list; } ;
struct ep93xx_dma_data {int port; scalar_t__ direction; char* name; } ;
struct ep93xx_dma_chan {int /*<<< orphan*/  clk; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; TYPE_1__* edma; int /*<<< orphan*/  chan; } ;
struct dma_chan {struct ep93xx_dma_data* private; } ;
struct TYPE_3__ {int (* hw_setup ) (struct ep93xx_dma_chan*) ;int /*<<< orphan*/  m2m; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CTRL_ACK ; 
 int DMA_MAX_CHAN_DESCRIPTORS ; 
 int EINVAL ; 
 int EP93XX_DMA_I2S1 ; 
#define  EP93XX_DMA_IDE 129 
 int EP93XX_DMA_IRDA ; 
#define  EP93XX_DMA_SSP 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chan2dev (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_2__*,struct dma_chan*) ; 
 char* dma_chan_name (struct dma_chan*) ; 
 int /*<<< orphan*/  dma_cookie_init (int /*<<< orphan*/ *) ; 
 scalar_t__ ep93xx_dma_chan_direction (struct dma_chan*) ; 
 int /*<<< orphan*/  ep93xx_dma_desc_put (struct ep93xx_dma_chan*,struct ep93xx_dma_desc*) ; 
 int /*<<< orphan*/  ep93xx_dma_interrupt ; 
 int /*<<< orphan*/  ep93xx_dma_tx_submit ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  is_slave_direction (scalar_t__) ; 
 struct ep93xx_dma_desc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (struct ep93xx_dma_chan*) ; 
 struct ep93xx_dma_chan* to_ep93xx_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int ep93xx_dma_alloc_chan_resources(struct dma_chan *chan)
{
	struct ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	struct ep93xx_dma_data *data = chan->private;
	const char *name = dma_chan_name(chan);
	int ret, i;

	/* Sanity check the channel parameters */
	if (!edmac->edma->m2m) {
		if (!data)
			return -EINVAL;
		if (data->port < EP93XX_DMA_I2S1 ||
		    data->port > EP93XX_DMA_IRDA)
			return -EINVAL;
		if (data->direction != ep93xx_dma_chan_direction(chan))
			return -EINVAL;
	} else {
		if (data) {
			switch (data->port) {
			case EP93XX_DMA_SSP:
			case EP93XX_DMA_IDE:
				if (!is_slave_direction(data->direction))
					return -EINVAL;
				break;
			default:
				return -EINVAL;
			}
		}
	}

	if (data && data->name)
		name = data->name;

	ret = clk_enable(edmac->clk);
	if (ret)
		return ret;

	ret = request_irq(edmac->irq, ep93xx_dma_interrupt, 0, name, edmac);
	if (ret)
		goto fail_clk_disable;

	spin_lock_irq(&edmac->lock);
	dma_cookie_init(&edmac->chan);
	ret = edmac->edma->hw_setup(edmac);
	spin_unlock_irq(&edmac->lock);

	if (ret)
		goto fail_free_irq;

	for (i = 0; i < DMA_MAX_CHAN_DESCRIPTORS; i++) {
		struct ep93xx_dma_desc *desc;

		desc = kzalloc(sizeof(*desc), GFP_KERNEL);
		if (!desc) {
			dev_warn(chan2dev(edmac), "not enough descriptors\n");
			break;
		}

		INIT_LIST_HEAD(&desc->tx_list);

		dma_async_tx_descriptor_init(&desc->txd, chan);
		desc->txd.flags = DMA_CTRL_ACK;
		desc->txd.tx_submit = ep93xx_dma_tx_submit;

		ep93xx_dma_desc_put(edmac, desc);
	}

	return i;

fail_free_irq:
	free_irq(edmac->irq, edmac);
fail_clk_disable:
	clk_disable(edmac->clk);

	return ret;
}