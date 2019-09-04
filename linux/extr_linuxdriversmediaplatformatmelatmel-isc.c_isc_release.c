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
struct isc_device {int /*<<< orphan*/  lock; TYPE_1__* current_subdev; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct v4l2_subdev* sd; } ;

/* Variables and functions */
 int _vb2_fop_release (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_power ; 
 int v4l2_fh_is_singular_file (struct file*) ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isc_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int isc_release(struct file *file)
{
	struct isc_device *isc = video_drvdata(file);
	struct v4l2_subdev *sd = isc->current_subdev->sd;
	bool fh_singular;
	int ret;

	mutex_lock(&isc->lock);

	fh_singular = v4l2_fh_is_singular_file(file);

	ret = _vb2_fop_release(file, NULL);

	if (fh_singular)
		v4l2_subdev_call(sd, core, s_power, 0);

	mutex_unlock(&isc->lock);

	return ret;
}