#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gma_encoder {TYPE_1__* i2c_bus; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 
 struct gma_encoder* gma_attached_encoder (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

__attribute__((used)) static int cdv_hdmi_get_modes(struct drm_connector *connector)
{
	struct gma_encoder *gma_encoder = gma_attached_encoder(connector);
	struct edid *edid = NULL;
	int ret = 0;

	edid = drm_get_edid(connector, &gma_encoder->i2c_bus->adapter);
	if (edid) {
		drm_connector_update_edid_property(connector, edid);
		ret = drm_add_edid_modes(connector, edid);
		kfree(edid);
	}
	return ret;
}