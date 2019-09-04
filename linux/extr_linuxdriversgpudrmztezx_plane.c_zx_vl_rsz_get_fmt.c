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
 int RSZ_VL_FMT_YCBCR420 ; 
 int RSZ_VL_FMT_YCBCR422 ; 
 int RSZ_VL_FMT_YCBCR444 ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 

__attribute__((used)) static int zx_vl_rsz_get_fmt(uint32_t format)
{
	switch (format) {
	case DRM_FORMAT_NV12:
	case DRM_FORMAT_YUV420:
		return RSZ_VL_FMT_YCBCR420;
	case DRM_FORMAT_YUYV:
	case DRM_FORMAT_YVYU:
	case DRM_FORMAT_UYVY:
	case DRM_FORMAT_VYUY:
		return RSZ_VL_FMT_YCBCR422;
	case DRM_FORMAT_YUV444:
		return RSZ_VL_FMT_YCBCR444;
	default:
		WARN_ONCE(1, "invalid pixel format %d\n", format);
		return -EINVAL;
	}
}