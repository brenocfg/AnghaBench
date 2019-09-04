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
struct scif_hw_dev {int num_dma_ch; struct dma_chan** dma_ch; } ;
struct TYPE_3__ {int /*<<< orphan*/  rma_lock; struct dma_chan* dma_chan; } ;
struct scif_endpt {TYPE_1__ rma_info; struct scif_dev* remote_dev; } ;
struct scif_dev {size_t dma_ch_idx; struct scif_hw_dev* sdev; } ;
struct dma_chan {int dummy; } ;
struct TYPE_4__ {scalar_t__ nodeid; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct scif_dev* scif_dev ; 
 TYPE_2__ scif_info ; 
 scalar_t__ scifdev_self (struct scif_dev*) ; 

int scif_reserve_dma_chan(struct scif_endpt *ep)
{
	int err = 0;
	struct scif_dev *scifdev;
	struct scif_hw_dev *sdev;
	struct dma_chan *chan;

	/* Loopback DMAs are not supported on the management node */
	if (!scif_info.nodeid && scifdev_self(ep->remote_dev))
		return 0;
	if (scif_info.nodeid)
		scifdev = &scif_dev[0];
	else
		scifdev = ep->remote_dev;
	sdev = scifdev->sdev;
	if (!sdev->num_dma_ch)
		return -ENODEV;
	chan = sdev->dma_ch[scifdev->dma_ch_idx];
	scifdev->dma_ch_idx = (scifdev->dma_ch_idx + 1) % sdev->num_dma_ch;
	mutex_lock(&ep->rma_info.rma_lock);
	ep->rma_info.dma_chan = chan;
	mutex_unlock(&ep->rma_info.rma_lock);
	return err;
}