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
struct net_device {int dummy; } ;
struct ks_net {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ks_phy_reg (int) ; 
 int ks_rdreg16 (struct ks_net*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ks_net* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_phy_read(struct net_device *netdev, int phy_addr, int reg)
{
	struct ks_net *ks = netdev_priv(netdev);
	int ksreg;
	int result;

	ksreg = ks_phy_reg(reg);
	if (!ksreg)
		return 0x0;	/* no error return allowed, so use zero */

	mutex_lock(&ks->lock);
	result = ks_rdreg16(ks, ksreg);
	mutex_unlock(&ks->lock);

	return result;
}