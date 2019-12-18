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

/* Variables and functions */
#define  DRM_FORMAT_NV12 134 
#define  DRM_FORMAT_UYVY 133 
#define  DRM_FORMAT_VYUY 132 
#define  DRM_FORMAT_YUV420 131 
#define  DRM_FORMAT_YUV444 130 
#define  DRM_FORMAT_YUYV 129 
#define  DRM_FORMAT_YVYU 128 
 int EINVAL ; 
 int VL_FMT_YUV420 ; 
 int VL_FMT_YUV422 ; 
 int VL_FMT_YUV444_8BIT ; 
 int VL_YUV420_PLANAR ; 
 int VL_YUV422_UYVY ; 
 int VL_YUV422_VYUY ; 
 int VL_YUV422_YUYV ; 
 int VL_YUV422_YVYU ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 

__attribute__((used)) static int zx_vl_get_fmt(uint32_t format)
{
	switch (format) {
	case DRM_FORMAT_NV12:
		return VL_FMT_YUV420;
	case DRM_FORMAT_YUV420:
		return VL_YUV420_PLANAR | VL_FMT_YUV420;
	case DRM_FORMAT_YUYV:
		return VL_YUV422_YUYV | VL_FMT_YUV422;
	case DRM_FORMAT_YVYU:
		return VL_YUV422_YVYU | VL_FMT_YUV422;
	case DRM_FORMAT_UYVY:
		return VL_YUV422_UYVY | VL_FMT_YUV422;
	case DRM_FORMAT_VYUY:
		return VL_YUV422_VYUY | VL_FMT_YUV422;
	case DRM_FORMAT_YUV444:
		return VL_FMT_YUV444_8BIT;
	default:
		WARN_ONCE(1, "invalid pixel format %d\n", format);
		return -EINVAL;
	}
}