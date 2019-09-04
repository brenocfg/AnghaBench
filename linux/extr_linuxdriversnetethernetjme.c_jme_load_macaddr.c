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
typedef  int u32 ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct jme_adapter {int /*<<< orphan*/  macaddr_lock; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  JME_RXUMA_HI ; 
 int /*<<< orphan*/  JME_RXUMA_LO ; 
 int jread32 (struct jme_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
jme_load_macaddr(struct net_device *netdev)
{
	struct jme_adapter *jme = netdev_priv(netdev);
	unsigned char macaddr[ETH_ALEN];
	u32 val;

	spin_lock_bh(&jme->macaddr_lock);
	val = jread32(jme, JME_RXUMA_LO);
	macaddr[0] = (val >>  0) & 0xFF;
	macaddr[1] = (val >>  8) & 0xFF;
	macaddr[2] = (val >> 16) & 0xFF;
	macaddr[3] = (val >> 24) & 0xFF;
	val = jread32(jme, JME_RXUMA_HI);
	macaddr[4] = (val >>  0) & 0xFF;
	macaddr[5] = (val >>  8) & 0xFF;
	memcpy(netdev->dev_addr, macaddr, ETH_ALEN);
	spin_unlock_bh(&jme->macaddr_lock);
}