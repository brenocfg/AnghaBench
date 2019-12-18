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
typedef  int v4l2_std_id ;
struct vb2_queue {int dummy; } ;
struct stk1160 {int norm; int width; int height; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  udev; struct vb2_queue vb_vidq; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  stk1160_set_fmt (struct stk1160*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stk1160_set_std (struct stk1160*) ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vb2_is_busy (struct vb2_queue*) ; 
 int /*<<< orphan*/  video ; 
 struct stk1160* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_std(struct file *file, void *priv, v4l2_std_id norm)
{
	struct stk1160 *dev = video_drvdata(file);
	struct vb2_queue *q = &dev->vb_vidq;

	if (dev->norm == norm)
		return 0;

	if (vb2_is_busy(q))
		return -EBUSY;

	/* Check device presence */
	if (!dev->udev)
		return -ENODEV;

	/* We need to set this now, before we call stk1160_set_std */
	dev->width = 720;
	dev->height = (norm & V4L2_STD_525_60) ? 480 : 576;
	dev->norm = norm;

	stk1160_set_std(dev);

	/* Calling with NULL disables frame decimation */
	stk1160_set_fmt(dev, NULL);

	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_std,
			dev->norm);

	return 0;
}