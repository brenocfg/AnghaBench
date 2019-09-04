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
 struct edid* drm_get_edid (struct drm_connector*,struct i2c_adapter*) ; 
 int intel_connector_update_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

int intel_ddc_get_modes(struct drm_connector *connector,
			struct i2c_adapter *adapter)
{
	struct edid *edid;
	int ret;

	edid = drm_get_edid(connector, adapter);
	if (!edid)
		return 0;

	ret = intel_connector_update_modes(connector, edid);
	kfree(edid);

	return ret;
}