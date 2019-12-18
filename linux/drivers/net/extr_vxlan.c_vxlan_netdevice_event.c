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
struct vxlan_net {int dummy; } ;
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned long NETDEV_REGISTER ; 
 unsigned long NETDEV_UDP_TUNNEL_DROP_INFO ; 
 unsigned long NETDEV_UDP_TUNNEL_PUSH_INFO ; 
 unsigned long NETDEV_UNREGISTER ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct vxlan_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  vxlan_handle_lowerdev_unregister (struct vxlan_net*,struct net_device*) ; 
 int /*<<< orphan*/  vxlan_net_id ; 
 int /*<<< orphan*/  vxlan_offload_rx_ports (struct net_device*,int) ; 

__attribute__((used)) static int vxlan_netdevice_event(struct notifier_block *unused,
				 unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct vxlan_net *vn = net_generic(dev_net(dev), vxlan_net_id);

	if (event == NETDEV_UNREGISTER) {
		vxlan_offload_rx_ports(dev, false);
		vxlan_handle_lowerdev_unregister(vn, dev);
	} else if (event == NETDEV_REGISTER) {
		vxlan_offload_rx_ports(dev, true);
	} else if (event == NETDEV_UDP_TUNNEL_PUSH_INFO ||
		   event == NETDEV_UDP_TUNNEL_DROP_INFO) {
		vxlan_offload_rx_ports(dev, event == NETDEV_UDP_TUNNEL_PUSH_INFO);
	}

	return NOTIFY_DONE;
}