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
struct i2c_adapter {int dummy; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 struct i2c_adapter* i2c_get_adapter (int) ; 
 scalar_t__ raw_edid ; 

__attribute__((used)) static int oaktrail_hdmi_get_modes(struct drm_connector *connector)
{
	struct i2c_adapter *i2c_adap;
	struct edid *edid;
	int ret = 0;

	/*
	 *	FIXME: We need to figure this lot out. In theory we can
	 *	read the EDID somehow but I've yet to find working reference
	 *	code.
	 */
	i2c_adap = i2c_get_adapter(3);
	if (i2c_adap == NULL) {
		DRM_ERROR("No ddc adapter available!\n");
		edid = (struct edid *)raw_edid;
	} else {
		edid = (struct edid *)raw_edid;
		/* FIXME ? edid = drm_get_edid(connector, i2c_adap); */
	}

	if (edid) {
		drm_connector_update_edid_property(connector, edid);
		ret = drm_add_edid_modes(connector, edid);
	}
	return ret;
}