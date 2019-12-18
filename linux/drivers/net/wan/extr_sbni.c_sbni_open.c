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
struct timer_list {scalar_t__ expires; } ;
struct sbni_in_stats {int dummy; } ;
struct net_local {int /*<<< orphan*/  lock; struct net_device* watchdog_dev; int /*<<< orphan*/  in_stats; int /*<<< orphan*/  state; struct net_device* second; struct timer_list watchdog; } ;
struct net_device_stats {int dummy; } ;
struct net_device {int base_addr; scalar_t__ irq; int flags; int /*<<< orphan*/  stats; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  FL_SECONDARY ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int SBNI_MAX_NUM_CARDS ; 
 scalar_t__ SBNI_TIMEOUT ; 
 int /*<<< orphan*/  add_timer (struct timer_list*) ; 
 int /*<<< orphan*/  card_start (struct net_device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 scalar_t__ request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 struct net_device** sbni_cards ; 
 int /*<<< orphan*/  sbni_interrupt ; 
 int /*<<< orphan*/  sbni_watchdog ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (struct timer_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sbni_open( struct net_device  *dev )
{
	struct net_local	*nl = netdev_priv(dev);
	struct timer_list	*w  = &nl->watchdog;

	/*
	 * For double ISA adapters within "common irq" mode, we have to
	 * determine whether primary or secondary channel is initialized,
	 * and set the irq handler only in first case.
	 */
	if( dev->base_addr < 0x400 ) {		/* ISA only */
		struct net_device  **p = sbni_cards;
		for( ;  *p  &&  p < sbni_cards + SBNI_MAX_NUM_CARDS;  ++p )
			if( (*p)->irq == dev->irq &&
			    ((*p)->base_addr == dev->base_addr + 4 ||
			     (*p)->base_addr == dev->base_addr - 4) &&
			    (*p)->flags & IFF_UP ) {

				((struct net_local *) (netdev_priv(*p)))
					->second = dev;
				netdev_notice(dev, "using shared irq with %s\n",
					      (*p)->name);
				nl->state |= FL_SECONDARY;
				goto  handler_attached;
			}
	}

	if( request_irq(dev->irq, sbni_interrupt, IRQF_SHARED, dev->name, dev) ) {
		netdev_err(dev, "unable to get IRQ %d\n", dev->irq);
		return  -EAGAIN;
	}

handler_attached:

	spin_lock( &nl->lock );
	memset( &dev->stats, 0, sizeof(struct net_device_stats) );
	memset( &nl->in_stats, 0, sizeof(struct sbni_in_stats) );

	card_start( dev );

	netif_start_queue( dev );

	/* set timer watchdog */
	nl->watchdog_dev = dev;
	timer_setup(w, sbni_watchdog, 0);
	w->expires	= jiffies + SBNI_TIMEOUT;
	add_timer( w );
   
	spin_unlock( &nl->lock );
	return 0;
}