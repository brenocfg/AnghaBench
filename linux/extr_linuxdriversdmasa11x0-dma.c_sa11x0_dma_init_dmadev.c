#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  desc_free; } ;
struct sa11x0_dma_chan {TYPE_1__ vc; int /*<<< orphan*/  node; int /*<<< orphan*/  name; int /*<<< orphan*/  ddar; int /*<<< orphan*/  status; } ;
struct dma_device {int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_resume; int /*<<< orphan*/  device_pause; int /*<<< orphan*/  device_config; int /*<<< orphan*/  device_free_chan_resources; struct device* dev; int /*<<< orphan*/  channels; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  ddar; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  DMA_IN_PROGRESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_2__* chan_desc ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 int dma_async_device_register (struct dma_device*) ; 
 struct sa11x0_dma_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa11x0_dma_device_config ; 
 int /*<<< orphan*/  sa11x0_dma_device_pause ; 
 int /*<<< orphan*/  sa11x0_dma_device_resume ; 
 int /*<<< orphan*/  sa11x0_dma_device_terminate_all ; 
 int /*<<< orphan*/  sa11x0_dma_free_chan_resources ; 
 int /*<<< orphan*/  sa11x0_dma_free_desc ; 
 int /*<<< orphan*/  sa11x0_dma_issue_pending ; 
 int /*<<< orphan*/  sa11x0_dma_tx_status ; 
 int /*<<< orphan*/  vchan_init (TYPE_1__*,struct dma_device*) ; 

__attribute__((used)) static int sa11x0_dma_init_dmadev(struct dma_device *dmadev,
	struct device *dev)
{
	unsigned i;

	INIT_LIST_HEAD(&dmadev->channels);
	dmadev->dev = dev;
	dmadev->device_free_chan_resources = sa11x0_dma_free_chan_resources;
	dmadev->device_config = sa11x0_dma_device_config;
	dmadev->device_pause = sa11x0_dma_device_pause;
	dmadev->device_resume = sa11x0_dma_device_resume;
	dmadev->device_terminate_all = sa11x0_dma_device_terminate_all;
	dmadev->device_tx_status = sa11x0_dma_tx_status;
	dmadev->device_issue_pending = sa11x0_dma_issue_pending;

	for (i = 0; i < ARRAY_SIZE(chan_desc); i++) {
		struct sa11x0_dma_chan *c;

		c = kzalloc(sizeof(*c), GFP_KERNEL);
		if (!c) {
			dev_err(dev, "no memory for channel %u\n", i);
			return -ENOMEM;
		}

		c->status = DMA_IN_PROGRESS;
		c->ddar = chan_desc[i].ddar;
		c->name = chan_desc[i].name;
		INIT_LIST_HEAD(&c->node);

		c->vc.desc_free = sa11x0_dma_free_desc;
		vchan_init(&c->vc, dmadev);
	}

	return dma_async_device_register(dmadev);
}