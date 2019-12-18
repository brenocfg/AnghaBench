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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; int /*<<< orphan*/  addr_len; } ;
struct amd8111e_priv {int /*<<< orphan*/  lock; scalar_t__ mmio; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ PADR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct amd8111e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int amd8111e_set_mac_address(struct net_device *dev, void *p)
{
	struct amd8111e_priv *lp = netdev_priv(dev);
	int i;
	struct sockaddr *addr = p;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);
	spin_lock_irq(&lp->lock);
	/* Setting the MAC address to the device */
	for (i = 0; i < ETH_ALEN; i++)
		writeb( dev->dev_addr[i], lp->mmio + PADR + i );

	spin_unlock_irq(&lp->lock);

	return 0;
}