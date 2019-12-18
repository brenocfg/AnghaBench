#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_panel {int /*<<< orphan*/  drm; struct drm_connector* connector; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_4__ {int bus_flags; int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;
struct drm_connector {TYPE_1__ display_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;

/* Variables and functions */
 int DRM_BUS_FLAG_DE_HIGH ; 
 int DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE ; 
 int DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE ; 
 int ENOMEM ; 
 struct drm_display_mode* drm_mode_duplicate (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 
 TYPE_2__ td028ttec1_mode ; 

__attribute__((used)) static int td028ttec1_get_modes(struct drm_panel *panel)
{
	struct drm_connector *connector = panel->connector;
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(panel->drm, &td028ttec1_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = td028ttec1_mode.width_mm;
	connector->display_info.height_mm = td028ttec1_mode.height_mm;
	/*
	 * FIXME: According to the datasheet sync signals are sampled on the
	 * rising edge of the clock, but the code running on the OpenMoko Neo
	 * FreeRunner and Neo 1973 indicates sampling on the falling edge. This
	 * should be tested on a real device.
	 */
	connector->display_info.bus_flags = DRM_BUS_FLAG_DE_HIGH
					  | DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE
					  | DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE;

	return 1;
}