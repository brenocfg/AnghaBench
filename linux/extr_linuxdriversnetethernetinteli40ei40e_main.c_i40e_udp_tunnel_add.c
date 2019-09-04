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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct udp_tunnel_info {int type; int /*<<< orphan*/  port; } ;
struct net_device {int dummy; } ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_pf {int hw_features; int /*<<< orphan*/  state; int /*<<< orphan*/  pending_udp_bitmap; TYPE_1__* udp_ports; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;
struct TYPE_2__ {int /*<<< orphan*/  filter_index; int /*<<< orphan*/  port; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (scalar_t__) ; 
 int /*<<< orphan*/  I40E_AQC_TUNNEL_TYPE_NGE ; 
 int /*<<< orphan*/  I40E_AQC_TUNNEL_TYPE_VXLAN ; 
 int I40E_HW_GENEVE_OFFLOAD_CAPABLE ; 
 scalar_t__ I40E_MAX_PF_UDP_OFFLOAD_PORTS ; 
 int /*<<< orphan*/  I40E_UDP_PORT_INDEX_UNUSED ; 
#define  UDP_TUNNEL_TYPE_GENEVE 129 
#define  UDP_TUNNEL_TYPE_VXLAN 128 
 int /*<<< orphan*/  __I40E_UDP_FILTER_SYNC_PENDING ; 
 scalar_t__ i40e_get_udp_port_idx (struct i40e_pf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_udp_tunnel_add(struct net_device *netdev,
				struct udp_tunnel_info *ti)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	u16 port = ntohs(ti->port);
	u8 next_idx;
	u8 idx;

	idx = i40e_get_udp_port_idx(pf, port);

	/* Check if port already exists */
	if (idx < I40E_MAX_PF_UDP_OFFLOAD_PORTS) {
		netdev_info(netdev, "port %d already offloaded\n", port);
		return;
	}

	/* Now check if there is space to add the new port */
	next_idx = i40e_get_udp_port_idx(pf, 0);

	if (next_idx == I40E_MAX_PF_UDP_OFFLOAD_PORTS) {
		netdev_info(netdev, "maximum number of offloaded UDP ports reached, not adding port %d\n",
			    port);
		return;
	}

	switch (ti->type) {
	case UDP_TUNNEL_TYPE_VXLAN:
		pf->udp_ports[next_idx].type = I40E_AQC_TUNNEL_TYPE_VXLAN;
		break;
	case UDP_TUNNEL_TYPE_GENEVE:
		if (!(pf->hw_features & I40E_HW_GENEVE_OFFLOAD_CAPABLE))
			return;
		pf->udp_ports[next_idx].type = I40E_AQC_TUNNEL_TYPE_NGE;
		break;
	default:
		return;
	}

	/* New port: add it and mark its index in the bitmap */
	pf->udp_ports[next_idx].port = port;
	pf->udp_ports[next_idx].filter_index = I40E_UDP_PORT_INDEX_UNUSED;
	pf->pending_udp_bitmap |= BIT_ULL(next_idx);
	set_bit(__I40E_UDP_FILTER_SYNC_PENDING, pf->state);
}