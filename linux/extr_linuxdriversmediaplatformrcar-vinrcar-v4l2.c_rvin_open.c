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
struct rvin_dev {int /*<<< orphan*/  lock; } ;
struct file {struct rvin_dev* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rvin_initialize_device (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 struct rvin_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int rvin_open(struct file *file)
{
	struct rvin_dev *vin = video_drvdata(file);
	int ret;

	mutex_lock(&vin->lock);

	file->private_data = vin;

	ret = v4l2_fh_open(file);
	if (ret)
		goto unlock;

	if (!v4l2_fh_is_singular_file(file))
		goto unlock;

	if (rvin_initialize_device(file)) {
		v4l2_fh_release(file);
		ret = -ENODEV;
	}

unlock:
	mutex_unlock(&vin->lock);
	return ret;
}