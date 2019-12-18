#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct edid {int extensions; } ;
struct TYPE_4__ {int /*<<< orphan*/  edid_property; int /*<<< orphan*/  non_desktop_property; } ;
struct drm_device {TYPE_2__ mode_config; } ;
struct TYPE_3__ {int /*<<< orphan*/  non_desktop; } ;
struct drm_connector {int /*<<< orphan*/  base; int /*<<< orphan*/  edid_blob_ptr; TYPE_1__ display_info; scalar_t__ override_edid; struct drm_device* dev; } ;

/* Variables and functions */
 int EDID_LENGTH ; 
 int /*<<< orphan*/  drm_add_display_info (struct drm_connector*,struct edid const*) ; 
 int drm_connector_set_tile_property (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_object_property_set_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_property_replace_global_blob (struct drm_device*,int /*<<< orphan*/ *,size_t,struct edid const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_reset_display_info (struct drm_connector*) ; 

int drm_connector_update_edid_property(struct drm_connector *connector,
				       const struct edid *edid)
{
	struct drm_device *dev = connector->dev;
	size_t size = 0;
	int ret;

	/* ignore requests to set edid when overridden */
	if (connector->override_edid)
		return 0;

	if (edid)
		size = EDID_LENGTH * (1 + edid->extensions);

	/* Set the display info, using edid if available, otherwise
	 * reseting the values to defaults. This duplicates the work
	 * done in drm_add_edid_modes, but that function is not
	 * consistently called before this one in all drivers and the
	 * computation is cheap enough that it seems better to
	 * duplicate it rather than attempt to ensure some arbitrary
	 * ordering of calls.
	 */
	if (edid)
		drm_add_display_info(connector, edid);
	else
		drm_reset_display_info(connector);

	drm_object_property_set_value(&connector->base,
				      dev->mode_config.non_desktop_property,
				      connector->display_info.non_desktop);

	ret = drm_property_replace_global_blob(dev,
					       &connector->edid_blob_ptr,
	                                       size,
	                                       edid,
	                                       &connector->base,
	                                       dev->mode_config.edid_property);
	if (ret)
		return ret;
	return drm_connector_set_tile_property(connector);
}