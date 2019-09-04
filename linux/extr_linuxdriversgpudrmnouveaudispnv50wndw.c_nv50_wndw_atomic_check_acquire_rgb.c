#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int format; scalar_t__ colorspace; } ;
struct TYPE_7__ {TYPE_2__* fb; } ;
struct nv50_wndw_atom {TYPE_4__ image; TYPE_3__ state; } ;
struct TYPE_6__ {TYPE_1__* format; } ;
struct TYPE_5__ {int format; } ;

/* Variables and functions */
#define  DRM_FORMAT_ABGR2101010 139 
#define  DRM_FORMAT_ABGR8888 138 
#define  DRM_FORMAT_ARGB1555 137 
#define  DRM_FORMAT_ARGB2101010 136 
#define  DRM_FORMAT_ARGB8888 135 
#define  DRM_FORMAT_C8 134 
#define  DRM_FORMAT_RGB565 133 
#define  DRM_FORMAT_XBGR2101010 132 
#define  DRM_FORMAT_XBGR8888 131 
#define  DRM_FORMAT_XRGB1555 130 
#define  DRM_FORMAT_XRGB2101010 129 
#define  DRM_FORMAT_XRGB8888 128 
 int EINVAL ; 

__attribute__((used)) static int
nv50_wndw_atomic_check_acquire_rgb(struct nv50_wndw_atom *asyw)
{
	switch (asyw->state.fb->format->format) {
	case DRM_FORMAT_C8         : asyw->image.format = 0x1e; break;
	case DRM_FORMAT_XRGB8888   :
	case DRM_FORMAT_ARGB8888   : asyw->image.format = 0xcf; break;
	case DRM_FORMAT_RGB565     : asyw->image.format = 0xe8; break;
	case DRM_FORMAT_XRGB1555   :
	case DRM_FORMAT_ARGB1555   : asyw->image.format = 0xe9; break;
	case DRM_FORMAT_XBGR2101010:
	case DRM_FORMAT_ABGR2101010: asyw->image.format = 0xd1; break;
	case DRM_FORMAT_XBGR8888   :
	case DRM_FORMAT_ABGR8888   : asyw->image.format = 0xd5; break;
	case DRM_FORMAT_XRGB2101010:
	case DRM_FORMAT_ARGB2101010: asyw->image.format = 0xdf; break;
	default:
		return -EINVAL;
	}
	asyw->image.colorspace = 0;
	return 0;
}