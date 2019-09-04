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
struct edid {int dummy; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ddc; } ;
struct drm_dp_mst_port {int /*<<< orphan*/  has_audio; TYPE_1__ aux; scalar_t__ cached_edid; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_set_tile_property (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_detect_monitor_audio (struct edid*) ; 
 struct drm_dp_mst_port* drm_dp_get_validated_port_ref (struct drm_dp_mst_topology_mgr*,struct drm_dp_mst_port*) ; 
 int /*<<< orphan*/  drm_dp_put_port (struct drm_dp_mst_port*) ; 
 struct edid* drm_edid_duplicate (scalar_t__) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 

struct edid *drm_dp_mst_get_edid(struct drm_connector *connector, struct drm_dp_mst_topology_mgr *mgr, struct drm_dp_mst_port *port)
{
	struct edid *edid = NULL;

	/* we need to search for the port in the mgr in case its gone */
	port = drm_dp_get_validated_port_ref(mgr, port);
	if (!port)
		return NULL;

	if (port->cached_edid)
		edid = drm_edid_duplicate(port->cached_edid);
	else {
		edid = drm_get_edid(connector, &port->aux.ddc);
		drm_connector_set_tile_property(connector);
	}
	port->has_audio = drm_detect_monitor_audio(edid);
	drm_dp_put_port(port);
	return edid;
}