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
struct v4l2_subdev {int dummy; } ;
struct unicam_device {int /*<<< orphan*/  lock; struct v4l2_subdev* sensor; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int _vb2_fop_release (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_power ; 
 int v4l2_fh_is_singular_file (struct file*) ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct unicam_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int unicam_release(struct file *file)
{
	struct unicam_device *dev = video_drvdata(file);
	struct v4l2_subdev *sd = dev->sensor;
	bool fh_singular;
	int ret;

	mutex_lock(&dev->lock);

	fh_singular = v4l2_fh_is_singular_file(file);

	ret = _vb2_fop_release(file, NULL);

	if (fh_singular)
		v4l2_subdev_call(sd, core, s_power, 0);

	mutex_unlock(&dev->lock);

	return ret;
}