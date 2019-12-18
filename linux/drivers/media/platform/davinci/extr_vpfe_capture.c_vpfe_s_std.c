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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct vpfe_subdev_info {int /*<<< orphan*/  grp_id; } ;
struct vpfe_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  v4l2_dev; scalar_t__ started; struct vpfe_subdev_info* current_subdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  debug ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int v4l2_device_call_until_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  video ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 int vpfe_config_image_format (struct vpfe_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpfe_s_std(struct file *file, void *priv, v4l2_std_id std_id)
{
	struct vpfe_device *vpfe_dev = video_drvdata(file);
	struct vpfe_subdev_info *sdinfo;
	int ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_s_std\n");

	/* Call decoder driver function to set the standard */
	ret = mutex_lock_interruptible(&vpfe_dev->lock);
	if (ret)
		return ret;

	sdinfo = vpfe_dev->current_subdev;
	/* If streaming is started, return device busy error */
	if (vpfe_dev->started) {
		v4l2_err(&vpfe_dev->v4l2_dev, "streaming is started\n");
		ret = -EBUSY;
		goto unlock_out;
	}

	ret = v4l2_device_call_until_err(&vpfe_dev->v4l2_dev, sdinfo->grp_id,
					 video, s_std, std_id);
	if (ret < 0) {
		v4l2_err(&vpfe_dev->v4l2_dev, "Failed to set standard\n");
		goto unlock_out;
	}
	ret = vpfe_config_image_format(vpfe_dev, std_id);

unlock_out:
	mutex_unlock(&vpfe_dev->lock);
	return ret;
}