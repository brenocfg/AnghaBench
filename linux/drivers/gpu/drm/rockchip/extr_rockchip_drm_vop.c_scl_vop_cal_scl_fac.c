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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct vop_win_data {TYPE_2__* phy; } ;
struct vop {int /*<<< orphan*/  dev; } ;
struct drm_format_info {int hsub; int vsub; scalar_t__ is_yuv; } ;
struct TYPE_4__ {TYPE_1__* scl; } ;
struct TYPE_3__ {int /*<<< orphan*/  ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ LB_RGB_2560X4 ; 
 scalar_t__ LB_RGB_3840X2 ; 
 scalar_t__ SCALE_DOWN ; 
 scalar_t__ SCALE_DOWN_BIL ; 
 scalar_t__ SCALE_NONE ; 
 scalar_t__ SCALE_UP_BIC ; 
 scalar_t__ SCALE_UP_BIL ; 
 int /*<<< orphan*/  VOP_SCL_SET (struct vop*,struct vop_win_data const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VOP_SCL_SET_EXT (struct vop*,struct vop_win_data const*,scalar_t__,scalar_t__) ; 
 scalar_t__ cbcr_hsd_mode ; 
 scalar_t__ cbcr_vsd_mode ; 
 scalar_t__ cbcr_vsu_mode ; 
 int /*<<< orphan*/  scale_cbcr_x ; 
 int /*<<< orphan*/  scale_cbcr_y ; 
 int /*<<< orphan*/  scale_yrgb_x ; 
 int /*<<< orphan*/  scale_yrgb_y ; 
 int scl_cal_scale2 (scalar_t__,int) ; 
 scalar_t__ scl_get_scl_mode (scalar_t__,int) ; 
 scalar_t__ scl_vop_cal_lb_mode (int,int) ; 
 int scl_vop_cal_scale (scalar_t__,scalar_t__,int,int,scalar_t__,int*) ; 
 scalar_t__ vsd_cbcr_gt2 ; 
 scalar_t__ vsd_cbcr_gt4 ; 
 scalar_t__ vsd_yrgb_gt2 ; 
 scalar_t__ vsd_yrgb_gt4 ; 
 scalar_t__ yrgb_hsd_mode ; 
 scalar_t__ yrgb_vsd_mode ; 
 scalar_t__ yrgb_vsu_mode ; 

__attribute__((used)) static void scl_vop_cal_scl_fac(struct vop *vop, const struct vop_win_data *win,
			     uint32_t src_w, uint32_t src_h, uint32_t dst_w,
			     uint32_t dst_h, const struct drm_format_info *info)
{
	uint16_t yrgb_hor_scl_mode, yrgb_ver_scl_mode;
	uint16_t cbcr_hor_scl_mode = SCALE_NONE;
	uint16_t cbcr_ver_scl_mode = SCALE_NONE;
	bool is_yuv = false;
	uint16_t cbcr_src_w = src_w / info->hsub;
	uint16_t cbcr_src_h = src_h / info->vsub;
	uint16_t vsu_mode;
	uint16_t lb_mode;
	uint32_t val;
	int vskiplines;

	if (info->is_yuv)
		is_yuv = true;

	if (dst_w > 3840) {
		DRM_DEV_ERROR(vop->dev, "Maximum dst width (3840) exceeded\n");
		return;
	}

	if (!win->phy->scl->ext) {
		VOP_SCL_SET(vop, win, scale_yrgb_x,
			    scl_cal_scale2(src_w, dst_w));
		VOP_SCL_SET(vop, win, scale_yrgb_y,
			    scl_cal_scale2(src_h, dst_h));
		if (is_yuv) {
			VOP_SCL_SET(vop, win, scale_cbcr_x,
				    scl_cal_scale2(cbcr_src_w, dst_w));
			VOP_SCL_SET(vop, win, scale_cbcr_y,
				    scl_cal_scale2(cbcr_src_h, dst_h));
		}
		return;
	}

	yrgb_hor_scl_mode = scl_get_scl_mode(src_w, dst_w);
	yrgb_ver_scl_mode = scl_get_scl_mode(src_h, dst_h);

	if (is_yuv) {
		cbcr_hor_scl_mode = scl_get_scl_mode(cbcr_src_w, dst_w);
		cbcr_ver_scl_mode = scl_get_scl_mode(cbcr_src_h, dst_h);
		if (cbcr_hor_scl_mode == SCALE_DOWN)
			lb_mode = scl_vop_cal_lb_mode(dst_w, true);
		else
			lb_mode = scl_vop_cal_lb_mode(cbcr_src_w, true);
	} else {
		if (yrgb_hor_scl_mode == SCALE_DOWN)
			lb_mode = scl_vop_cal_lb_mode(dst_w, false);
		else
			lb_mode = scl_vop_cal_lb_mode(src_w, false);
	}

	VOP_SCL_SET_EXT(vop, win, lb_mode, lb_mode);
	if (lb_mode == LB_RGB_3840X2) {
		if (yrgb_ver_scl_mode != SCALE_NONE) {
			DRM_DEV_ERROR(vop->dev, "not allow yrgb ver scale\n");
			return;
		}
		if (cbcr_ver_scl_mode != SCALE_NONE) {
			DRM_DEV_ERROR(vop->dev, "not allow cbcr ver scale\n");
			return;
		}
		vsu_mode = SCALE_UP_BIL;
	} else if (lb_mode == LB_RGB_2560X4) {
		vsu_mode = SCALE_UP_BIL;
	} else {
		vsu_mode = SCALE_UP_BIC;
	}

	val = scl_vop_cal_scale(yrgb_hor_scl_mode, src_w, dst_w,
				true, 0, NULL);
	VOP_SCL_SET(vop, win, scale_yrgb_x, val);
	val = scl_vop_cal_scale(yrgb_ver_scl_mode, src_h, dst_h,
				false, vsu_mode, &vskiplines);
	VOP_SCL_SET(vop, win, scale_yrgb_y, val);

	VOP_SCL_SET_EXT(vop, win, vsd_yrgb_gt4, vskiplines == 4);
	VOP_SCL_SET_EXT(vop, win, vsd_yrgb_gt2, vskiplines == 2);

	VOP_SCL_SET_EXT(vop, win, yrgb_hor_scl_mode, yrgb_hor_scl_mode);
	VOP_SCL_SET_EXT(vop, win, yrgb_ver_scl_mode, yrgb_ver_scl_mode);
	VOP_SCL_SET_EXT(vop, win, yrgb_hsd_mode, SCALE_DOWN_BIL);
	VOP_SCL_SET_EXT(vop, win, yrgb_vsd_mode, SCALE_DOWN_BIL);
	VOP_SCL_SET_EXT(vop, win, yrgb_vsu_mode, vsu_mode);
	if (is_yuv) {
		val = scl_vop_cal_scale(cbcr_hor_scl_mode, cbcr_src_w,
					dst_w, true, 0, NULL);
		VOP_SCL_SET(vop, win, scale_cbcr_x, val);
		val = scl_vop_cal_scale(cbcr_ver_scl_mode, cbcr_src_h,
					dst_h, false, vsu_mode, &vskiplines);
		VOP_SCL_SET(vop, win, scale_cbcr_y, val);

		VOP_SCL_SET_EXT(vop, win, vsd_cbcr_gt4, vskiplines == 4);
		VOP_SCL_SET_EXT(vop, win, vsd_cbcr_gt2, vskiplines == 2);
		VOP_SCL_SET_EXT(vop, win, cbcr_hor_scl_mode, cbcr_hor_scl_mode);
		VOP_SCL_SET_EXT(vop, win, cbcr_ver_scl_mode, cbcr_ver_scl_mode);
		VOP_SCL_SET_EXT(vop, win, cbcr_hsd_mode, SCALE_DOWN_BIL);
		VOP_SCL_SET_EXT(vop, win, cbcr_vsd_mode, SCALE_DOWN_BIL);
		VOP_SCL_SET_EXT(vop, win, cbcr_vsu_mode, vsu_mode);
	}
}