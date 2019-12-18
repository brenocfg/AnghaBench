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
struct msi2500_dev {int /*<<< orphan*/  v4l2_lock; int /*<<< orphan*/  v4l2_subdev; scalar_t__ udev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STOP_STREAMING ; 
 int /*<<< orphan*/  CMD_WREG ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msi2500_cleanup_queued_bufs (struct msi2500_dev*) ; 
 int /*<<< orphan*/  msi2500_ctrl_msg (struct msi2500_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msi2500_isoc_cleanup (struct msi2500_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_power ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct msi2500_dev* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void msi2500_stop_streaming(struct vb2_queue *vq)
{
	struct msi2500_dev *dev = vb2_get_drv_priv(vq);

	dev_dbg(dev->dev, "\n");

	mutex_lock(&dev->v4l2_lock);

	if (dev->udev)
		msi2500_isoc_cleanup(dev);

	msi2500_cleanup_queued_bufs(dev);

	/* according to tests, at least 700us delay is required  */
	msleep(20);
	if (!msi2500_ctrl_msg(dev, CMD_STOP_STREAMING, 0)) {
		/* sleep USB IF / ADC */
		msi2500_ctrl_msg(dev, CMD_WREG, 0x01000003);
	}

	/* sleep tuner */
	v4l2_subdev_call(dev->v4l2_subdev, core, s_power, 0);

	mutex_unlock(&dev->v4l2_lock);
}