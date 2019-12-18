#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_dv_timings {int dummy; } ;
struct vpbe_enc_mode_info {int timings_type; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  left_margin; struct v4l2_dv_timings dv_timings; int /*<<< orphan*/  std_id; int /*<<< orphan*/  name; } ;
struct vpbe_device {int current_out_index; int /*<<< orphan*/  lock; struct vpbe_enc_mode_info current_timings; struct osd_state* osd_device; struct vpbe_config* cfg; } ;
struct vpbe_config {TYPE_1__* outputs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_top_margin ) (struct osd_state*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_left_margin ) (struct osd_state*,int /*<<< orphan*/ ) ;} ;
struct osd_state {TYPE_2__ ops; } ;
struct TYPE_3__ {int num_modes; struct vpbe_enc_mode_info* modes; } ;

/* Variables and functions */
 int EINVAL ; 
 int VPBE_ENC_DV_TIMINGS ; 
 int VPBE_ENC_STD ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct osd_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct osd_state*,int /*<<< orphan*/ ) ; 
 int vpbe_s_dv_timings (struct vpbe_device*,struct v4l2_dv_timings*) ; 
 int vpbe_s_std (struct vpbe_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpbe_set_mode(struct vpbe_device *vpbe_dev,
			 struct vpbe_enc_mode_info *mode_info)
{
	struct vpbe_enc_mode_info *preset_mode = NULL;
	struct vpbe_config *cfg = vpbe_dev->cfg;
	struct v4l2_dv_timings dv_timings;
	struct osd_state *osd_device;
	int out_index = vpbe_dev->current_out_index;
	int i;

	if (!mode_info || !mode_info->name)
		return -EINVAL;

	for (i = 0; i < cfg->outputs[out_index].num_modes; i++) {
		if (!strcmp(mode_info->name,
		     cfg->outputs[out_index].modes[i].name)) {
			preset_mode = &cfg->outputs[out_index].modes[i];
			/*
			 * it may be one of the 3 timings type. Check and
			 * invoke right API
			 */
			if (preset_mode->timings_type & VPBE_ENC_STD)
				return vpbe_s_std(vpbe_dev,
						 preset_mode->std_id);
			if (preset_mode->timings_type &
						VPBE_ENC_DV_TIMINGS) {
				dv_timings =
					preset_mode->dv_timings;
				return vpbe_s_dv_timings(vpbe_dev, &dv_timings);
			}
		}
	}

	/* Only custom timing should reach here */
	if (!preset_mode)
		return -EINVAL;

	mutex_lock(&vpbe_dev->lock);

	osd_device = vpbe_dev->osd_device;
	vpbe_dev->current_timings = *preset_mode;
	osd_device->ops.set_left_margin(osd_device,
		vpbe_dev->current_timings.left_margin);
	osd_device->ops.set_top_margin(osd_device,
		vpbe_dev->current_timings.upper_margin);

	mutex_unlock(&vpbe_dev->lock);
	return 0;
}