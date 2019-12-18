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
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct nfp_flower_cmsg_portmod {int info; int /*<<< orphan*/  mtu; int /*<<< orphan*/  portnum; } ;
struct nfp_app {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NFP_FLOWER_CMSG_PORTMOD_INFO_LINK ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_mtu (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 struct net_device* nfp_app_dev_get (struct nfp_app*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nfp_flower_cmsg_portmod* nfp_flower_cmsg_get_data (struct sk_buff*) ; 
 int /*<<< orphan*/  nfp_flower_cmsg_warn (struct nfp_app*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void
nfp_flower_cmsg_portmod_rx(struct nfp_app *app, struct sk_buff *skb)
{
	struct nfp_flower_cmsg_portmod *msg;
	struct net_device *netdev;
	bool link;

	msg = nfp_flower_cmsg_get_data(skb);
	link = msg->info & NFP_FLOWER_CMSG_PORTMOD_INFO_LINK;

	rtnl_lock();
	rcu_read_lock();
	netdev = nfp_app_dev_get(app, be32_to_cpu(msg->portnum), NULL);
	rcu_read_unlock();
	if (!netdev) {
		nfp_flower_cmsg_warn(app, "ctrl msg for unknown port 0x%08x\n",
				     be32_to_cpu(msg->portnum));
		rtnl_unlock();
		return;
	}

	if (link) {
		u16 mtu = be16_to_cpu(msg->mtu);

		netif_carrier_on(netdev);

		/* An MTU of 0 from the firmware should be ignored */
		if (mtu)
			dev_set_mtu(netdev, mtu);
	} else {
		netif_carrier_off(netdev);
	}
	rtnl_unlock();
}