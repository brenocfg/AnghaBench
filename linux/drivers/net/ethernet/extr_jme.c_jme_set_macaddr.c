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
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct jme_adapter {int /*<<< orphan*/  macaddr_lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  jme_set_unicastaddr (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jme_set_macaddr(struct net_device *netdev, void *p)
{
	struct jme_adapter *jme = netdev_priv(netdev);
	struct sockaddr *addr = p;

	if (netif_running(netdev))
		return -EBUSY;

	spin_lock_bh(&jme->macaddr_lock);
	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	jme_set_unicastaddr(netdev);
	spin_unlock_bh(&jme->macaddr_lock);

	return 0;
}