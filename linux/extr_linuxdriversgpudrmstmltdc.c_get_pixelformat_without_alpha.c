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
#define  DRM_FORMAT_ARGB1555 133 
#define  DRM_FORMAT_ARGB4444 132 
#define  DRM_FORMAT_ARGB8888 131 
#define  DRM_FORMAT_RGBA4444 130 
#define  DRM_FORMAT_RGBA5551 129 
#define  DRM_FORMAT_RGBA8888 128 
 int DRM_FORMAT_RGBX4444 ; 
 int DRM_FORMAT_RGBX5551 ; 
 int DRM_FORMAT_RGBX8888 ; 
 int DRM_FORMAT_XRGB1555 ; 
 int DRM_FORMAT_XRGB4444 ; 
 int DRM_FORMAT_XRGB8888 ; 

__attribute__((used)) static inline u32 get_pixelformat_without_alpha(u32 drm)
{
	switch (drm) {
	case DRM_FORMAT_ARGB4444:
		return DRM_FORMAT_XRGB4444;
	case DRM_FORMAT_RGBA4444:
		return DRM_FORMAT_RGBX4444;
	case DRM_FORMAT_ARGB1555:
		return DRM_FORMAT_XRGB1555;
	case DRM_FORMAT_RGBA5551:
		return DRM_FORMAT_RGBX5551;
	case DRM_FORMAT_ARGB8888:
		return DRM_FORMAT_XRGB8888;
	case DRM_FORMAT_RGBA8888:
		return DRM_FORMAT_RGBX8888;
	default:
		return 0;
	}
}