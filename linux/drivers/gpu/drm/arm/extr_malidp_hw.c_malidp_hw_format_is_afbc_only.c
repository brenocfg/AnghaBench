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
#define  DRM_FORMAT_VUY101010 131 
#define  DRM_FORMAT_VUY888 130 
#define  DRM_FORMAT_YUV420_10BIT 129 
#define  DRM_FORMAT_YUV420_8BIT 128 

bool malidp_hw_format_is_afbc_only(u32 format)
{
	switch (format) {
	case DRM_FORMAT_VUY888:
	case DRM_FORMAT_VUY101010:
	case DRM_FORMAT_YUV420_8BIT:
	case DRM_FORMAT_YUV420_10BIT:
		return true;
	default:
		return false;
	}
}