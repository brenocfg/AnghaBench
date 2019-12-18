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
struct net_local {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  watchdog; TYPE_1__* second; struct net_device* link; } ;
struct net_device {int /*<<< orphan*/  irq; scalar_t__ base_addr; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ CSR0 ; 
 int EBUSY ; 
 int FL_SECONDARY ; 
 int FL_SLAVE ; 
 int IFF_UP ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drop_xmit_queue (struct net_device*) ; 
 int /*<<< orphan*/  emancipate (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sbni_close( struct net_device  *dev )
{
	struct net_local  *nl = netdev_priv(dev);

	if( nl->second  &&  nl->second->flags & IFF_UP ) {
		netdev_notice(dev, "Secondary channel (%s) is active!\n",
			      nl->second->name);
		return  -EBUSY;
	}

#ifdef CONFIG_SBNI_MULTILINE
	if( nl->state & FL_SLAVE )
		emancipate( dev );
	else
		while( nl->link )	/* it's master device! */
			emancipate( nl->link );
#endif

	spin_lock( &nl->lock );

	nl->second = NULL;
	drop_xmit_queue( dev );	
	netif_stop_queue( dev );
   
	del_timer( &nl->watchdog );

	outb( 0, dev->base_addr + CSR0 );

	if( !(nl->state & FL_SECONDARY) )
		free_irq( dev->irq, dev );
	nl->state &= FL_SECONDARY;

	spin_unlock( &nl->lock );
	return 0;
}