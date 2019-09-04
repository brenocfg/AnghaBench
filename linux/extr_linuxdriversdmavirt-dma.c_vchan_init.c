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
struct TYPE_2__ {int /*<<< orphan*/  device_node; struct dma_device* device; } ;
struct virt_dma_chan {TYPE_1__ chan; int /*<<< orphan*/  task; int /*<<< orphan*/  desc_completed; int /*<<< orphan*/  desc_issued; int /*<<< orphan*/  desc_submitted; int /*<<< orphan*/  desc_allocated; int /*<<< orphan*/  lock; } ;
struct dma_device {int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_cookie_init (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vchan_complete ; 

void vchan_init(struct virt_dma_chan *vc, struct dma_device *dmadev)
{
	dma_cookie_init(&vc->chan);

	spin_lock_init(&vc->lock);
	INIT_LIST_HEAD(&vc->desc_allocated);
	INIT_LIST_HEAD(&vc->desc_submitted);
	INIT_LIST_HEAD(&vc->desc_issued);
	INIT_LIST_HEAD(&vc->desc_completed);

	tasklet_init(&vc->task, vchan_complete, (unsigned long)vc);

	vc->chan.device = dmadev;
	list_add_tail(&vc->chan.device_node, &dmadev->channels);
}