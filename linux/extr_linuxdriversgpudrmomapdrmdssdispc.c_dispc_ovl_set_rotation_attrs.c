#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct dispc_device {int dummy; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;
typedef  enum omap_dss_rotation_type { ____Placeholder_omap_dss_rotation_type } omap_dss_rotation_type ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
 scalar_t__ DRM_FORMAT_NV12 ; 
 scalar_t__ DRM_FORMAT_UYVY ; 
 scalar_t__ DRM_FORMAT_YUYV ; 
 int DRM_MODE_REFLECT_X ; 
#define  DRM_MODE_ROTATE_0 131 
#define  DRM_MODE_ROTATE_180 130 
#define  DRM_MODE_ROTATE_270 129 
#define  DRM_MODE_ROTATE_90 128 
 int DRM_MODE_ROTATE_MASK ; 
 int /*<<< orphan*/  FEAT_ROWREPEATENABLE ; 
 int OMAP_DSS_ROT_TILER ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dispc_device*,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ dispc_has_feature (struct dispc_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ dispc_ovl_color_mode_supported (struct dispc_device*,int,scalar_t__) ; 
 scalar_t__ drm_rotation_90_or_270 (int) ; 

__attribute__((used)) static void dispc_ovl_set_rotation_attrs(struct dispc_device *dispc,
					 enum omap_plane_id plane, u8 rotation,
					 enum omap_dss_rotation_type rotation_type,
					 u32 fourcc)
{
	bool row_repeat = false;
	int vidrot = 0;

	/* Note: DSS HW rotates clockwise, DRM_MODE_ROTATE_* counter-clockwise */
	if (fourcc == DRM_FORMAT_YUYV || fourcc == DRM_FORMAT_UYVY) {

		if (rotation & DRM_MODE_REFLECT_X) {
			switch (rotation & DRM_MODE_ROTATE_MASK) {
			case DRM_MODE_ROTATE_0:
				vidrot = 2;
				break;
			case DRM_MODE_ROTATE_90:
				vidrot = 1;
				break;
			case DRM_MODE_ROTATE_180:
				vidrot = 0;
				break;
			case DRM_MODE_ROTATE_270:
				vidrot = 3;
				break;
			}
		} else {
			switch (rotation & DRM_MODE_ROTATE_MASK) {
			case DRM_MODE_ROTATE_0:
				vidrot = 0;
				break;
			case DRM_MODE_ROTATE_90:
				vidrot = 3;
				break;
			case DRM_MODE_ROTATE_180:
				vidrot = 2;
				break;
			case DRM_MODE_ROTATE_270:
				vidrot = 1;
				break;
			}
		}

		if (drm_rotation_90_or_270(rotation))
			row_repeat = true;
		else
			row_repeat = false;
	}

	/*
	 * OMAP4/5 Errata i631:
	 * NV12 in 1D mode must use ROTATION=1. Otherwise DSS will fetch extra
	 * rows beyond the framebuffer, which may cause OCP error.
	 */
	if (fourcc == DRM_FORMAT_NV12 && rotation_type != OMAP_DSS_ROT_TILER)
		vidrot = 1;

	REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), vidrot, 13, 12);
	if (dispc_has_feature(dispc, FEAT_ROWREPEATENABLE))
		REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane),
			row_repeat ? 1 : 0, 18, 18);

	if (dispc_ovl_color_mode_supported(dispc, plane, DRM_FORMAT_NV12)) {
		bool doublestride =
			fourcc == DRM_FORMAT_NV12 &&
			rotation_type == OMAP_DSS_ROT_TILER &&
			!drm_rotation_90_or_270(rotation);

		/* DOUBLESTRIDE */
		REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane),
			    doublestride, 22, 22);
	}
}