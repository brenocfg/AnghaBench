#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  left_margin; } ;
struct vpbe_device {int current_sd_index; int current_out_index; int /*<<< orphan*/  lock; TYPE_4__ current_timings; struct osd_state* osd_device; int /*<<< orphan*/ * encoders; struct venc_platform_data* venc_device; struct vpbe_config* cfg; } ;
struct vpbe_config {int num_outputs; TYPE_2__* outputs; } ;
struct venc_platform_data {int (* setup_if_config ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_top_margin ) (struct osd_state*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_left_margin ) (struct osd_state*,int /*<<< orphan*/ ) ;} ;
struct osd_state {TYPE_3__ ops; } ;
struct encoder_config_info {int /*<<< orphan*/  module_name; } ;
struct TYPE_5__ {int index; } ;
struct TYPE_6__ {int /*<<< orphan*/  default_mode; int /*<<< orphan*/  if_params; int /*<<< orphan*/  subdev_name; TYPE_1__ output; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_routing ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct osd_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct osd_state*,int /*<<< orphan*/ ) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 
 struct encoder_config_info* vpbe_current_encoder_info (struct vpbe_device*) ; 
 int vpbe_find_encoder_sd_index (struct vpbe_config*,int) ; 
 int vpbe_get_mode_info (struct vpbe_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vpbe_set_output(struct vpbe_device *vpbe_dev, int index)
{
	struct encoder_config_info *curr_enc_info =
			vpbe_current_encoder_info(vpbe_dev);
	struct vpbe_config *cfg = vpbe_dev->cfg;
	struct venc_platform_data *venc_device = vpbe_dev->venc_device;
	int enc_out_index;
	int sd_index;
	int ret;

	if (index >= cfg->num_outputs)
		return -EINVAL;

	mutex_lock(&vpbe_dev->lock);

	sd_index = vpbe_dev->current_sd_index;
	enc_out_index = cfg->outputs[index].output.index;
	/*
	 * Currently we switch the encoder based on output selected
	 * by the application. If media controller is implemented later
	 * there is will be an API added to setup_link between venc
	 * and external encoder. So in that case below comparison always
	 * match and encoder will not be switched. But if application
	 * chose not to use media controller, then this provides current
	 * way of switching encoder at the venc output.
	 */
	if (strcmp(curr_enc_info->module_name,
		   cfg->outputs[index].subdev_name)) {
		/* Need to switch the encoder at the output */
		sd_index = vpbe_find_encoder_sd_index(cfg, index);
		if (sd_index < 0) {
			ret = -EINVAL;
			goto unlock;
		}

		ret = venc_device->setup_if_config(cfg->outputs[index].if_params);
		if (ret)
			goto unlock;
	}

	/* Set output at the encoder */
	ret = v4l2_subdev_call(vpbe_dev->encoders[sd_index], video,
				       s_routing, 0, enc_out_index, 0);
	if (ret)
		goto unlock;

	/*
	 * It is assumed that venc or external encoder will set a default
	 * mode in the sub device. For external encoder or LCD pannel output,
	 * we also need to set up the lcd port for the required mode. So setup
	 * the lcd port for the default mode that is configured in the board
	 * arch/arm/mach-davinci/board-dm355-evm.setup file for the external
	 * encoder.
	 */
	ret = vpbe_get_mode_info(vpbe_dev,
				 cfg->outputs[index].default_mode, index);
	if (!ret) {
		struct osd_state *osd_device = vpbe_dev->osd_device;

		osd_device->ops.set_left_margin(osd_device,
			vpbe_dev->current_timings.left_margin);
		osd_device->ops.set_top_margin(osd_device,
		vpbe_dev->current_timings.upper_margin);
		vpbe_dev->current_sd_index = sd_index;
		vpbe_dev->current_out_index = index;
	}
unlock:
	mutex_unlock(&vpbe_dev->lock);
	return ret;
}