#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_connector {scalar_t__ connector_type; struct drm_device* dev; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_connector_atom_dig {scalar_t__ dp_sink_type; } ;
struct TYPE_4__ {scalar_t__ ddc_valid; } ;
struct amdgpu_connector {void* edid; TYPE_3__* ddc_bus; struct amdgpu_connector_atom_dig* con_priv; TYPE_1__ router; } ;
struct TYPE_5__ {int /*<<< orphan*/  ddc; } ;
struct TYPE_6__ {int /*<<< orphan*/  adapter; TYPE_2__ aux; scalar_t__ has_aux; } ;

/* Variables and functions */
 scalar_t__ CONNECTOR_OBJECT_ID_DISPLAYPORT ; 
 scalar_t__ CONNECTOR_OBJECT_ID_eDP ; 
 scalar_t__ DRM_MODE_CONNECTOR_DisplayPort ; 
 scalar_t__ DRM_MODE_CONNECTOR_LVDS ; 
 scalar_t__ DRM_MODE_CONNECTOR_eDP ; 
 scalar_t__ ENCODER_OBJECT_ID_NONE ; 
 scalar_t__ amdgpu_connector_encoder_get_dp_bridge_encoder_id (struct drm_connector*) ; 
 void* amdgpu_connector_get_hardcoded_edid (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_i2c_router_select_ddc_port (struct amdgpu_connector*) ; 
 void* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 
 struct amdgpu_connector* to_amdgpu_connector (struct drm_connector*) ; 

__attribute__((used)) static void amdgpu_connector_get_edid(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);

	if (amdgpu_connector->edid)
		return;

	/* on hw with routers, select right port */
	if (amdgpu_connector->router.ddc_valid)
		amdgpu_i2c_router_select_ddc_port(amdgpu_connector);

	if ((amdgpu_connector_encoder_get_dp_bridge_encoder_id(connector) !=
	     ENCODER_OBJECT_ID_NONE) &&
	    amdgpu_connector->ddc_bus->has_aux) {
		amdgpu_connector->edid = drm_get_edid(connector,
						      &amdgpu_connector->ddc_bus->aux.ddc);
	} else if ((connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort) ||
		   (connector->connector_type == DRM_MODE_CONNECTOR_eDP)) {
		struct amdgpu_connector_atom_dig *dig = amdgpu_connector->con_priv;

		if ((dig->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT ||
		     dig->dp_sink_type == CONNECTOR_OBJECT_ID_eDP) &&
		    amdgpu_connector->ddc_bus->has_aux)
			amdgpu_connector->edid = drm_get_edid(connector,
							      &amdgpu_connector->ddc_bus->aux.ddc);
		else if (amdgpu_connector->ddc_bus)
			amdgpu_connector->edid = drm_get_edid(connector,
							      &amdgpu_connector->ddc_bus->adapter);
	} else if (amdgpu_connector->ddc_bus) {
		amdgpu_connector->edid = drm_get_edid(connector,
						      &amdgpu_connector->ddc_bus->adapter);
	}

	if (!amdgpu_connector->edid) {
		/* some laptops provide a hardcoded edid in rom for LCDs */
		if (((connector->connector_type == DRM_MODE_CONNECTOR_LVDS) ||
		     (connector->connector_type == DRM_MODE_CONNECTOR_eDP)))
			amdgpu_connector->edid = amdgpu_connector_get_hardcoded_edid(adev);
	}
}