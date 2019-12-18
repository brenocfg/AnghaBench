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
struct tfp410 {int /*<<< orphan*/  ddc; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int drm_add_modes_noedid (struct drm_connector*,int,int) ; 
 struct tfp410* drm_connector_to_tfp410 (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_set_preferred_mode (struct drm_connector*,int,int) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

__attribute__((used)) static int tfp410_get_modes(struct drm_connector *connector)
{
	struct tfp410 *dvi = drm_connector_to_tfp410(connector);
	struct edid *edid;
	int ret;

	if (!dvi->ddc)
		goto fallback;

	edid = drm_get_edid(connector, dvi->ddc);
	if (!edid) {
		DRM_INFO("EDID read failed. Fallback to standard modes\n");
		goto fallback;
	}

	drm_connector_update_edid_property(connector, edid);

	ret = drm_add_edid_modes(connector, edid);

	kfree(edid);

	return ret;

fallback:
	/* No EDID, fallback on the XGA standard modes */
	ret = drm_add_modes_noedid(connector, 1920, 1200);

	/* And prefer a mode pretty much anything can handle */
	drm_set_preferred_mode(connector, 1024, 768);

	return ret;
}