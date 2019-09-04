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
struct viu_fh {scalar_t__ dev; } ;
struct viu_dev {int ovenable; int /*<<< orphan*/  slock; int /*<<< orphan*/  vr; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  viu_activate_overlay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viu_start_dma (struct viu_dev*) ; 
 int /*<<< orphan*/  viu_stop_dma (struct viu_dev*) ; 

__attribute__((used)) static int vidioc_overlay(struct file *file, void *priv, unsigned int on)
{
	struct viu_fh  *fh  = priv;
	struct viu_dev *dev = (struct viu_dev *)fh->dev;
	unsigned long  flags;

	if (on) {
		spin_lock_irqsave(&dev->slock, flags);
		viu_activate_overlay(dev->vr);
		dev->ovenable = 1;

		/* start dma */
		viu_start_dma(dev);
		spin_unlock_irqrestore(&dev->slock, flags);
	} else {
		viu_stop_dma(dev);
		dev->ovenable = 0;
	}

	return 0;
}