#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mipi_dbi_dev {int /*<<< orphan*/  mode; } ;
struct drm_display_mode {char* name; int /*<<< orphan*/  height_mm; scalar_t__ width_mm; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  height_mm; scalar_t__ width_mm; } ;
struct drm_connector {TYPE_1__ display_info; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_TYPE_PREFERRED ; 
 struct drm_display_mode* drm_mode_duplicate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 
 struct mipi_dbi_dev* drm_to_mipi_dbi_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mipi_dbi_connector_get_modes(struct drm_connector *connector)
{
	struct mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(connector->dev);
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &dbidev->mode);
	if (!mode) {
		DRM_ERROR("Failed to duplicate mode\n");
		return 0;
	}

	if (mode->name[0] == '\0')
		drm_mode_set_name(mode);

	mode->type |= DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	if (mode->width_mm) {
		connector->display_info.width_mm = mode->width_mm;
		connector->display_info.height_mm = mode->height_mm;
	}

	return 1;
}