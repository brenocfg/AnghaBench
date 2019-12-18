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
struct saa7134_dev {void* overlay_owner; int /*<<< orphan*/  slock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ saa7134_no_overlay ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_preview (struct saa7134_dev*) ; 
 int /*<<< orphan*/  stop_preview (struct saa7134_dev*) ; 
 int /*<<< orphan*/  video_dbg (char*) ; 
 struct saa7134_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int saa7134_overlay(struct file *file, void *priv, unsigned int on)
{
	struct saa7134_dev *dev = video_drvdata(file);
	unsigned long flags;

	if (on) {
		if (saa7134_no_overlay > 0) {
			video_dbg("no_overlay\n");
			return -EINVAL;
		}

		if (dev->overlay_owner && priv != dev->overlay_owner)
			return -EBUSY;
		dev->overlay_owner = priv;
		spin_lock_irqsave(&dev->slock, flags);
		start_preview(dev);
		spin_unlock_irqrestore(&dev->slock, flags);
	}
	if (!on) {
		if (priv != dev->overlay_owner)
			return -EINVAL;
		spin_lock_irqsave(&dev->slock, flags);
		stop_preview(dev);
		spin_unlock_irqrestore(&dev->slock, flags);
		dev->overlay_owner = NULL;
	}
	return 0;
}