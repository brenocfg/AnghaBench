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
struct mtk_disp_rdma {int dummy; } ;

/* Variables and functions */
#define  DRM_FORMAT_ABGR8888 141 
#define  DRM_FORMAT_ARGB8888 140 
#define  DRM_FORMAT_BGR565 139 
#define  DRM_FORMAT_BGR888 138 
#define  DRM_FORMAT_BGRA8888 137 
#define  DRM_FORMAT_BGRX8888 136 
#define  DRM_FORMAT_RGB565 135 
#define  DRM_FORMAT_RGB888 134 
#define  DRM_FORMAT_RGBA8888 133 
#define  DRM_FORMAT_RGBX8888 132 
#define  DRM_FORMAT_UYVY 131 
#define  DRM_FORMAT_XBGR8888 130 
#define  DRM_FORMAT_XRGB8888 129 
#define  DRM_FORMAT_YUYV 128 
 unsigned int MEM_MODE_INPUT_FORMAT_ARGB8888 ; 
 unsigned int MEM_MODE_INPUT_FORMAT_RGB565 ; 
 unsigned int MEM_MODE_INPUT_FORMAT_RGB888 ; 
 unsigned int MEM_MODE_INPUT_FORMAT_RGBA8888 ; 
 unsigned int MEM_MODE_INPUT_FORMAT_UYVY ; 
 unsigned int MEM_MODE_INPUT_FORMAT_YUYV ; 
 unsigned int MEM_MODE_INPUT_SWAP ; 

__attribute__((used)) static unsigned int rdma_fmt_convert(struct mtk_disp_rdma *rdma,
				     unsigned int fmt)
{
	/* The return value in switch "MEM_MODE_INPUT_FORMAT_XXX"
	 * is defined in mediatek HW data sheet.
	 * The alphabet order in XXX is no relation to data
	 * arrangement in memory.
	 */
	switch (fmt) {
	default:
	case DRM_FORMAT_RGB565:
		return MEM_MODE_INPUT_FORMAT_RGB565;
	case DRM_FORMAT_BGR565:
		return MEM_MODE_INPUT_FORMAT_RGB565 | MEM_MODE_INPUT_SWAP;
	case DRM_FORMAT_RGB888:
		return MEM_MODE_INPUT_FORMAT_RGB888;
	case DRM_FORMAT_BGR888:
		return MEM_MODE_INPUT_FORMAT_RGB888 | MEM_MODE_INPUT_SWAP;
	case DRM_FORMAT_RGBX8888:
	case DRM_FORMAT_RGBA8888:
		return MEM_MODE_INPUT_FORMAT_ARGB8888;
	case DRM_FORMAT_BGRX8888:
	case DRM_FORMAT_BGRA8888:
		return MEM_MODE_INPUT_FORMAT_ARGB8888 | MEM_MODE_INPUT_SWAP;
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_ARGB8888:
		return MEM_MODE_INPUT_FORMAT_RGBA8888;
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_ABGR8888:
		return MEM_MODE_INPUT_FORMAT_RGBA8888 | MEM_MODE_INPUT_SWAP;
	case DRM_FORMAT_UYVY:
		return MEM_MODE_INPUT_FORMAT_UYVY;
	case DRM_FORMAT_YUYV:
		return MEM_MODE_INPUT_FORMAT_YUYV;
	}
}