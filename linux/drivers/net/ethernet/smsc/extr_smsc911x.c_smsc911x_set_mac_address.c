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
struct smsc911x_data {int generation; int /*<<< orphan*/  mac_lock; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EBUSY ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  smsc911x_set_hw_mac_address (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smsc911x_set_mac_address(struct net_device *dev, void *p)
{
	struct smsc911x_data *pdata = netdev_priv(dev);
	struct sockaddr *addr = p;

	/* On older hardware revisions we cannot change the mac address
	 * registers while receiving data.  Newer devices can safely change
	 * this at any time. */
	if (pdata->generation <= 1 && netif_running(dev))
		return -EBUSY;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(dev->dev_addr, addr->sa_data, ETH_ALEN);

	spin_lock_irq(&pdata->mac_lock);
	smsc911x_set_hw_mac_address(pdata, dev->dev_addr);
	spin_unlock_irq(&pdata->mac_lock);

	netdev_info(dev, "MAC Address: %pM\n", dev->dev_addr);

	return 0;
}