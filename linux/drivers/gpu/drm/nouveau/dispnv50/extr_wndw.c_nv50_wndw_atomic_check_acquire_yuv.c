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
struct TYPE_8__ {int format; int colorspace; } ;
struct TYPE_7__ {TYPE_2__* fb; } ;
struct nv50_wndw_atom {TYPE_4__ image; TYPE_3__ state; } ;
struct TYPE_6__ {TYPE_1__* format; } ;
struct TYPE_5__ {int format; } ;

/* Variables and functions */
#define  DRM_FORMAT_UYVY 129 
#define  DRM_FORMAT_YUYV 128 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int
nv50_wndw_atomic_check_acquire_yuv(struct nv50_wndw_atom *asyw)
{
	switch (asyw->state.fb->format->format) {
	case DRM_FORMAT_YUYV: asyw->image.format = 0x28; break;
	case DRM_FORMAT_UYVY: asyw->image.format = 0x29; break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}
	asyw->image.colorspace = 1;
	return 0;
}