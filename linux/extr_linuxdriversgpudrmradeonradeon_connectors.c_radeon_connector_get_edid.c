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
struct radeon_device {int flags; scalar_t__ is_atom_bios; } ;
struct radeon_connector_atom_dig {scalar_t__ dp_sink_type; } ;
struct drm_connector {scalar_t__ connector_type; struct drm_device* dev; } ;
struct TYPE_4__ {scalar_t__ ddc_valid; } ;
struct radeon_connector {void* edid; TYPE_3__* ddc_bus; struct drm_connector base; struct radeon_connector_atom_dig* con_priv; TYPE_1__ router; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_5__ {int /*<<< orphan*/  ddc; } ;
struct TYPE_6__ {int /*<<< orphan*/  adapter; TYPE_2__ aux; scalar_t__ has_aux; } ;

/* Variables and functions */
 scalar_t__ CONNECTOR_OBJECT_ID_DISPLAYPORT ; 
 scalar_t__ CONNECTOR_OBJECT_ID_eDP ; 
 scalar_t__ DRM_MODE_CONNECTOR_DisplayPort ; 
 scalar_t__ DRM_MODE_CONNECTOR_LVDS ; 
 scalar_t__ DRM_MODE_CONNECTOR_eDP ; 
 scalar_t__ ENCODER_OBJECT_ID_NONE ; 
 int RADEON_IS_PX ; 
 int VGA_SWITCHEROO_CAN_SWITCH_DDC ; 
 void* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 
 void* drm_get_edid_switcheroo (struct drm_connector*,int /*<<< orphan*/ *) ; 
 void* radeon_bios_get_hardcoded_edid (struct radeon_device*) ; 
 scalar_t__ radeon_connector_encoder_get_dp_bridge_encoder_id (struct drm_connector*) ; 
 int /*<<< orphan*/  radeon_router_select_ddc_port (struct radeon_connector*) ; 
 scalar_t__ radeon_runtime_pm ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 
 int vga_switcheroo_handler_flags () ; 

__attribute__((used)) static void radeon_connector_get_edid(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);

	if (radeon_connector->edid)
		return;

	/* on hw with routers, select right port */
	if (radeon_connector->router.ddc_valid)
		radeon_router_select_ddc_port(radeon_connector);

	if ((radeon_connector_encoder_get_dp_bridge_encoder_id(connector) !=
	     ENCODER_OBJECT_ID_NONE) &&
	    radeon_connector->ddc_bus->has_aux) {
		radeon_connector->edid = drm_get_edid(connector,
						      &radeon_connector->ddc_bus->aux.ddc);
	} else if ((connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort) ||
		   (connector->connector_type == DRM_MODE_CONNECTOR_eDP)) {
		struct radeon_connector_atom_dig *dig = radeon_connector->con_priv;

		if ((dig->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT ||
		     dig->dp_sink_type == CONNECTOR_OBJECT_ID_eDP) &&
		    radeon_connector->ddc_bus->has_aux)
			radeon_connector->edid = drm_get_edid(&radeon_connector->base,
							      &radeon_connector->ddc_bus->aux.ddc);
		else if (radeon_connector->ddc_bus)
			radeon_connector->edid = drm_get_edid(&radeon_connector->base,
							      &radeon_connector->ddc_bus->adapter);
	} else if (vga_switcheroo_handler_flags() & VGA_SWITCHEROO_CAN_SWITCH_DDC &&
		   connector->connector_type == DRM_MODE_CONNECTOR_LVDS &&
		   radeon_connector->ddc_bus) {
		radeon_connector->edid = drm_get_edid_switcheroo(&radeon_connector->base,
								 &radeon_connector->ddc_bus->adapter);
	} else if (radeon_connector->ddc_bus) {
		radeon_connector->edid = drm_get_edid(&radeon_connector->base,
						      &radeon_connector->ddc_bus->adapter);
	}

	if (!radeon_connector->edid) {
		/* don't fetch the edid from the vbios if ddc fails and runpm is
		 * enabled so we report disconnected.
		 */
		if ((rdev->flags & RADEON_IS_PX) && (radeon_runtime_pm != 0))
			return;

		if (rdev->is_atom_bios) {
			/* some laptops provide a hardcoded edid in rom for LCDs */
			if (((connector->connector_type == DRM_MODE_CONNECTOR_LVDS) ||
			     (connector->connector_type == DRM_MODE_CONNECTOR_eDP)))
				radeon_connector->edid = radeon_bios_get_hardcoded_edid(rdev);
		} else {
			/* some servers provide a hardcoded edid in rom for KVMs */
			radeon_connector->edid = radeon_bios_get_hardcoded_edid(rdev);
		}
	}
}