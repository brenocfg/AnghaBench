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
struct net_device {int flags; } ;
struct hostap_interface {TYPE_1__* local; } ;
struct TYPE_2__ {int is_promisc; int /*<<< orphan*/  set_multicast_list_queue; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hostap_set_multicast_list(struct net_device *dev)
{
#if 0
	/* FIX: promiscuous mode seems to be causing a lot of problems with
	 * some station firmware versions (FCSErr frames, invalid MACPort, etc.
	 * corrupted incoming frames). This code is now commented out while the
	 * problems are investigated. */
	struct hostap_interface *iface;
	local_info_t *local;

	iface = netdev_priv(dev);
	local = iface->local;
	if ((dev->flags & IFF_ALLMULTI) || (dev->flags & IFF_PROMISC)) {
		local->is_promisc = 1;
	} else {
		local->is_promisc = 0;
	}

	schedule_work(&local->set_multicast_list_queue);
#endif
}