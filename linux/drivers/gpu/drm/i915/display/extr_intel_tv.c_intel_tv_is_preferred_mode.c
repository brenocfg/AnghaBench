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
struct tv_mode {int dummy; } ;
struct drm_display_mode {int vdisplay; } ;

/* Variables and functions */
 int intel_tv_mode_vdisplay (struct tv_mode const*) ; 

__attribute__((used)) static bool
intel_tv_is_preferred_mode(const struct drm_display_mode *mode,
			   const struct tv_mode *tv_mode)
{
	int vdisplay = intel_tv_mode_vdisplay(tv_mode);

	/* prefer 480 line modes for all SD TV modes */
	if (vdisplay <= 576)
		vdisplay = 480;

	return vdisplay == mode->vdisplay;
}