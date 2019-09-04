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
struct net_device {int dummy; } ;

/* Variables and functions */
 struct net_device* MASTER_TO_SLAVE (struct net_device*) ; 
 int /*<<< orphan*/  isdn_net_hangup (struct net_device*) ; 
 int /*<<< orphan*/  isdn_unlock_drivers () ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int
isdn_net_close(struct net_device *dev)
{
	struct net_device *p;
#ifdef CONFIG_ISDN_X25
	struct concap_proto *cprot =
		((isdn_net_local *)netdev_priv(dev))->netdev->cprot;
	/* printk(KERN_DEBUG "isdn_net_close %s\n" , dev-> name); */
#endif

#ifdef CONFIG_ISDN_X25
	if (cprot && cprot->pops) cprot->pops->close(cprot);
#endif
	netif_stop_queue(dev);
	p = MASTER_TO_SLAVE(dev);
	if (p) {
		/* If this interface has slaves, stop them also */
		while (p) {
#ifdef CONFIG_ISDN_X25
			cprot = ((isdn_net_local *)netdev_priv(p))
				->netdev->cprot;
			if (cprot && cprot->pops)
				cprot->pops->close(cprot);
#endif
			isdn_net_hangup(p);
			p = MASTER_TO_SLAVE(p);
		}
	}
	isdn_net_hangup(dev);
	isdn_unlock_drivers();
	return 0;
}