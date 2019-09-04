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
struct mmp_pdma_phy {int idx; int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int /*<<< orphan*/  channels; } ;
struct mmp_pdma_device {TYPE_2__ device; int /*<<< orphan*/  dev; int /*<<< orphan*/  base; struct mmp_pdma_phy* phy; } ;
struct TYPE_3__ {int /*<<< orphan*/  device_node; TYPE_2__* device; } ;
struct mmp_pdma_chan {TYPE_1__ chan; int /*<<< orphan*/  chain_running; int /*<<< orphan*/  chain_pending; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  dev; int /*<<< orphan*/  desc_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mmp_pdma_chan* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mmp_pdma_phy*) ; 
 int /*<<< orphan*/  dma_do_tasklet ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmp_pdma_chan_handler ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int mmp_pdma_chan_init(struct mmp_pdma_device *pdev, int idx, int irq)
{
	struct mmp_pdma_phy *phy  = &pdev->phy[idx];
	struct mmp_pdma_chan *chan;
	int ret;

	chan = devm_kzalloc(pdev->dev, sizeof(*chan), GFP_KERNEL);
	if (chan == NULL)
		return -ENOMEM;

	phy->idx = idx;
	phy->base = pdev->base;

	if (irq) {
		ret = devm_request_irq(pdev->dev, irq, mmp_pdma_chan_handler,
				       IRQF_SHARED, "pdma", phy);
		if (ret) {
			dev_err(pdev->dev, "channel request irq fail!\n");
			return ret;
		}
	}

	spin_lock_init(&chan->desc_lock);
	chan->dev = pdev->dev;
	chan->chan.device = &pdev->device;
	tasklet_init(&chan->tasklet, dma_do_tasklet, (unsigned long)chan);
	INIT_LIST_HEAD(&chan->chain_pending);
	INIT_LIST_HEAD(&chan->chain_running);

	/* register virt channel to dma engine */
	list_add_tail(&chan->chan.device_node, &pdev->device.channels);

	return 0;
}