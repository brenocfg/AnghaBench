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
struct tv_mode {int nbr_end; int progressive; } ;
struct drm_display_mode {int vdisplay; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_TYPE_PREFERRED ; 

__attribute__((used)) static void
intel_tv_choose_preferred_modes(const struct tv_mode *tv_mode,
			       struct drm_display_mode *mode_ptr)
{
	if (tv_mode->nbr_end < 480 && mode_ptr->vdisplay == 480)
		mode_ptr->type |= DRM_MODE_TYPE_PREFERRED;
	else if (tv_mode->nbr_end > 480) {
		if (tv_mode->progressive == true && tv_mode->nbr_end < 720) {
			if (mode_ptr->vdisplay == 720)
				mode_ptr->type |= DRM_MODE_TYPE_PREFERRED;
		} else if (mode_ptr->vdisplay == 1080)
				mode_ptr->type |= DRM_MODE_TYPE_PREFERRED;
	}
}