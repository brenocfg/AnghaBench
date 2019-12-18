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
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ddc; } ;
struct drm_dp_mst_port {int pdt; int port_num; int /*<<< orphan*/  ldps; TYPE_1__ aux; int /*<<< orphan*/  cached_edid; int /*<<< orphan*/  ddps; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
#define  DP_PEER_DEVICE_DP_LEGACY_CONV 131 
#define  DP_PEER_DEVICE_MST_BRANCHING 130 
#define  DP_PEER_DEVICE_NONE 129 
#define  DP_PEER_DEVICE_SST_SINK 128 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 struct drm_dp_mst_port* drm_dp_mst_topology_get_port_validated (struct drm_dp_mst_topology_mgr*,struct drm_dp_mst_port*) ; 
 int /*<<< orphan*/  drm_dp_mst_topology_put_port (struct drm_dp_mst_port*) ; 
 int /*<<< orphan*/  drm_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 

enum drm_connector_status drm_dp_mst_detect_port(struct drm_connector *connector,
						 struct drm_dp_mst_topology_mgr *mgr, struct drm_dp_mst_port *port)
{
	enum drm_connector_status status = connector_status_disconnected;

	/* we need to search for the port in the mgr in case it's gone */
	port = drm_dp_mst_topology_get_port_validated(mgr, port);
	if (!port)
		return connector_status_disconnected;

	if (!port->ddps)
		goto out;

	switch (port->pdt) {
	case DP_PEER_DEVICE_NONE:
	case DP_PEER_DEVICE_MST_BRANCHING:
		break;

	case DP_PEER_DEVICE_SST_SINK:
		status = connector_status_connected;
		/* for logical ports - cache the EDID */
		if (port->port_num >= 8 && !port->cached_edid) {
			port->cached_edid = drm_get_edid(connector, &port->aux.ddc);
		}
		break;
	case DP_PEER_DEVICE_DP_LEGACY_CONV:
		if (port->ldps)
			status = connector_status_connected;
		break;
	}
out:
	drm_dp_mst_topology_put_port(port);
	return status;
}