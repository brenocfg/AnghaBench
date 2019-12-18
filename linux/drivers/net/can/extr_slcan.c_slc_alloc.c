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
struct slcan {int /*<<< orphan*/  tx_work; int /*<<< orphan*/  lock; struct net_device* dev; int /*<<< orphan*/  magic; } ;
struct net_device {int base_addr; void* ml_priv; } ;
struct can_ml_priv {int dummy; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETDEV_ALIGN ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int /*<<< orphan*/  SLCAN_MAGIC ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int maxdev ; 
 struct slcan* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  slc_setup ; 
 struct net_device** slcan_devs ; 
 int /*<<< orphan*/  slcan_transmit ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static struct slcan *slc_alloc(void)
{
	int i;
	char name[IFNAMSIZ];
	struct net_device *dev = NULL;
	struct slcan       *sl;
	int size;

	for (i = 0; i < maxdev; i++) {
		dev = slcan_devs[i];
		if (dev == NULL)
			break;

	}

	/* Sorry, too many, all slots in use */
	if (i >= maxdev)
		return NULL;

	sprintf(name, "slcan%d", i);
	size = ALIGN(sizeof(*sl), NETDEV_ALIGN) + sizeof(struct can_ml_priv);
	dev = alloc_netdev(size, name, NET_NAME_UNKNOWN, slc_setup);
	if (!dev)
		return NULL;

	dev->base_addr  = i;
	sl = netdev_priv(dev);
	dev->ml_priv = (void *)sl + ALIGN(sizeof(*sl), NETDEV_ALIGN);

	/* Initialize channel control data */
	sl->magic = SLCAN_MAGIC;
	sl->dev	= dev;
	spin_lock_init(&sl->lock);
	INIT_WORK(&sl->tx_work, slcan_transmit);
	slcan_devs[i] = dev;

	return sl;
}