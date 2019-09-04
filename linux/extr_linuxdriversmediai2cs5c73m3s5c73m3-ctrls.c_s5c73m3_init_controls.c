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
struct v4l2_ctrl_ops {int dummy; } ;
struct v4l2_ctrl_handler {int error; } ;
struct s5c73m3_ctrls {void* focus_auto; TYPE_1__* af_status; TYPE_3__* auto_iso; TYPE_3__* auto_exposure; void* aaa_lock; void* scene_mode; void* jpeg_quality; void* stabilization; void* wdr; void* colorfx; void* zoom; void* sharpness; void* saturation; void* contrast; void* iso; void* af_distance; void* af_stop; void* af_start; void* exposure_metering; void* exposure_bias; void* auto_wb; struct v4l2_ctrl_handler handler; } ;
struct TYPE_5__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct s5c73m3 {TYPE_2__ sensor_sd; struct s5c73m3_ctrls ctrls; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int V4L2_AUTO_FOCUS_RANGE_MACRO ; 
 int V4L2_AUTO_FOCUS_RANGE_NORMAL ; 
 int V4L2_AUTO_FOCUS_STATUS_BUSY ; 
 int V4L2_AUTO_FOCUS_STATUS_FAILED ; 
 int V4L2_AUTO_FOCUS_STATUS_IDLE ; 
 int V4L2_AUTO_FOCUS_STATUS_REACHED ; 
 int /*<<< orphan*/  V4L2_CID_3A_LOCK ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_EXPOSURE_BIAS ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_FOCUS_RANGE ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_FOCUS_START ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_FOCUS_STATUS ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_FOCUS_STOP ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_COLORFX ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE_AUTO ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE_METERING ; 
 int /*<<< orphan*/  V4L2_CID_FOCUS_AUTO ; 
 int /*<<< orphan*/  V4L2_CID_IMAGE_STABILIZATION ; 
 int /*<<< orphan*/  V4L2_CID_ISO_SENSITIVITY ; 
 int /*<<< orphan*/  V4L2_CID_ISO_SENSITIVITY_AUTO ; 
 int /*<<< orphan*/  V4L2_CID_JPEG_COMPRESSION_QUALITY ; 
 int /*<<< orphan*/  V4L2_CID_POWER_LINE_FREQUENCY ; 
 int V4L2_CID_POWER_LINE_FREQUENCY_AUTO ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int /*<<< orphan*/  V4L2_CID_SCENE_MODE ; 
 int /*<<< orphan*/  V4L2_CID_SHARPNESS ; 
 int /*<<< orphan*/  V4L2_CID_WIDE_DYNAMIC_RANGE ; 
 int /*<<< orphan*/  V4L2_CID_ZOOM_ABSOLUTE ; 
 int V4L2_COLORFX_AQUA ; 
 int V4L2_COLORFX_NONE ; 
 int V4L2_CTRL_FLAG_UPDATE ; 
 int V4L2_CTRL_FLAG_VOLATILE ; 
 int V4L2_EXPOSURE_AUTO ; 
 int V4L2_EXPOSURE_METERING_AVERAGE ; 
 int V4L2_ISO_SENSITIVITY_AUTO ; 
 int V4L2_SCENE_MODE_NONE ; 
 int V4L2_SCENE_MODE_TEXT ; 
 int V4L2_WHITE_BALANCE_AUTO ; 
 int /*<<< orphan*/  ev_bias_qmenu ; 
 int /*<<< orphan*/  iso_qmenu ; 
 struct v4l2_ctrl_ops s5c73m3_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_auto_cluster (int,TYPE_3__**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_cluster (int,void**) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 void* v4l2_ctrl_new_int_menu (struct v4l2_ctrl_handler*,struct v4l2_ctrl_ops const*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 void* v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,struct v4l2_ctrl_ops const*,int /*<<< orphan*/ ,int,int,int,int) ; 
 void* v4l2_ctrl_new_std_menu (struct v4l2_ctrl_handler*,struct v4l2_ctrl_ops const*,int /*<<< orphan*/ ,int,int,int) ; 

int s5c73m3_init_controls(struct s5c73m3 *state)
{
	const struct v4l2_ctrl_ops *ops = &s5c73m3_ctrl_ops;
	struct s5c73m3_ctrls *ctrls = &state->ctrls;
	struct v4l2_ctrl_handler *hdl = &ctrls->handler;

	int ret = v4l2_ctrl_handler_init(hdl, 22);
	if (ret)
		return ret;

	/* White balance */
	ctrls->auto_wb = v4l2_ctrl_new_std_menu(hdl, ops,
			V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE,
			9, ~0x15e, V4L2_WHITE_BALANCE_AUTO);

	/* Exposure (only automatic exposure) */
	ctrls->auto_exposure = v4l2_ctrl_new_std_menu(hdl, ops,
			V4L2_CID_EXPOSURE_AUTO, 0, ~0x01, V4L2_EXPOSURE_AUTO);

	ctrls->exposure_bias = v4l2_ctrl_new_int_menu(hdl, ops,
			V4L2_CID_AUTO_EXPOSURE_BIAS,
			ARRAY_SIZE(ev_bias_qmenu) - 1,
			ARRAY_SIZE(ev_bias_qmenu)/2 - 1,
			ev_bias_qmenu);

	ctrls->exposure_metering = v4l2_ctrl_new_std_menu(hdl, ops,
			V4L2_CID_EXPOSURE_METERING,
			2, ~0x7, V4L2_EXPOSURE_METERING_AVERAGE);

	/* Auto focus */
	ctrls->focus_auto = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_FOCUS_AUTO, 0, 1, 1, 0);

	ctrls->af_start = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_AUTO_FOCUS_START, 0, 1, 1, 0);

