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
typedef  int /*<<< orphan*/  typebuf ;
struct efx_udp_tunnel {scalar_t__ type; int /*<<< orphan*/  port; scalar_t__ count; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {int datapath_caps; int /*<<< orphan*/  udp_tunnels_lock; } ;

/* Variables and functions */
 int ENOENT ; 
 int MC_CMD_GET_CAPABILITIES_OUT_VXLAN_NVGRE_LBN ; 
 struct efx_udp_tunnel* __efx_ef10_udp_tnl_lookup_port (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_device_detach_sync (struct efx_nic*) ; 
 int efx_ef10_set_udp_tnl_ports (struct efx_nic*,int) ; 
 int /*<<< orphan*/  efx_get_udp_tunnel_type_name (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  netif_warn (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_ef10_udp_tnl_del_port(struct efx_nic *efx,
				     struct efx_udp_tunnel tnl)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	struct efx_udp_tunnel *match;
	char typebuf[8];
	int rc;

	if (!(nic_data->datapath_caps &
	      (1 << MC_CMD_GET_CAPABILITIES_OUT_VXLAN_NVGRE_LBN)))
		return 0;

	efx_get_udp_tunnel_type_name(tnl.type, typebuf, sizeof(typebuf));
	netif_dbg(efx, drv, efx->net_dev, "Removing UDP tunnel (%s) port %d\n",
		  typebuf, ntohs(tnl.port));

	mutex_lock(&nic_data->udp_tunnels_lock);
	/* Make sure all TX are stopped while we remove from the table, else we
	 * might race against an efx_features_check().
	 */
	efx_device_detach_sync(efx);

	match = __efx_ef10_udp_tnl_lookup_port(efx, tnl.port);
	if (match != NULL) {
		if (match->type == tnl.type) {
			if (--match->count) {
				/* Port is still in use, so nothing to do */
				netif_dbg(efx, drv, efx->net_dev,
					  "UDP tunnel port %d remains active\n",
					  ntohs(tnl.port));
				rc = 0;
				goto out_unlock;
			}
			rc = efx_ef10_set_udp_tnl_ports(efx, false);
			goto out_unlock;
		}
		efx_get_udp_tunnel_type_name(match->type,
					     typebuf, sizeof(typebuf));
		netif_warn(efx, drv, efx->net_dev,
			   "UDP port %d is actually in use by %s, not removing\n",
			   ntohs(tnl.port), typebuf);
	}
	rc = -ENOENT;

out_unlock:
	mutex_unlock(&nic_data->udp_tunnels_lock);
	return rc;
}