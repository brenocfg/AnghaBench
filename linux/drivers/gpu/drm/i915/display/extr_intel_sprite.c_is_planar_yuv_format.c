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

/* Variables and functions */
#define  DRM_FORMAT_NV12 131 
#define  DRM_FORMAT_P010 130 
#define  DRM_FORMAT_P012 129 
#define  DRM_FORMAT_P016 128 

bool is_planar_yuv_format(u32 pixelformat)
{
	switch (pixelformat) {
	case DRM_FORMAT_NV12:
	case DRM_FORMAT_P010:
	case DRM_FORMAT_P012:
	case DRM_FORMAT_P016:
		return true;
	default:
		return false;
	}
}