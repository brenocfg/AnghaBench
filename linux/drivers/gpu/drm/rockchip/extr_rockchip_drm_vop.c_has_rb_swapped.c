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
#define  DRM_FORMAT_ABGR8888 131 
#define  DRM_FORMAT_BGR565 130 
#define  DRM_FORMAT_BGR888 129 
#define  DRM_FORMAT_XBGR8888 128 

__attribute__((used)) static bool has_rb_swapped(uint32_t format)
{
	switch (format) {
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_ABGR8888:
	case DRM_FORMAT_BGR888:
	case DRM_FORMAT_BGR565:
		return true;
	default:
		return false;
	}
}