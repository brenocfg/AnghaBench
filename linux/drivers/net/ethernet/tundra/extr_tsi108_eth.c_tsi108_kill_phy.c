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
struct tsi108_prv_data {scalar_t__ phy_ok; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMCR_PDOWN ; 
 int /*<<< orphan*/  MII_BMCR ; 
 struct tsi108_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tsi108_write_mii (struct tsi108_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsi108_kill_phy(struct net_device *dev)
{
	struct tsi108_prv_data *data = netdev_priv(dev);
	unsigned long flags;

	spin_lock_irqsave(&phy_lock, flags);
	tsi108_write_mii(data, MII_BMCR, BMCR_PDOWN);
	data->phy_ok = 0;
	spin_unlock_irqrestore(&phy_lock, flags);
}