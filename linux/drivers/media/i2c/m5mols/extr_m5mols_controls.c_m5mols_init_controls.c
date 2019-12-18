#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct v4l2_subdev {TYPE_2__* ctrl_handler; } ;
struct TYPE_10__ {int error; } ;
struct m5mols_info {TYPE_2__ handle; TYPE_7__* colorfx; TYPE_7__* auto_wb; TYPE_7__* auto_exposure; TYPE_1__* lock_3a; TYPE_7__* auto_iso; void* jpeg_quality; void* stabilization; void* wdr; void* zoom; void* saturation; void* iso; void* metering; void* exposure_bias; void* exposure; } ;
struct TYPE_11__ {int flags; } ;
struct TYPE_9__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_MAX_GAIN_MON ; 
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_MONITOR ; 
 int /*<<< orphan*/  REG_PARAMETER ; 
 int /*<<< orphan*/  REG_SAMSUNG_OPTICS ; 
 int /*<<< orphan*/  V4L2_CID_3A_LOCK ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_EXPOSURE_BIAS ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_COLORFX ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE_AUTO ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE_METERING ; 
 int /*<<< orphan*/  V4L2_CID_IMAGE_STABILIZATION ; 
 int /*<<< orphan*/  V4L2_CID_ISO_SENSITIVITY ; 
 int /*<<< orphan*/  V4L2_CID_ISO_SENSITIVITY_AUTO ; 
 int /*<<< orphan*/  V4L2_CID_JPEG_COMPRESSION_QUALITY ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int /*<<< orphan*/  V4L2_CID_WIDE_DYNAMIC_RANGE ; 
 int /*<<< orphan*/  V4L2_CID_ZOOM_ABSOLUTE ; 
 int V4L2_COLORFX_NONE ; 
 int V4L2_CTRL_FLAG_UPDATE ; 
 int V4L2_CTRL_FLAG_VOLATILE ; 
 int V4L2_EXPOSURE_AUTO ; 
 int V4L2_EXPOSURE_METERING_AVERAGE ; 
 int V4L2_WHITE_BALANCE_AUTO ; 
 int /*<<< orphan*/  ev_bias_qmenu ; 
 scalar_t__ is_manufacturer (struct m5mols_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iso_qmenu ; 
 int /*<<< orphan*/  m5mols_ctrl_ops ; 
 int m5mols_read_u16 (struct v4l2_subdev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  m5mols_set_ctrl_mode (TYPE_7__*,int /*<<< orphan*/ ) ; 
 struct m5mols_info* to_m5mols (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_auto_cluster (int,TYPE_7__**,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 void* v4l2_ctrl_new_int_menu (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 void* v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 void* v4l2_ctrl_new_std_menu (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*,int) ; 

int m5mols_init_controls(struct v4l2_subdev *sd)
{
	struct m5mols_info *info = to_m5mols(sd);
	u16 exposure_max;
	u16 zoom_step;
	int ret;

	/* Determine the firmware dependent control range and step values */
	ret = m5mols_read_u16(sd, AE_MAX_GAIN_MON, &exposure_max);
	if (ret < 0)
		return ret;

	zoom_step = is_manufacturer(info, REG_SAMSUNG_OPTICS) ? 31 : 1;
	v4l2_ctrl_handler_init(&info->handle, 20);

	info->auto_wb = v4l2_ctrl_new_std_menu(&info->handle,
			&m5mols_ctrl_ops, V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE,
			9, ~0x3fe, V4L2_WHITE_BALANCE_AUTO);

	/* Exposure control cluster */
	info->auto_exposure = v4l2_ctrl_new_std_menu(&info->handle,
			&m5mols_ctrl_ops, V4L2_CID_EXPOSURE_AUTO,
			1, ~0x03, V4L2_EXPOSURE_AUTO);

	info->exposure = v4l2_ctrl_new_std(&info->handle,
			&m5mols_ctrl_ops, V4L2_CID_EXPOSURE,
			0, exposure_max, 1, exposure_max / 2);

	info->exposure_bias = v4l2_ctrl_new_int_menu(&info->handle,
			&m5mols_ctrl_ops, V4L2_CID_AUTO_EXPOSURE_BIAS,
			ARRAY_SIZE(ev_bias_qmenu) - 1,
			ARRAY_SIZE(ev_bias_qmenu)/2 - 1,
			ev_bias_qmenu);

	info->metering = v4l2_ctrl_new_std_menu(&info->handle,
			&m5mols_ctrl_ops, V4L2_CID_EXPOSURE_METERING,
			2, ~0x7, V4L2_EXPOSURE_METERING_AVERAGE);

	/* ISO control cluster */
	info->auto_iso = v4l2_ctrl_new_std_menu(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_ISO_SENSITIVITY_AUTO, 1, ~0x03, 1);

	info->iso = v4l2_ctrl_new_int_menu(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_ISO_SENSITIVITY, ARRAY_SIZE(iso_qmenu) - 1,
			ARRAY_SIZE(iso_qmenu)/2 - 1, iso_qmenu);

	info->saturation = v4l2_ctrl_new_std(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_SATURATION, 1, 5, 1, 3);

	info->zoom = v4l2_ctrl_new_std(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_ZOOM_ABSOLUTE, 1, 70, zoom_step, 1);

	info->colorfx = v4l2_ctrl_new_std_menu(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_COLORFX, 4, 0, V4L2_COLORFX_NONE);

	info->wdr = v4l2_ctrl_new_std(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_WIDE_DYNAMIC_RANGE, 0, 1, 1, 0);

	info->stabilization = v4l2_ctrl_new_std(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_IMAGE_STABILIZATION, 0, 1, 1, 0);

	info->jpeg_quality = v4l2_ctrl_new_std(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_JPEG_COMPRESSION_QUALITY, 1, 100, 1, 80);

	info->lock_3a = v4l2_ctrl_new_std(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_3A_LOCK, 0, 0x7, 0, 0);

	if (info->handle.error) {
		int ret = info->handle.error;
		v4l2_err(sd, "Failed to initialize controls: %d\n", ret);
		v4l2_ctrl_handler_free(&info->handle);
		return ret;
	}

	v4l2_ctrl_auto_cluster(4, &info->auto_exposure, 1, false);
	info->auto_iso->flags |= V4L2_CTRL_FLAG_VOLATILE |
				V4L2_CTRL_FLAG_UPDATE;
	v4l2_ctrl_auto_cluster(2, &info->auto_iso, 0, false);

	info->lock_3a->flags |= V4L2_CTRL_FLAG_VOLATILE;

	m5mols_set_ctrl_mode(info->auto_exposure, REG_PARAMETER);
	m5mols_set_ctrl_mode(info->auto_wb, REG_PARAMETER);
	m5mols_set_ctrl_mode(info->colorfx, REG_MONITOR);

	sd->ctrl_handler = &info->handle;

	return 0;
}