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
struct tv_mode {scalar_t__ vdisplay; int /*<<< orphan*/  name; } ;
struct drm_display_mode {scalar_t__ vdisplay; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct tv_mode*) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tv_mode* tv_modes ; 

__attribute__((used)) static const struct tv_mode *sun4i_tv_find_tv_by_mode(const struct drm_display_mode *mode)
{
	int i;

	/* First try to identify the mode by name */
	for (i = 0; i < ARRAY_SIZE(tv_modes); i++) {
		const struct tv_mode *tv_mode = &tv_modes[i];

		DRM_DEBUG_DRIVER("Comparing mode %s vs %s",
				 mode->name, tv_mode->name);

		if (!strcmp(mode->name, tv_mode->name))
			return tv_mode;
	}

	/* Then by number of lines */
	for (i = 0; i < ARRAY_SIZE(tv_modes); i++) {
		const struct tv_mode *tv_mode = &tv_modes[i];

		DRM_DEBUG_DRIVER("Comparing mode %s vs %s (X: %d vs %d)",
				 mode->name, tv_mode->name,
				 mode->vdisplay, tv_mode->vdisplay);

		if (mode->vdisplay == tv_mode->vdisplay)
			return tv_mode;
	}

	return NULL;
}