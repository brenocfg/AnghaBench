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
typedef  void* u32 ;
struct sk_buff {int dummy; } ;
struct nfp_tun_active_tuns {TYPE_1__* tun_info; int /*<<< orphan*/  count; } ;
struct nfp_app {int dummy; } ;
struct net_device {int dummy; } ;
struct neighbour {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  egress_port; int /*<<< orphan*/  ipv4; } ;

/* Variables and functions */
 int NFP_FL_MAX_ROUTES ; 
 int /*<<< orphan*/  arp_tbl ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_event_send (struct neighbour*,int /*<<< orphan*/ *) ; 
 struct neighbour* neigh_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 struct net_device* nfp_app_dev_get (struct nfp_app*,void*,int /*<<< orphan*/ *) ; 
 struct nfp_tun_active_tuns* nfp_flower_cmsg_get_data (struct sk_buff*) ; 
 int nfp_flower_cmsg_get_data_len (struct sk_buff*) ; 
 int /*<<< orphan*/  nfp_flower_cmsg_warn (struct nfp_app*,char*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int struct_size (struct nfp_tun_active_tuns*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tun_info ; 

void nfp_tunnel_keep_alive(struct nfp_app *app, struct sk_buff *skb)
{
	struct nfp_tun_active_tuns *payload;
	struct net_device *netdev;
	int count, i, pay_len;
	struct neighbour *n;
	__be32 ipv4_addr;
	u32 port;

	payload = nfp_flower_cmsg_get_data(skb);
	count = be32_to_cpu(payload->count);
	if (count > NFP_FL_MAX_ROUTES) {
		nfp_flower_cmsg_warn(app, "Tunnel keep-alive request exceeds max routes.\n");
		return;
	}

	pay_len = nfp_flower_cmsg_get_data_len(skb);
	if (pay_len != struct_size(payload, tun_info, count)) {
		nfp_flower_cmsg_warn(app, "Corruption in tunnel keep-alive message.\n");
		return;
	}

	rcu_read_lock();
	for (i = 0; i < count; i++) {
		ipv4_addr = payload->tun_info[i].ipv4;
		port = be32_to_cpu(payload->tun_info[i].egress_port);
		netdev = nfp_app_dev_get(app, port, NULL);
		if (!netdev)
			continue;

		n = neigh_lookup(&arp_tbl, &ipv4_addr, netdev);
		if (!n)
			continue;

		/* Update the used timestamp of neighbour */
		neigh_event_send(n, NULL);
		neigh_release(n);
	}
	rcu_read_unlock();
}