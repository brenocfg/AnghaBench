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
typedef  int uint32_t ;
typedef  enum vop_data_format { ____Placeholder_vop_data_format } vop_data_format ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
#define  DRM_FORMAT_ABGR8888 138 
#define  DRM_FORMAT_ARGB8888 137 
#define  DRM_FORMAT_BGR565 136 
#define  DRM_FORMAT_BGR888 135 
#define  DRM_FORMAT_NV12 134 
#define  DRM_FORMAT_NV16 133 
#define  DRM_FORMAT_NV24 132 
#define  DRM_FORMAT_RGB565 131 
#define  DRM_FORMAT_RGB888 130 
#define  DRM_FORMAT_XBGR8888 129 
#define  DRM_FORMAT_XRGB8888 128 
 int EINVAL ; 
 int VOP_FMT_ARGB8888 ; 
 int VOP_FMT_RGB565 ; 
 int VOP_FMT_RGB888 ; 
 int VOP_FMT_YUV420SP ; 
 int VOP_FMT_YUV422SP ; 
 int VOP_FMT_YUV444SP ; 

__attribute__((used)) static enum vop_data_format vop_convert_format(uint32_t format)
{
	switch (format) {
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_ABGR8888:
		return VOP_FMT_ARGB8888;
	case DRM_FORMAT_RGB888:
	case DRM_FORMAT_BGR888:
		return VOP_FMT_RGB888;
	case DRM_FORMAT_RGB565:
	case DRM_FORMAT_BGR565:
		return VOP_FMT_RGB565;
	case DRM_FORMAT_NV12:
		return VOP_FMT_YUV420SP;
	case DRM_FORMAT_NV16:
		return VOP_FMT_YUV422SP;
	case DRM_FORMAT_NV24:
		return VOP_FMT_YUV444SP;
	default:
		DRM_ERROR("unsupported format[%08x]\n", format);
		return -EINVAL;
	}
}