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
struct TYPE_3__ {int capabilities; } ;
struct vpbe_output {int num_modes; TYPE_2__* modes; TYPE_1__ output; } ;
struct vpbe_device {int current_out_index; struct vpbe_config* cfg; } ;
struct vpbe_config {struct vpbe_output* outputs; } ;
struct v4l2_enum_dv_timings {int index; int /*<<< orphan*/  timings; } ;
struct TYPE_4__ {scalar_t__ timings_type; int /*<<< orphan*/  dv_timings; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int V4L2_OUT_CAP_DV_TIMINGS ; 
 scalar_t__ VPBE_ENC_DV_TIMINGS ; 

__attribute__((used)) static int vpbe_enum_dv_timings(struct vpbe_device *vpbe_dev,
			 struct v4l2_enum_dv_timings *timings)
{
	struct vpbe_config *cfg = vpbe_dev->cfg;
	int out_index = vpbe_dev->current_out_index;
	struct vpbe_output *output = &cfg->outputs[out_index];
	int j = 0;
	int i;

	if (!(output->output.capabilities & V4L2_OUT_CAP_DV_TIMINGS))
		return -ENODATA;

	for (i = 0; i < output->num_modes; i++) {
		if (output->modes[i].timings_type == VPBE_ENC_DV_TIMINGS) {
			if (j == timings->index)
				break;
			j++;
		}
	}

	if (i == output->num_modes)
		return -EINVAL;
	timings->timings = output->modes[i].dv_timings;
	return 0;
}