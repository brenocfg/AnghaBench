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
struct net_device {unsigned char* dev_addr; } ;
struct bmac_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MADD0 ; 
 int /*<<< orphan*/  MADD1 ; 
 int /*<<< orphan*/  MADD2 ; 
 int /*<<< orphan*/  XXDEBUG (char*) ; 
 int /*<<< orphan*/  bmwrite (struct net_device*,int /*<<< orphan*/ ,unsigned short) ; 
 struct bmac_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int bmac_set_address(struct net_device *dev, void *addr)
{
	struct bmac_data *bp = netdev_priv(dev);
	unsigned char *p = addr;
	unsigned short *pWord16;
	unsigned long flags;
	int i;

	XXDEBUG(("bmac: enter set_address\n"));
	spin_lock_irqsave(&bp->lock, flags);

	for (i = 0; i < 6; ++i) {
		dev->dev_addr[i] = p[i];
	}
	/* load up the hardware address */
	pWord16  = (unsigned short *)dev->dev_addr;
	bmwrite(dev, MADD0, *pWord16++);
	bmwrite(dev, MADD1, *pWord16++);
	bmwrite(dev, MADD2, *pWord16);

	spin_unlock_irqrestore(&bp->lock, flags);
	XXDEBUG(("bmac: exit set_address\n"));
	return 0;
}