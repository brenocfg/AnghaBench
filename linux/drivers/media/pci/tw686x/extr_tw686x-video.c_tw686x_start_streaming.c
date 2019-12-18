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
struct vb2_queue {int dummy; } ;
struct tw686x_video_channel {int /*<<< orphan*/  qlock; int /*<<< orphan*/  ch; int /*<<< orphan*/  pb; scalar_t__ sequence; int /*<<< orphan*/  num; TYPE_1__* dma_descs; struct tw686x_dev* dev; } ;
struct tw686x_dev {scalar_t__ dma_mode; int /*<<< orphan*/  dma_delay_timer; int /*<<< orphan*/  lock; TYPE_2__* dma_ops; int /*<<< orphan*/  v4l2_dev; struct pci_dev* pci_dev; } ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* buf_refill ) (struct tw686x_video_channel*,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  virt; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ TW686X_DMA_MODE_MEMCPY ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct tw686x_video_channel*,int) ; 
 int /*<<< orphan*/  tw686x_clear_queue (struct tw686x_video_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw686x_enable_channel (struct tw686x_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct tw686x_video_channel* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int tw686x_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct tw686x_video_channel *vc = vb2_get_drv_priv(vq);
	struct tw686x_dev *dev = vc->dev;
	struct pci_dev *pci_dev;
	unsigned long flags;
	int pb, err;

	/* Check device presence */
	spin_lock_irqsave(&dev->lock, flags);
	pci_dev = dev->pci_dev;
	spin_unlock_irqrestore(&dev->lock, flags);
	if (!pci_dev) {
		err = -ENODEV;
		goto err_clear_queue;
	}

	spin_lock_irqsave(&vc->qlock, flags);

	/* Sanity check */
	if (dev->dma_mode == TW686X_DMA_MODE_MEMCPY &&
	    (!vc->dma_descs[0].virt || !vc->dma_descs[1].virt)) {
		spin_unlock_irqrestore(&vc->qlock, flags);
		v4l2_err(&dev->v4l2_dev,
			 "video%d: refusing to start without DMA buffers\n",
			 vc->num);
		err = -ENOMEM;
		goto err_clear_queue;
	}

	for (pb = 0; pb < 2; pb++)
		dev->dma_ops->buf_refill(vc, pb);
	spin_unlock_irqrestore(&vc->qlock, flags);

	vc->sequence = 0;
	vc->pb = 0;

	spin_lock_irqsave(&dev->lock, flags);
	tw686x_enable_channel(dev, vc->ch);
	spin_unlock_irqrestore(&dev->lock, flags);

	mod_timer(&dev->dma_delay_timer, jiffies + msecs_to_jiffies(100));

	return 0;

err_clear_queue:
	spin_lock_irqsave(&vc->qlock, flags);
	tw686x_clear_queue(vc, VB2_BUF_STATE_QUEUED);
	spin_unlock_irqrestore(&vc->qlock, flags);
	return err;
}