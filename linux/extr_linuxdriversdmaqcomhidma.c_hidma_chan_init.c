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
typedef  int /*<<< orphan*/  u32 ;
struct dma_device {int /*<<< orphan*/  chancnt; int /*<<< orphan*/  channels; int /*<<< orphan*/  dev; } ;
struct hidma_dev {struct dma_device ddev; } ;
struct TYPE_2__ {int /*<<< orphan*/  device_node; struct dma_device* device; } ;
struct hidma_chan {TYPE_1__ chan; int /*<<< orphan*/  lock; int /*<<< orphan*/  queued; int /*<<< orphan*/  completed; int /*<<< orphan*/  active; int /*<<< orphan*/  prepared; int /*<<< orphan*/  free; struct hidma_dev* dmadev; int /*<<< orphan*/  dma_sig; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct hidma_chan* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cookie_init (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hidma_chan_init(struct hidma_dev *dmadev, u32 dma_sig)
{
	struct hidma_chan *mchan;
	struct dma_device *ddev;

	mchan = devm_kzalloc(dmadev->ddev.dev, sizeof(*mchan), GFP_KERNEL);
	if (!mchan)
		return -ENOMEM;

	ddev = &dmadev->ddev;
	mchan->dma_sig = dma_sig;
	mchan->dmadev = dmadev;
	mchan->chan.device = ddev;
	dma_cookie_init(&mchan->chan);

	INIT_LIST_HEAD(&mchan->free);
	INIT_LIST_HEAD(&mchan->prepared);
	INIT_LIST_HEAD(&mchan->active);
	INIT_LIST_HEAD(&mchan->completed);
	INIT_LIST_HEAD(&mchan->queued);

	spin_lock_init(&mchan->lock);
	list_add_tail(&mchan->chan.device_node, &ddev->channels);
	dmadev->ddev.chancnt++;
	return 0;
}