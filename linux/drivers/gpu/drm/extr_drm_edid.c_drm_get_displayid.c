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
struct edid {int dummy; } ;
struct drm_connector {int has_tile; int /*<<< orphan*/ * tile_group; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDID_LENGTH ; 
 void* drm_find_displayid_extension (struct edid*) ; 
 int /*<<< orphan*/  drm_mode_put_tile_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drm_parse_display_id (struct drm_connector*,void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void drm_get_displayid(struct drm_connector *connector,
			      struct edid *edid)
{
	void *displayid = NULL;
	int ret;
	connector->has_tile = false;
	displayid = drm_find_displayid_extension(edid);
	if (!displayid) {
		/* drop reference to any tile group we had */
		goto out_drop_ref;
	}

	ret = drm_parse_display_id(connector, displayid, EDID_LENGTH, true);
	if (ret < 0)
		goto out_drop_ref;
	if (!connector->has_tile)
		goto out_drop_ref;
	return;
out_drop_ref:
	if (connector->tile_group) {
		drm_mode_put_tile_group(connector->dev, connector->tile_group);
		connector->tile_group = NULL;
	}
	return;
}