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
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct dev_priv {int /*<<< orphan*/  chip_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR0 ; 
 int /*<<< orphan*/  CSR0_STOP ; 
 int /*<<< orphan*/  CSR3 ; 
 int /*<<< orphan*/  CSR3_MASKALL ; 
 int /*<<< orphan*/  am79c961_ramtest (struct net_device*,int) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_rreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
am79c961_hw_init(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);

	spin_lock_irq(&priv->chip_lock);
	write_rreg (dev->base_addr, CSR0, CSR0_STOP);
	write_rreg (dev->base_addr, CSR3, CSR3_MASKALL);
	spin_unlock_irq(&priv->chip_lock);

	am79c961_ramtest(dev, 0x66);
	am79c961_ramtest(dev, 0x99);

	return 0;
}