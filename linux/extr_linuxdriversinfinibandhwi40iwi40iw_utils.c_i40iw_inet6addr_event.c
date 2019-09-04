#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct notifier_block {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  u6_addr32; } ;
struct TYPE_8__ {TYPE_3__ in6_u; } ;
struct inet6_ifaddr {TYPE_4__ addr; TYPE_1__* idev; } ;
struct i40iw_device {scalar_t__ init_state; TYPE_2__* ldev; scalar_t__ closing; } ;
struct i40iw_handler {struct i40iw_device device; } ;
struct TYPE_6__ {struct net_device* netdev; } ;
struct TYPE_5__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_ARP_ADD ; 
 int /*<<< orphan*/  I40IW_ARP_DELETE ; 
 scalar_t__ IP_ADDR_REGISTERED ; 
#define  NETDEV_CHANGEADDR 130 
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  i40iw_copy_ip_ntohl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct i40iw_handler* i40iw_find_netdev (struct net_device*) ; 
 int /*<<< orphan*/  i40iw_if_notify (struct i40iw_device*,struct net_device*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  i40iw_manage_arp_cache (struct i40iw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int i40iw_inet6addr_event(struct notifier_block *notifier,
			  unsigned long event,
			  void *ptr)
{
	struct inet6_ifaddr *ifa = (struct inet6_ifaddr *)ptr;
	struct net_device *event_netdev = ifa->idev->dev;
	struct net_device *netdev;
	struct i40iw_device *iwdev;
	struct i40iw_handler *hdl;
	u32 local_ipaddr6[4];
	u32 action = I40IW_ARP_ADD;

	hdl = i40iw_find_netdev(event_netdev);
	if (!hdl)
		return NOTIFY_DONE;

	iwdev = &hdl->device;
	if (iwdev->init_state < IP_ADDR_REGISTERED || iwdev->closing)
		return NOTIFY_DONE;

	netdev = iwdev->ldev->netdev;
	if (netdev != event_netdev)
		return NOTIFY_DONE;

	i40iw_copy_ip_ntohl(local_ipaddr6, ifa->addr.in6_u.u6_addr32);
	switch (event) {
	case NETDEV_DOWN:
		action = I40IW_ARP_DELETE;
		/* Fall through */
	case NETDEV_UP:
		/* Fall through */
	case NETDEV_CHANGEADDR:
		i40iw_manage_arp_cache(iwdev,
				       netdev->dev_addr,
				       local_ipaddr6,
				       false,
				       action);
		i40iw_if_notify(iwdev, netdev, local_ipaddr6, false,
				(action == I40IW_ARP_ADD) ? true : false);
		break;
	default:
		break;
	}
	return NOTIFY_DONE;
}