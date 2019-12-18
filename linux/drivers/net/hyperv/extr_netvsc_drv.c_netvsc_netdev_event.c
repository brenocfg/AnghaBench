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
struct notifier_block {int dummy; } ;
struct net_device {scalar_t__ type; int priv_flags; int flags; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int IFF_BONDING ; 
 int IFF_MASTER ; 
#define  NETDEV_DOWN 131 
#define  NETDEV_REGISTER 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  device_ops ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int netvsc_register_vf (struct net_device*) ; 
 int netvsc_unregister_vf (struct net_device*) ; 
 int netvsc_vf_changed (struct net_device*) ; 

__attribute__((used)) static int netvsc_netdev_event(struct notifier_block *this,
			       unsigned long event, void *ptr)
{
	struct net_device *event_dev = netdev_notifier_info_to_dev(ptr);

	/* Skip our own events */
	if (event_dev->netdev_ops == &device_ops)
		return NOTIFY_DONE;

	/* Avoid non-Ethernet type devices */
	if (event_dev->type != ARPHRD_ETHER)
		return NOTIFY_DONE;

	/* Avoid Vlan dev with same MAC registering as VF */
	if (is_vlan_dev(event_dev))
		return NOTIFY_DONE;

	/* Avoid Bonding master dev with same MAC registering as VF */
	if ((event_dev->priv_flags & IFF_BONDING) &&
	    (event_dev->flags & IFF_MASTER))
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_REGISTER:
		return netvsc_register_vf(event_dev);
	case NETDEV_UNREGISTER:
		return netvsc_unregister_vf(event_dev);
	case NETDEV_UP:
	case NETDEV_DOWN:
		return netvsc_vf_changed(event_dev);
	default:
		return NOTIFY_DONE;
	}
}