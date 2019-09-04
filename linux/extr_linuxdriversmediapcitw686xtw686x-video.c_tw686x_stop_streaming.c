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
struct vb2_queue {int dummy; } ;
struct tw686x_video_channel {int /*<<< orphan*/  qlock; int /*<<< orphan*/  ch; struct tw686x_dev* dev; } ;
struct tw686x_dev {int /*<<< orphan*/  lock; struct pci_dev* pci_dev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tw686x_clear_queue (struct tw686x_video_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw686x_disable_channel (struct tw686x_dev*,int /*<<< orphan*/ ) ; 
 struct tw686x_video_channel* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void tw686x_stop_streaming(struct vb2_queue *vq)
{
	struct tw686x_video_channel *vc = vb2_get_drv_priv(vq);
	struct tw686x_dev *dev = vc->dev;
	struct pci_dev *pci_dev;
	unsigned long flags;

	/* Check device presence */
	spin_lock_irqsave(&dev->lock, flags);
	pci_dev = dev->pci_dev;
	spin_unlock_irqrestore(&dev->lock, flags);
	if (pci_dev)
		tw686x_disable_channel(dev, vc->ch);

	spin_lock_irqsave(&vc->qlock, flags);
	tw686x_clear_queue(vc, VB2_BUF_STATE_ERROR);
	spin_unlock_irqrestore(&vc->qlock, flags);
}