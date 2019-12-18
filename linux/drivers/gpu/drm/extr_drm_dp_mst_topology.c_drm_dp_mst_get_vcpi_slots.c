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
struct TYPE_2__ {int num_slots; } ;
struct drm_dp_mst_port {TYPE_1__ vcpi; } ;

/* Variables and functions */
 struct drm_dp_mst_port* drm_dp_mst_topology_get_port_validated (struct drm_dp_mst_topology_mgr*,struct drm_dp_mst_port*) ; 
 int /*<<< orphan*/  drm_dp_mst_topology_put_port (struct drm_dp_mst_port*) ; 

int drm_dp_mst_get_vcpi_slots(struct drm_dp_mst_topology_mgr *mgr, struct drm_dp_mst_port *port)
{
	int slots = 0;
	port = drm_dp_mst_topology_get_port_validated(mgr, port);
	if (!port)
		return slots;

	slots = port->vcpi.num_slots;
	drm_dp_mst_topology_put_port(port);
	return slots;
}