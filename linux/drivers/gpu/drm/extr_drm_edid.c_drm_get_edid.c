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
struct drm_connector {scalar_t__ force; } ;

/* Variables and functions */
 scalar_t__ DRM_FORCE_OFF ; 
 scalar_t__ DRM_FORCE_UNSPECIFIED ; 
 struct edid* drm_do_get_edid (struct drm_connector*,int /*<<< orphan*/ ,struct i2c_adapter*) ; 
 int /*<<< orphan*/  drm_do_probe_ddc_edid ; 
 int /*<<< orphan*/  drm_get_displayid (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_probe_ddc (struct i2c_adapter*) ; 

struct edid *drm_get_edid(struct drm_connector *connector,
			  struct i2c_adapter *adapter)
{
	struct edid *edid;

	if (connector->force == DRM_FORCE_OFF)
		return NULL;

	if (connector->force == DRM_FORCE_UNSPECIFIED && !drm_probe_ddc(adapter))
		return NULL;

	edid = drm_do_get_edid(connector, drm_do_probe_ddc_edid, adapter);
	if (edid)
		drm_get_displayid(connector, edid);
	return edid;
}