#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct vpfe_subdev_info {int /*<<< orphan*/  ccdc_if_params; scalar_t__ can_route; struct vpfe_route* routes; } ;
struct vpfe_route {scalar_t__ output; scalar_t__ input; } ;
struct TYPE_10__ {int /*<<< orphan*/  ctrl_handler; } ;
struct vpfe_device {unsigned int current_input; size_t std_index; int /*<<< orphan*/  lock; TYPE_4__ v4l2_dev; struct vpfe_subdev_info* current_subdev; struct v4l2_subdev** sd; TYPE_1__* cfg; scalar_t__ started; } ;
struct v4l2_subdev {int /*<<< orphan*/  ctrl_handler; } ;
struct file {int dummy; } ;
struct TYPE_8__ {int (* set_hw_if_params ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {TYPE_2__ hw_ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  std_id; } ;
struct TYPE_7__ {struct vpfe_subdev_info* sub_devs; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 TYPE_6__* ccdc_dev ; 
 int /*<<< orphan*/  debug ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_routing ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,TYPE_4__*,char*) ; 
 int /*<<< orphan*/  v4l2_err (TYPE_4__*,char*) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 int vpfe_config_image_format (struct vpfe_device*,int /*<<< orphan*/ ) ; 
 int vpfe_get_subdev_input_index (struct vpfe_device*,int*,int*,unsigned int) ; 
 TYPE_3__* vpfe_standards ; 

__attribute__((used)) static int vpfe_s_input(struct file *file, void *priv, unsigned int index)
{
	struct vpfe_device *vpfe_dev = video_drvdata(file);
	struct v4l2_subdev *sd;
	struct vpfe_subdev_info *sdinfo;
	int subdev_index, inp_index;
	struct vpfe_route *route;
	u32 input, output;
	int ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_s_input\n");

	ret = mutex_lock_interruptible(&vpfe_dev->lock);
	if (ret)
		return ret;

	/*
	 * If streaming is started return device busy
	 * error
	 */
	if (vpfe_dev->started) {
		v4l2_err(&vpfe_dev->v4l2_dev, "Streaming is on\n");
		ret = -EBUSY;
		goto unlock_out;
	}
	ret = vpfe_get_subdev_input_index(vpfe_dev,
					  &subdev_index,
					  &inp_index,
					  index);
	if (ret < 0) {
		v4l2_err(&vpfe_dev->v4l2_dev, "invalid input index\n");
		goto unlock_out;
	}

	sdinfo = &vpfe_dev->cfg->sub_devs[subdev_index];
	sd = vpfe_dev->sd[subdev_index];
	route = &sdinfo->routes[inp_index];
	if (route && sdinfo->can_route) {
		input = route->input;
		output = route->output;
	} else {
		input = 0;
		output = 0;
	}

	if (sd)
		ret = v4l2_subdev_call(sd, video, s_routing, input, output, 0);

	if (ret) {
		v4l2_err(&vpfe_dev->v4l2_dev,
			"vpfe_doioctl:error in setting input in decoder\n");
		ret = -EINVAL;
		goto unlock_out;
	}
	vpfe_dev->current_subdev = sdinfo;
	if (sd)
		vpfe_dev->v4l2_dev.ctrl_handler = sd->ctrl_handler;
	vpfe_dev->current_input = index;
	vpfe_dev->std_index = 0;

	/* set the bus/interface parameter for the sub device in ccdc */
	ret = ccdc_dev->hw_ops.set_hw_if_params(&sdinfo->ccdc_if_params);
	if (ret)
		goto unlock_out;

	/* set the default image parameters in the device */
	ret = vpfe_config_image_format(vpfe_dev,
				vpfe_standards[vpfe_dev->std_index].std_id);
unlock_out:
	mutex_unlock(&vpfe_dev->lock);
	return ret;
}