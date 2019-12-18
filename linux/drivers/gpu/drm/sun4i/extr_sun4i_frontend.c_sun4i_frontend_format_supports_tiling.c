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
#define  DRM_FORMAT_NV12 137 
#define  DRM_FORMAT_NV16 136 
#define  DRM_FORMAT_NV21 135 
#define  DRM_FORMAT_NV61 134 
#define  DRM_FORMAT_YUV411 133 
#define  DRM_FORMAT_YUV420 132 
#define  DRM_FORMAT_YUV422 131 
#define  DRM_FORMAT_YVU411 130 
#define  DRM_FORMAT_YVU420 129 
#define  DRM_FORMAT_YVU422 128 

__attribute__((used)) static bool sun4i_frontend_format_supports_tiling(uint32_t fmt)
{
	switch (fmt) {
	case DRM_FORMAT_NV12:
	case DRM_FORMAT_NV16:
	case DRM_FORMAT_NV21:
	case DRM_FORMAT_NV61:
	case DRM_FORMAT_YUV411:
	case DRM_FORMAT_YUV420:
	case DRM_FORMAT_YUV422:
	case DRM_FORMAT_YVU420:
	case DRM_FORMAT_YVU422:
	case DRM_FORMAT_YVU411:
		return true;

	default:
		return false;
	}
}