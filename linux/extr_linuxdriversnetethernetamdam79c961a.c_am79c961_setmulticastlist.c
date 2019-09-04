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
typedef  int u16 ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct dev_priv {int /*<<< orphan*/  chip_lock; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 scalar_t__ CSR0 ; 
 int CSR0_STOP ; 
 scalar_t__ CTRL1 ; 
 int CTRL1_SPND ; 
 scalar_t__ LADRL ; 
 scalar_t__ MODE ; 
 int am79c961_get_rx_mode (struct net_device*,int*) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nop () ; 
 int read_rreg (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_rreg (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void am79c961_setmulticastlist (struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	unsigned long flags;
	u16 multi_hash[4], mode = am79c961_get_rx_mode(dev, multi_hash);
	int i, stopped;

	spin_lock_irqsave(&priv->chip_lock, flags);

	stopped = read_rreg(dev->base_addr, CSR0) & CSR0_STOP;

	if (!stopped) {
		/*
		 * Put the chip into suspend mode
		 */
		write_rreg(dev->base_addr, CTRL1, CTRL1_SPND);

		/*
		 * Spin waiting for chip to report suspend mode
		 */
		while ((read_rreg(dev->base_addr, CTRL1) & CTRL1_SPND) == 0) {
			spin_unlock_irqrestore(&priv->chip_lock, flags);
			nop();
			spin_lock_irqsave(&priv->chip_lock, flags);
		}
	}

	/*
	 * Update the multicast hash table
	 */
	for (i = 0; i < ARRAY_SIZE(multi_hash); i++)
		write_rreg(dev->base_addr, i + LADRL, multi_hash[i]);

	/*
	 * Write the mode register
	 */
	write_rreg(dev->base_addr, MODE, mode);

	if (!stopped) {
		/*
		 * Put the chip back into running mode
		 */
		write_rreg(dev->base_addr, CTRL1, 0);
	}

	spin_unlock_irqrestore(&priv->chip_lock, flags);
}