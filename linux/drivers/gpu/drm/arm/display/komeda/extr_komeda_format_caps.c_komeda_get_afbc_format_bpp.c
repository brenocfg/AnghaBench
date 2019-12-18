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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct drm_format_info {int format; int* cpp; } ;

/* Variables and functions */
#define  DRM_FORMAT_YUV420_10BIT 129 
#define  DRM_FORMAT_YUV420_8BIT 128 

u32 komeda_get_afbc_format_bpp(const struct drm_format_info *info, u64 modifier)
{
	u32 bpp;

	switch (info->format) {
	case DRM_FORMAT_YUV420_8BIT:
		bpp = 12;
		break;
	case DRM_FORMAT_YUV420_10BIT:
		bpp = 15;
		break;
	default:
		bpp = info->cpp[0] * 8;
		break;
	}

	return bpp;
}