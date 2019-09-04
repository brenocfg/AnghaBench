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
struct unicam_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  sensor; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_power ; 
 int /*<<< orphan*/  unicam_err (struct unicam_device*,char*) ; 
 int /*<<< orphan*/  v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct unicam_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int unicam_open(struct file *file)
{
	struct unicam_device *dev = video_drvdata(file);
	int ret;

	mutex_lock(&dev->lock);

	ret = v4l2_fh_open(file);
	if (ret) {
		unicam_err(dev, "v4l2_fh_open failed\n");
		goto unlock;
	}

	if (!v4l2_fh_is_singular_file(file))
		goto unlock;

	ret = v4l2_subdev_call(dev->sensor, core, s_power, 1);
	if (ret < 0 && ret != -ENOIOCTLCMD) {
		v4l2_fh_release(file);
		goto unlock;
	}

unlock:
	mutex_unlock(&dev->lock);
	return ret;
}