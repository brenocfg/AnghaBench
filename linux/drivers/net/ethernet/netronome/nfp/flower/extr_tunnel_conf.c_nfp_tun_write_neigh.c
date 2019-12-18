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
typedef  int /*<<< orphan*/  u32 ;
struct nfp_tun_neigh {int /*<<< orphan*/  dst_ipv4; int /*<<< orphan*/  port_id; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; int /*<<< orphan*/  src_ipv4; } ;
struct nfp_app {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct neighbour {int nud_state; scalar_t__ dead; } ;
struct flowi4 {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_FLOWER_CMSG_TYPE_TUN_NEIGH ; 
 int NUD_VALID ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nfp_tun_neigh*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  neigh_event_send (struct neighbour*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_ha_snapshot (int /*<<< orphan*/ ,struct neighbour*,struct net_device*) ; 
 int /*<<< orphan*/  nfp_flower_get_port_id_from_netdev (struct nfp_app*,struct net_device*) ; 
 int /*<<< orphan*/  nfp_flower_xmit_tun_conf (struct nfp_app*,int /*<<< orphan*/ ,int,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_tun_add_route_to_cache (struct nfp_app*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_tun_del_route_from_cache (struct nfp_app*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_tun_write_neigh(struct net_device *netdev, struct nfp_app *app,
		    struct flowi4 *flow, struct neighbour *neigh, gfp_t flag)
{
	struct nfp_tun_neigh payload;
	u32 port_id;

	port_id = nfp_flower_get_port_id_from_netdev(app, netdev);
	if (!port_id)
		return;

	memset(&payload, 0, sizeof(struct nfp_tun_neigh));
	payload.dst_ipv4 = flow->daddr;

	/* If entry has expired send dst IP with all other fields 0. */
	if (!(neigh->nud_state & NUD_VALID) || neigh->dead) {
		nfp_tun_del_route_from_cache(app, payload.dst_ipv4);
		/* Trigger ARP to verify invalid neighbour state. */
		neigh_event_send(neigh, NULL);
		goto send_msg;
	}

	/* Have a valid neighbour so populate rest of entry. */
	payload.src_ipv4 = flow->saddr;
	ether_addr_copy(payload.src_addr, netdev->dev_addr);
	neigh_ha_snapshot(payload.dst_addr, neigh, netdev);
	payload.port_id = cpu_to_be32(port_id);
	/* Add destination of new route to NFP cache. */
	nfp_tun_add_route_to_cache(app, payload.dst_ipv4);

send_msg:
	nfp_flower_xmit_tun_conf(app, NFP_FLOWER_CMSG_TYPE_TUN_NEIGH,
				 sizeof(struct nfp_tun_neigh),
				 (unsigned char *)&payload, flag);
}