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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
#define  DRM_FORMAT_ABGR8888 129 
#define  DRM_FORMAT_ARGB8888 128 
 int /*<<< orphan*/  PLANE_CTL_ALPHA_DISABLE ; 
 int /*<<< orphan*/  PLANE_CTL_ALPHA_SW_PREMULTIPLY ; 

__attribute__((used)) static u32 skl_plane_ctl_alpha(uint32_t pixel_format)
{
	switch (pixel_format) {
	case DRM_FORMAT_ABGR8888:
	case DRM_FORMAT_ARGB8888:
		return PLANE_CTL_ALPHA_SW_PREMULTIPLY;
	default:
		return PLANE_CTL_ALPHA_DISABLE;
	}
}