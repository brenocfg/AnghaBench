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
typedef  int u32 ;
struct dispc_device {int dummy; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
#define  DRM_FORMAT_ARGB1555 142 
#define  DRM_FORMAT_ARGB4444 141 
#define  DRM_FORMAT_ARGB8888 140 
#define  DRM_FORMAT_NV12 139 
#define  DRM_FORMAT_RGB565 138 
#define  DRM_FORMAT_RGB888 137 
#define  DRM_FORMAT_RGBA4444 136 
#define  DRM_FORMAT_RGBA8888 135 
#define  DRM_FORMAT_RGBX4444 134 
#define  DRM_FORMAT_RGBX8888 133 
#define  DRM_FORMAT_UYVY 132 
#define  DRM_FORMAT_XRGB1555 131 
#define  DRM_FORMAT_XRGB4444 130 
#define  DRM_FORMAT_XRGB8888 129 
#define  DRM_FORMAT_YUYV 128 
 int OMAP_DSS_GFX ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dispc_device*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void dispc_ovl_set_color_mode(struct dispc_device *dispc,
				     enum omap_plane_id plane, u32 fourcc)
{
	u32 m = 0;
	if (plane != OMAP_DSS_GFX) {
		switch (fourcc) {
		case DRM_FORMAT_NV12:
			m = 0x0; break;
		case DRM_FORMAT_XRGB4444:
			m = 0x1; break;
		case DRM_FORMAT_RGBA4444:
			m = 0x2; break;
		case DRM_FORMAT_RGBX4444:
			m = 0x4; break;
		case DRM_FORMAT_ARGB4444:
			m = 0x5; break;
		case DRM_FORMAT_RGB565:
			m = 0x6; break;
		case DRM_FORMAT_ARGB1555:
			m = 0x7; break;
		case DRM_FORMAT_XRGB8888:
			m = 0x8; break;
		case DRM_FORMAT_RGB888:
			m = 0x9; break;
		case DRM_FORMAT_YUYV:
			m = 0xa; break;
		case DRM_FORMAT_UYVY:
			m = 0xb; break;
		case DRM_FORMAT_ARGB8888:
			m = 0xc; break;
		case DRM_FORMAT_RGBA8888:
			m = 0xd; break;
		case DRM_FORMAT_RGBX8888:
			m = 0xe; break;
		case DRM_FORMAT_XRGB1555:
			m = 0xf; break;
		default:
			BUG(); return;
		}
	} else {
		switch (fourcc) {
		case DRM_FORMAT_RGBX4444:
			m = 0x4; break;
		case DRM_FORMAT_ARGB4444:
			m = 0x5; break;
		case DRM_FORMAT_RGB565:
			m = 0x6; break;
		case DRM_FORMAT_ARGB1555:
			m = 0x7; break;
		case DRM_FORMAT_XRGB8888:
			m = 0x8; break;
		case DRM_FORMAT_RGB888:
			m = 0x9; break;
		case DRM_FORMAT_XRGB4444:
			m = 0xa; break;
		case DRM_FORMAT_RGBA4444:
			m = 0xb; break;
		case DRM_FORMAT_ARGB8888:
			m = 0xc; break;
		case DRM_FORMAT_RGBA8888:
			m = 0xd; break;
		case DRM_FORMAT_RGBX8888:
			m = 0xe; break;
		case DRM_FORMAT_XRGB1555:
			m = 0xf; break;
		default:
			BUG(); return;
		}
	}

	REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), m, 4, 1);
}