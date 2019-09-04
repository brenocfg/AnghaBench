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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct TYPE_8__ {int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  left_margin; } ;
struct vpbe_device {int current_out_index; int current_sd_index; int /*<<< orphan*/  lock; TYPE_4__ current_timings; struct osd_state* osd_device; int /*<<< orphan*/ * encoders; struct vpbe_config* cfg; } ;
struct vpbe_config {TYPE_2__* outputs; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_top_margin ) (struct osd_state*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_left_margin ) (struct osd_state*,int /*<<< orphan*/ ) ;} ;
struct osd_state {TYPE_3__ ops; } ;
struct TYPE_5__ {int capabilities; } ;
struct TYPE_6__ {TYPE_1__ output; } ;

/* Variables and functions */
 int ENODATA ; 
 int V4L2_OUT_CAP_STD ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_std_output ; 
 int /*<<< orphan*/  stub1 (struct osd_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct osd_state*,int /*<<< orphan*/ ) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 
 int vpbe_get_std_info (struct vpbe_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpbe_s_std(struct vpbe_device *vpbe_dev, v4l2_std_id std_id)
{
	struct vpbe_config *cfg = vpbe_dev->cfg;
	int out_index = vpbe_dev->current_out_index;
	int sd_index = vpbe_dev->current_sd_index;
	int ret;

	if (!(cfg->outputs[out_index].output.capabilities &
		V4L2_OUT_CAP_STD))
		return -ENODATA;

	ret = vpbe_get_std_info(vpbe_dev, std_id);
	if (ret)
		return ret;

	mutex_lock(&vpbe_dev->lock);

	ret = v4l2_subdev_call(vpbe_dev->encoders[sd_index], video,
			       s_std_output, std_id);
	/* set the lcd controller output for the given mode */
	if (!ret) {
		struct osd_state *osd_device = vpbe_dev->osd_device;

		osd_device->ops.set_left_margin(osd_device,
		vpbe_dev->current_timings.left_margin);
		osd_device->ops.set_top_margin(osd_device,
		vpbe_dev->current_timings.upper_margin);
	}
	mutex_unlock(&vpbe_dev->lock);

	return ret;
}