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
struct tv_mode {int /*<<< orphan*/  name; } ;
struct drm_display_mode {int /*<<< orphan*/  name; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct tv_mode*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 struct drm_display_mode* drm_mode_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4i_tv_mode_to_drm_mode (struct tv_mode const*,struct drm_display_mode*) ; 
 struct tv_mode* tv_modes ; 

__attribute__((used)) static int sun4i_tv_comp_get_modes(struct drm_connector *connector)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(tv_modes); i++) {
		struct drm_display_mode *mode;
		const struct tv_mode *tv_mode = &tv_modes[i];

		mode = drm_mode_create(connector->dev);
		if (!mode) {
			DRM_ERROR("Failed to create a new display mode\n");
			return 0;
		}

		strcpy(mode->name, tv_mode->name);

		sun4i_tv_mode_to_drm_mode(tv_mode, mode);
		drm_mode_probed_add(connector, mode);
	}

	return i;
}