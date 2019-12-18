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
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct drm_dp_mst_port {int has_audio; } ;

/* Variables and functions */
 struct drm_dp_mst_port* drm_dp_mst_topology_get_port_validated (struct drm_dp_mst_topology_mgr*,struct drm_dp_mst_port*) ; 
 int /*<<< orphan*/  drm_dp_mst_topology_put_port (struct drm_dp_mst_port*) ; 

bool drm_dp_mst_port_has_audio(struct drm_dp_mst_topology_mgr *mgr,
					struct drm_dp_mst_port *port)
{
	bool ret = false;

	port = drm_dp_mst_topology_get_port_validated(mgr, port);
	if (!port)
		return ret;
	ret = port->has_audio;
	drm_dp_mst_topology_put_port(port);
	return ret;
}