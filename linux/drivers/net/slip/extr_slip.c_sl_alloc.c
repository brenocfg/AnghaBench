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
struct slip {int /*<<< orphan*/  outfill_timer; int /*<<< orphan*/  keepalive_timer; int /*<<< orphan*/  mode; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  lock; struct net_device* dev; int /*<<< orphan*/  magic; } ;
struct net_device {int base_addr; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int /*<<< orphan*/  SLIP_MAGIC ; 
 int /*<<< orphan*/  SL_MODE_DEFAULT ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct slip* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sl_keepalive ; 
 int /*<<< orphan*/  sl_outfill ; 
 int /*<<< orphan*/  sl_setup ; 
 struct net_device** slip_devs ; 
 int slip_maxdev ; 
 int /*<<< orphan*/  slip_transmit ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct slip *sl_alloc(void)
{
	int i;
	char name[IFNAMSIZ];
	struct net_device *dev = NULL;
	struct slip       *sl;

	for (i = 0; i < slip_maxdev; i++) {
		dev = slip_devs[i];
		if (dev == NULL)
			break;
	}
	/* Sorry, too many, all slots in use */
	if (i >= slip_maxdev)
		return NULL;

	sprintf(name, "sl%d", i);
	dev = alloc_netdev(sizeof(*sl), name, NET_NAME_UNKNOWN, sl_setup);
	if (!dev)
		return NULL;

	dev->base_addr  = i;
	sl = netdev_priv(dev);

	/* Initialize channel control data */
	sl->magic       = SLIP_MAGIC;
	sl->dev	      	= dev;
	spin_lock_init(&sl->lock);
	INIT_WORK(&sl->tx_work, slip_transmit);
	sl->mode        = SL_MODE_DEFAULT;
#ifdef CONFIG_SLIP_SMART
	/* initialize timer_list struct */
	timer_setup(&sl->keepalive_timer, sl_keepalive, 0);
	timer_setup(&sl->outfill_timer, sl_outfill, 0);
#endif
	slip_devs[i] = dev;
	return sl;
}