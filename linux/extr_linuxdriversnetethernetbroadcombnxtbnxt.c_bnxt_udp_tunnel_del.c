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
struct udp_tunnel_info {scalar_t__ sa_family; int type; int /*<<< orphan*/  port; } ;
struct net_device {int dummy; } ;
struct bnxt {int /*<<< orphan*/  sp_event; int /*<<< orphan*/  nge_port_cnt; int /*<<< orphan*/  nge_port; int /*<<< orphan*/  vxlan_port_cnt; int /*<<< orphan*/  vxlan_port; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  BNXT_GENEVE_DEL_PORT_SP_EVENT ; 
 int /*<<< orphan*/  BNXT_VXLAN_DEL_PORT_SP_EVENT ; 
#define  UDP_TUNNEL_TYPE_GENEVE 129 
#define  UDP_TUNNEL_TYPE_VXLAN 128 
 int /*<<< orphan*/  bnxt_queue_sp_work (struct bnxt*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_udp_tunnel_del(struct net_device *dev,
				struct udp_tunnel_info *ti)
{
	struct bnxt *bp = netdev_priv(dev);

	if (ti->sa_family != AF_INET6 && ti->sa_family != AF_INET)
		return;

	if (!netif_running(dev))
		return;

	switch (ti->type) {
	case UDP_TUNNEL_TYPE_VXLAN:
		if (!bp->vxlan_port_cnt || bp->vxlan_port != ti->port)
			return;
		bp->vxlan_port_cnt--;

		if (bp->vxlan_port_cnt != 0)
			return;

		set_bit(BNXT_VXLAN_DEL_PORT_SP_EVENT, &bp->sp_event);
		break;
	case UDP_TUNNEL_TYPE_GENEVE:
		if (!bp->nge_port_cnt || bp->nge_port != ti->port)
			return;
		bp->nge_port_cnt--;

		if (bp->nge_port_cnt != 0)
			return;

		set_bit(BNXT_GENEVE_DEL_PORT_SP_EVENT, &bp->sp_event);
		break;
	default:
		return;
	}

	bnxt_queue_sp_work(bp);
}