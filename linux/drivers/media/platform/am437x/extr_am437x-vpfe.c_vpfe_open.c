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
struct vpfe_device {int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vpfe_err (struct vpfe_device*,char*) ; 
 scalar_t__ vpfe_initialize_device (struct vpfe_device*) ; 

__attribute__((used)) static int vpfe_open(struct file *file)
{
	struct vpfe_device *vpfe = video_drvdata(file);
	int ret;

	mutex_lock(&vpfe->lock);

	ret = v4l2_fh_open(file);
	if (ret) {
		vpfe_err(vpfe, "v4l2_fh_open failed\n");
		goto unlock;
	}

	if (!v4l2_fh_is_singular_file(file))
		goto unlock;

	if (vpfe_initialize_device(vpfe)) {
		v4l2_fh_release(file);
		ret = -ENODEV;
	}

unlock:
	mutex_unlock(&vpfe->lock);
	return ret;
}