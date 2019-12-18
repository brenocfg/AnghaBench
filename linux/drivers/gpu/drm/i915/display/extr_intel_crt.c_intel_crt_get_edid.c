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
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 struct edid* drm_get_edid (struct drm_connector*,struct i2c_adapter*) ; 
 int /*<<< orphan*/  intel_gmbus_force_bit (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  intel_gmbus_is_forced_bit (struct i2c_adapter*) ; 

__attribute__((used)) static struct edid *intel_crt_get_edid(struct drm_connector *connector,
				struct i2c_adapter *i2c)
{
	struct edid *edid;

	edid = drm_get_edid(connector, i2c);

	if (!edid && !intel_gmbus_is_forced_bit(i2c)) {
		DRM_DEBUG_KMS("CRT GMBUS EDID read failed, retry using GPIO bit-banging\n");
		intel_gmbus_force_bit(i2c, true);
		edid = drm_get_edid(connector, i2c);
		intel_gmbus_force_bit(i2c, false);
	}

	return edid;
}