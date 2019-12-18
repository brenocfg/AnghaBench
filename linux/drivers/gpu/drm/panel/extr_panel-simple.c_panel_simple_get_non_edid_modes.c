#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int type; } ;
struct TYPE_6__ {struct drm_device* drm; struct drm_connector* connector; } ;
struct panel_simple {TYPE_3__* desc; TYPE_4__ override_mode; TYPE_1__ base; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  bus_flags; int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; int /*<<< orphan*/  bpc; } ;
struct drm_connector {TYPE_5__ display_info; } ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {int /*<<< orphan*/  bus_flags; int /*<<< orphan*/  bus_format; TYPE_2__ size; int /*<<< orphan*/  bpc; scalar_t__ num_modes; scalar_t__ num_timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_display_info_set_bus_formats (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 struct drm_display_mode* drm_mode_duplicate (struct drm_device*,TYPE_4__*) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 unsigned int panel_simple_get_display_modes (struct panel_simple*) ; 
 unsigned int panel_simple_get_timings_modes (struct panel_simple*) ; 

__attribute__((used)) static int panel_simple_get_non_edid_modes(struct panel_simple *panel)
{
	struct drm_connector *connector = panel->base.connector;
	struct drm_device *drm = panel->base.drm;
	struct drm_display_mode *mode;
	bool has_override = panel->override_mode.type;
	unsigned int num = 0;

	if (!panel->desc)
		return 0;

	if (has_override) {
		mode = drm_mode_duplicate(drm, &panel->override_mode);
		if (mode) {
			drm_mode_probed_add(connector, mode);
			num = 1;
		} else {
			dev_err(drm->dev, "failed to add override mode\n");
		}
	}

	/* Only add timings if override was not there or failed to validate */
	if (num == 0 && panel->desc->num_timings)
		num = panel_simple_get_timings_modes(panel);

	/*
	 * Only add fixed modes if timings/override added no mode.
	 *
	 * We should only ever have either the display timings specified
	 * or a fixed mode. Anything else is rather bogus.
	 */
	WARN_ON(panel->desc->num_timings && panel->desc->num_modes);
	if (num == 0)
		num = panel_simple_get_display_modes(panel);

	connector->display_info.bpc = panel->desc->bpc;
	connector->display_info.width_mm = panel->desc->size.width;
	connector->display_info.height_mm = panel->desc->size.height;
	if (panel->desc->bus_format)
		drm_display_info_set_bus_formats(&connector->display_info,
						 &panel->desc->bus_format, 1);
	connector->display_info.bus_flags = panel->desc->bus_flags;

	return num;
}