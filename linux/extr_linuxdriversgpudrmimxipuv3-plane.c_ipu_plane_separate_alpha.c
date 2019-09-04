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
struct TYPE_8__ {TYPE_3__* state; } ;
struct ipu_plane {TYPE_4__ base; } ;
struct TYPE_7__ {TYPE_2__* fb; } ;
struct TYPE_6__ {TYPE_1__* format; } ;
struct TYPE_5__ {int format; } ;

/* Variables and functions */
#define  DRM_FORMAT_BGR565_A8 133 
#define  DRM_FORMAT_BGR888_A8 132 
#define  DRM_FORMAT_BGRX8888_A8 131 
#define  DRM_FORMAT_RGB565_A8 130 
#define  DRM_FORMAT_RGB888_A8 129 
#define  DRM_FORMAT_RGBX8888_A8 128 

__attribute__((used)) static bool ipu_plane_separate_alpha(struct ipu_plane *ipu_plane)
{
	switch (ipu_plane->base.state->fb->format->format) {
	case DRM_FORMAT_RGB565_A8:
	case DRM_FORMAT_BGR565_A8:
	case DRM_FORMAT_RGB888_A8:
	case DRM_FORMAT_BGR888_A8:
	case DRM_FORMAT_RGBX8888_A8:
	case DRM_FORMAT_BGRX8888_A8:
		return true;
	default:
		return false;
	}
}