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
struct net_device {int features; } ;
struct cp_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  cpcmd; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  CpCmd ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  RxChkSum ; 
 int /*<<< orphan*/  RxVlanOn ; 
 int /*<<< orphan*/  cpw16_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cp_set_features(struct net_device *dev, netdev_features_t features)
{
	struct cp_private *cp = netdev_priv(dev);
	unsigned long flags;

	if (!((dev->features ^ features) & NETIF_F_RXCSUM))
		return 0;

	spin_lock_irqsave(&cp->lock, flags);

	if (features & NETIF_F_RXCSUM)
		cp->cpcmd |= RxChkSum;
	else
		cp->cpcmd &= ~RxChkSum;

	if (features & NETIF_F_HW_VLAN_CTAG_RX)
		cp->cpcmd |= RxVlanOn;
	else
		cp->cpcmd &= ~RxVlanOn;

	cpw16_f(CpCmd, cp->cpcmd);
	spin_unlock_irqrestore(&cp->lock, flags);

	return 0;
}