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
struct dumb_vga {int /*<<< orphan*/  ddc; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int drm_add_modes_noedid (struct drm_connector*,int,int) ; 
 struct dumb_vga* drm_connector_to_dumb_vga (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_set_preferred_mode (struct drm_connector*,int,int) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

__attribute__((used)) static int dumb_vga_get_modes(struct drm_connector *connector)
{
	struct dumb_vga *vga = drm_connector_to_dumb_vga(connector);
	struct edid *edid;
	int ret;

	if (!vga->ddc)
		goto fallback;

	edid = drm_get_edid(connector, vga->ddc);
	if (!edid) {
		DRM_INFO("EDID readout failed, falling back to standard modes\n");
		goto fallback;
	}

	drm_connector_update_edid_property(connector, edid);
	ret = drm_add_edid_modes(connector, edid);
	kfree(edid);
	return ret;

fallback:
	/*
	 * In case we cannot retrieve the EDIDs (broken or missing i2c
	 * bus), fallback on the XGA standards
	 */
	ret = drm_add_modes_noedid(connector, 1920, 1200);

	/* And prefer a mode pretty much anyone can handle */
	drm_set_preferred_mode(connector, 1024, 768);

	return ret;
}