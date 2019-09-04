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
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct drm_dp_mst_port {int /*<<< orphan*/  connector; } ;

/* Variables and functions */
 struct edid* drm_dp_mst_get_edid (int /*<<< orphan*/ ,struct drm_dp_mst_topology_mgr*,struct drm_dp_mst_port*) ; 
 int /*<<< orphan*/  drm_edid_get_monitor_name (struct edid*,char*,int) ; 

__attribute__((used)) static void fetch_monitor_name(struct drm_dp_mst_topology_mgr *mgr,
			       struct drm_dp_mst_port *port, char *name,
			       int namelen)
{
	struct edid *mst_edid;

	mst_edid = drm_dp_mst_get_edid(port->connector, mgr, port);
	drm_edid_get_monitor_name(mst_edid, name, namelen);
}