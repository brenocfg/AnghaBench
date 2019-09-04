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
struct v4l2_subdev {int dummy; } ;
struct isc_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  fmt; TYPE_1__* current_subdev; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct v4l2_subdev* sd; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  core ; 
 int isc_set_fmt (struct isc_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_power ; 
 int /*<<< orphan*/  v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct isc_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int isc_open(struct file *file)
{
	struct isc_device *isc = video_drvdata(file);
	struct v4l2_subdev *sd = isc->current_subdev->sd;
	int ret;

	if (mutex_lock_interruptible(&isc->lock))
		return -ERESTARTSYS;

	ret = v4l2_fh_open(file);
	if (ret < 0)
		goto unlock;

	if (!v4l2_fh_is_singular_file(file))
		goto unlock;

	ret = v4l2_subdev_call(sd, core, s_power, 1);
	if (ret < 0 && ret != -ENOIOCTLCMD) {
		v4l2_fh_release(file);
		goto unlock;
	}

	ret = isc_set_fmt(isc, &isc->fmt);
	if (ret) {
		v4l2_subdev_call(sd, core, s_power, 0);
		v4l2_fh_release(file);
	}

unlock:
	mutex_unlock(&isc->lock);
	return ret;
}