#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_dv_timings {int dummy; } ;
struct TYPE_6__ {int timings_type; struct v4l2_dv_timings dv_timings; } ;
struct vpbe_device {int current_out_index; TYPE_3__ current_timings; struct vpbe_config* cfg; } ;
struct vpbe_config {TYPE_2__* outputs; } ;
struct TYPE_4__ {int capabilities; } ;
struct TYPE_5__ {TYPE_1__ output; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int V4L2_OUT_CAP_DV_TIMINGS ; 
 int VPBE_ENC_DV_TIMINGS ; 

__attribute__((used)) static int vpbe_g_dv_timings(struct vpbe_device *vpbe_dev,
		     struct v4l2_dv_timings *dv_timings)
{
	struct vpbe_config *cfg = vpbe_dev->cfg;
	int out_index = vpbe_dev->current_out_index;

	if (!(cfg->outputs[out_index].output.capabilities &
		V4L2_OUT_CAP_DV_TIMINGS))
		return -ENODATA;

	if (vpbe_dev->current_timings.timings_type &
	  VPBE_ENC_DV_TIMINGS) {
		*dv_timings = vpbe_dev->current_timings.dv_timings;
		return 0;
	}

	return -EINVAL;
}