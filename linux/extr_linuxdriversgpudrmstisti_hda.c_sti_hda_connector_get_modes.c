#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sti_hda_connector {struct sti_hda* hda; } ;
struct sti_hda {int /*<<< orphan*/  drm_dev; } ;
struct drm_display_mode {int /*<<< orphan*/  type; int /*<<< orphan*/  vrefresh; } ;
struct drm_connector {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_MODE_TYPE_PREFERRED ; 
 struct drm_display_mode* drm_mode_duplicate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_vrefresh (struct drm_display_mode*) ; 
 TYPE_1__* hda_supported_modes ; 
 struct sti_hda_connector* to_sti_hda_connector (struct drm_connector*) ; 

__attribute__((used)) static int sti_hda_connector_get_modes(struct drm_connector *connector)
{
	unsigned int i;
	int count = 0;
	struct sti_hda_connector *hda_connector
		= to_sti_hda_connector(connector);
	struct sti_hda *hda = hda_connector->hda;

	DRM_DEBUG_DRIVER("\n");

	for (i = 0; i < ARRAY_SIZE(hda_supported_modes); i++) {
		struct drm_display_mode *mode =
			drm_mode_duplicate(hda->drm_dev,
					&hda_supported_modes[i].mode);
		if (!mode)
			continue;
		mode->vrefresh = drm_mode_vrefresh(mode);

		/* the first mode is the preferred mode */
		if (i == 0)
			mode->type |= DRM_MODE_TYPE_PREFERRED;

		drm_mode_probed_add(connector, mode);
		count++;
	}

	return count;
}