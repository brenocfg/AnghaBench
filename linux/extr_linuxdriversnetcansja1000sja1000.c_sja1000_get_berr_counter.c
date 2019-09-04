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
struct sja1000_priv {int /*<<< orphan*/  (* read_reg ) (struct sja1000_priv*,int /*<<< orphan*/ ) ;} ;
struct net_device {int dummy; } ;
struct can_berr_counter {int /*<<< orphan*/  rxerr; int /*<<< orphan*/  txerr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SJA1000_RXERR ; 
 int /*<<< orphan*/  SJA1000_TXERR ; 
 struct sja1000_priv* netdev_priv (struct net_device const*) ; 
 int /*<<< orphan*/  stub1 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sja1000_get_berr_counter(const struct net_device *dev,
				    struct can_berr_counter *bec)
{
	struct sja1000_priv *priv = netdev_priv(dev);

	bec->txerr = priv->read_reg(priv, SJA1000_TXERR);
	bec->rxerr = priv->read_reg(priv, SJA1000_RXERR);

	return 0;
}