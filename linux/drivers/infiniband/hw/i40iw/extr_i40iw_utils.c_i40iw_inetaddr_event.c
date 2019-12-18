#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct notifier_block {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_address; TYPE_1__* ifa_dev; } ;
struct in_device {int /*<<< orphan*/  ifa_list; } ;
struct i40iw_device {scalar_t__ init_state; TYPE_2__* ldev; scalar_t__ closing; } ;
struct i40iw_handler {struct i40iw_device device; } ;
struct TYPE_4__ {struct net_device* netdev; } ;
struct TYPE_3__ {struct net_device* dev; } ;

/* Variables and functions */
 scalar_t__ I40IW_ARP_ADD ; 
 scalar_t__ I40IW_ARP_DELETE ; 
 scalar_t__ IP_ADDR_REGISTERED ; 
#define  NETDEV_CHANGEADDR 130 
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 struct in_device* __in_dev_get_rcu (struct net_device*) ; 
 struct i40iw_handler* i40iw_find_netdev (struct net_device*) ; 
 int /*<<< orphan*/  i40iw_if_notify (struct i40iw_device*,struct net_device*,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  i40iw_manage_arp_cache (struct i40iw_device*,int /*<<< orphan*/ ,scalar_t__*,int,scalar_t__) ; 
 struct net_device* netdev_master_upper_dev_get (struct net_device*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 struct in_ifaddr* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int i40iw_inetaddr_event(struct notifier_block *notifier,
			 unsigned long event,
			 void *ptr)
{
	struct in_ifaddr *ifa = ptr;
	struct net_device *event_netdev = ifa->ifa_dev->dev;
	struct net_device *netdev;
	struct net_device *upper_dev;
	struct i40iw_device *iwdev;
	struct i40iw_handler *hdl;
	u32 local_ipaddr;
	u32 action = I40IW_ARP_ADD;

	hdl = i40iw_find_netdev(event_netdev);
	if (!hdl)
		return NOTIFY_DONE;

	iwdev = &hdl->device;
	if (iwdev->init_state < IP_ADDR_REGISTERED || iwdev->closing)
		return NOTIFY_DONE;

	netdev = iwdev->ldev->netdev;
	upper_dev = netdev_master_upper_dev_get(netdev);
	if (netdev != event_netdev)
		return NOTIFY_DONE;

	if (upper_dev) {
		struct in_device *in;

		rcu_read_lock();
		in = __in_dev_get_rcu(upper_dev);

		local_ipaddr = 0;
		if (in) {
			struct in_ifaddr *ifa;

			ifa = rcu_dereference(in->ifa_list);
			if (ifa)
				local_ipaddr = ntohl(ifa->ifa_address);
		}

		rcu_read_unlock();
	} else {
		local_ipaddr = ntohl(ifa->ifa_address);
	}
	switch (event) {
	case NETDEV_DOWN:
		action = I40IW_ARP_DELETE;
		/* Fall through */
	case NETDEV_UP:
		/* Fall through */
	case NETDEV_CHANGEADDR:

		/* Just skip if no need to handle ARP cache */
		if (!local_ipaddr)
			break;

		i40iw_manage_arp_cache(iwdev,
				       netdev->dev_addr,
				       &local_ipaddr,
				       true,
				       action);
		i40iw_if_notify(iwdev, netdev, &local_ipaddr, true,
				(action == I40IW_ARP_ADD) ? true : false);
		break;
	default:
		break;
	}
	return NOTIFY_DONE;
}