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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct udp_tunnel_info {int type; int /*<<< orphan*/  port; } ;
struct net_device {int dummy; } ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_pf {int /*<<< orphan*/  state; int /*<<< orphan*/  pending_udp_bitmap; TYPE_1__* udp_ports; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;
struct TYPE_2__ {scalar_t__ port; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (size_t) ; 
 int /*<<< orphan*/  I40E_AQC_TUNNEL_TYPE_NGE ; 
 int /*<<< orphan*/  I40E_AQC_TUNNEL_TYPE_VXLAN ; 
 size_t I40E_MAX_PF_UDP_OFFLOAD_PORTS ; 
#define  UDP_TUNNEL_TYPE_GENEVE 129 
#define  UDP_TUNNEL_TYPE_VXLAN 128 
 int /*<<< orphan*/  __I40E_UDP_FILTER_SYNC_PENDING ; 
 size_t i40e_get_udp_port_idx (struct i40e_pf*,int /*<<< orphan*/ ) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_udp_tunnel_del(struct net_device *netdev,
				struct udp_tunnel_info *ti)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	u16 port = ntohs(ti->port);
	u8 idx;

	idx = i40e_get_udp_port_idx(pf, port);

	/* Check if port already exists */
	if (idx >= I40E_MAX_PF_UDP_OFFLOAD_PORTS)
		goto not_found;

	switch (ti->type) {
	case UDP_TUNNEL_TYPE_VXLAN:
		if (pf->udp_ports[idx].type != I40E_AQC_TUNNEL_TYPE_VXLAN)
			goto not_found;
		break;
	case UDP_TUNNEL_TYPE_GENEVE:
		if (pf->udp_ports[idx].type != I40E_AQC_TUNNEL_TYPE_NGE)
			goto not_found;
		break;
	default:
		goto not_found;
	}

	/* if port exists, set it to 0 (mark for deletion)
	 * and make it pending
	 */
	pf->udp_ports[idx].port = 0;

	/* Toggle pending bit instead of setting it. This way if we are
	 * deleting a port that has yet to be added we just clear the pending
	 * bit and don't have to worry about it.
	 */
	pf->pending_udp_bitmap ^= BIT_ULL(idx);
	set_bit(__I40E_UDP_FILTER_SYNC_PENDING, pf->state);

	return;
not_found:
	netdev_warn(netdev, "UDP port %d was not found, not deleting\n",
		    port);
}