	ctrls->af_stop = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_AUTO_FOCUS_STOP, 0, 1, 1, 0);

	ctrls->af_status = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_AUTO_FOCUS_STATUS, 0,
			(V4L2_AUTO_FOCUS_STATUS_BUSY |
			 V4L2_AUTO_FOCUS_STATUS_REACHED |
			 V4L2_AUTO_FOCUS_STATUS_FAILED),
			0, V4L2_AUTO_FOCUS_STATUS_IDLE);

	ctrls->af_distance = v4l2_ctrl_new_std_menu(hdl, ops,
			V4L2_CID_AUTO_FOCUS_RANGE,
			V4L2_AUTO_FOCUS_RANGE_MACRO,
			~(1 << V4L2_AUTO_FOCUS_RANGE_NORMAL |
			  1 << V4L2_AUTO_FOCUS_RANGE_MACRO),
			V4L2_AUTO_FOCUS_RANGE_NORMAL);
	/* ISO sensitivity */
	ctrls->auto_iso = v4l2_ctrl_new_std_menu(hdl, ops,
			V4L2_CID_ISO_SENSITIVITY_AUTO, 1, 0,
			V4L2_ISO_SENSITIVITY_AUTO);

	ctrls->iso = v4l2_ctrl_new_int_menu(hdl, ops,
			V4L2_CID_ISO_SENSITIVITY, ARRAY_SIZE(iso_qmenu) - 1,
			ARRAY_SIZE(iso_qmenu)/2 - 1, iso_qmenu);

	ctrls->contrast = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_CONTRAST, -2, 2, 1, 0);

	ctrls->saturation = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_SATURATION, -2, 2, 1, 0);

	ctrls->sharpness = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_SHARPNESS, -2, 2, 1, 0);

	ctrls->zoom = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_ZOOM_ABSOLUTE, 0, 30, 1, 0);

	ctrls->colorfx = v4l2_ctrl_new_std_menu(hdl, ops, V4L2_CID_COLORFX,
			V4L2_COLORFX_AQUA, ~0x40f, V4L2_COLORFX_NONE);

	ctrls->wdr = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_WIDE_DYNAMIC_RANGE, 0, 1, 1, 0);

	ctrls->stabilization = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_IMAGE_STABILIZATION, 0, 1, 1, 0);

	v4l2_ctrl_new_std_menu(hdl, ops, V4L2_CID_POWER_LINE_FREQUENCY,
			       V4L2_CID_POWER_LINE_FREQUENCY_AUTO, 0,
			       V4L2_CID_POWER_LINE_FREQUENCY_AUTO);

	ctrls->jpeg_quality = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_JPEG_COMPRESSION_QUALITY, 1, 100, 1, 80);

	ctrls->scene_mode = v4l2_ctrl_new_std_menu(hdl, ops,
			V4L2_CID_SCENE_MODE, V4L2_SCENE_MODE_TEXT, ~0x3fff,
			V4L2_SCENE_MODE_NONE);

	ctrls->aaa_lock = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_3A_LOCK, 0, 0x7, 0, 0);

	if (hdl->error) {
		ret = hdl->error;
		v4l2_ctrl_handler_free(hdl);
		return ret;
	}

	v4l2_ctrl_auto_cluster(3, &ctrls->auto_exposure, 0, false);
	ctrls->auto_iso->flags |= V4L2_CTRL_FLAG_VOLATILE |
				V4L2_CTRL_FLAG_UPDATE;
	v4l2_ctrl_auto_cluster(2, &ctrls->auto_iso, 0, false);
	ctrls->af_status->flags |= V4L2_CTRL_FLAG_VOLATILE;
	v4l2_ctrl_cluster(6, &ctrls->focus_auto);

	state->sensor_sd.ctrl_handler = hdl;

	return 0;
}