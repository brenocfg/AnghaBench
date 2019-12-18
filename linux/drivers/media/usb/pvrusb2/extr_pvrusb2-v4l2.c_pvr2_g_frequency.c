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
struct v4l2_tuner {int capability; } ;
struct v4l2_frequency {int frequency; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__* mc_head; } ;
struct pvr2_v4l2_fh {TYPE_2__ channel; } ;
struct pvr2_hdw {int dummy; } ;
struct file {struct pvr2_v4l2_fh* private_data; } ;
struct TYPE_3__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_CID_FREQUENCY ; 
 int /*<<< orphan*/  PVR2_CID_INPUT ; 
 int PVR2_CVAL_INPUT_RADIO ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int V4L2_TUNER_CAP_LOW ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int pvr2_ctrl_get_value (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pvr2_hdw_get_ctrl_by_id (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 
 int pvr2_hdw_get_tuner_status (struct pvr2_hdw*,struct v4l2_tuner*) ; 

__attribute__((used)) static int pvr2_g_frequency(struct file *file, void *priv, struct v4l2_frequency *vf)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	int val = 0;
	int cur_input;
	struct v4l2_tuner vt;
	int ret;

	ret = pvr2_hdw_get_tuner_status(hdw, &vt);
	if (ret != 0)
		return ret;
	ret = pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_FREQUENCY),
			&val);
	if (ret != 0)
		return ret;
	pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_INPUT),
			&cur_input);
	if (cur_input == PVR2_CVAL_INPUT_RADIO)
		vf->type = V4L2_TUNER_RADIO;
	else
		vf->type = V4L2_TUNER_ANALOG_TV;
	if (vt.capability & V4L2_TUNER_CAP_LOW)
		val = (val * 2) / 125;
	else
		val /= 62500;
	vf->frequency = val;
	return 0;
}