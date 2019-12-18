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
struct msi2500_dev {int /*<<< orphan*/  v4l2_lock; int /*<<< orphan*/  v4l2_subdev; int /*<<< orphan*/  udev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_START_STREAMING ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msi2500_cleanup_queued_bufs (struct msi2500_dev*) ; 
 int msi2500_ctrl_msg (struct msi2500_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msi2500_isoc_init (struct msi2500_dev*) ; 
 int msi2500_set_usb_adc (struct msi2500_dev*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_power ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct msi2500_dev* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int msi2500_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct msi2500_dev *dev = vb2_get_drv_priv(vq);
	int ret;

	dev_dbg(dev->dev, "\n");

	if (!dev->udev)
		return -ENODEV;

	if (mutex_lock_interruptible(&dev->v4l2_lock))
		return -ERESTARTSYS;

	/* wake-up tuner */
	v4l2_subdev_call(dev->v4l2_subdev, core, s_power, 1);

	ret = msi2500_set_usb_adc(dev);

	ret = msi2500_isoc_init(dev);
	if (ret)
		msi2500_cleanup_queued_bufs(dev);

	ret = msi2500_ctrl_msg(dev, CMD_START_STREAMING, 0);

	mutex_unlock(&dev->v4l2_lock);

	return ret;
}