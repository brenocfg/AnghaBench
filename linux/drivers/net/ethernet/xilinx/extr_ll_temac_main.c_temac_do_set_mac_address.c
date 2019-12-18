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
struct temac_local {int /*<<< orphan*/  indirect_lock; } ;
struct net_device {int* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  XTE_UAW0_OFFSET ; 
 int /*<<< orphan*/  XTE_UAW1_OFFSET ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  temac_indirect_out32_locked (struct temac_local*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void temac_do_set_mac_address(struct net_device *ndev)
{
	struct temac_local *lp = netdev_priv(ndev);
	unsigned long flags;

	/* set up unicast MAC address filter set its mac address */
	spin_lock_irqsave(lp->indirect_lock, flags);
	temac_indirect_out32_locked(lp, XTE_UAW0_OFFSET,
				    (ndev->dev_addr[0]) |
				    (ndev->dev_addr[1] << 8) |
				    (ndev->dev_addr[2] << 16) |
				    (ndev->dev_addr[3] << 24));
	/* There are reserved bits in EUAW1
	 * so don't affect them Set MAC bits [47:32] in EUAW1 */
	temac_indirect_out32_locked(lp, XTE_UAW1_OFFSET,
				    (ndev->dev_addr[4] & 0x000000ff) |
				    (ndev->dev_addr[5] << 8));
	spin_unlock_irqrestore(lp->indirect_lock, flags);
}