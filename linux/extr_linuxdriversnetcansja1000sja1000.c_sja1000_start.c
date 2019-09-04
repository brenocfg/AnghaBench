#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ state; } ;
struct sja1000_priv {int (* read_reg ) (struct sja1000_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_reg ) (struct sja1000_priv*,int /*<<< orphan*/ ,int) ;TYPE_1__ can; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CAN_STATE_STOPPED ; 
 int CDR_PELICAN ; 
 int /*<<< orphan*/  SJA1000_CDR ; 
 int /*<<< orphan*/  SJA1000_ECC ; 
 int /*<<< orphan*/  SJA1000_IR ; 
 int /*<<< orphan*/  SJA1000_RXERR ; 
 int /*<<< orphan*/  SJA1000_TXERR ; 
 int /*<<< orphan*/  chipset_init (struct net_device*) ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_normal_mode (struct net_device*) ; 
 int /*<<< orphan*/  set_reset_mode (struct net_device*) ; 
 int stub1 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int stub4 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 
 int stub5 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sja1000_start(struct net_device *dev)
{
	struct sja1000_priv *priv = netdev_priv(dev);

	/* leave reset mode */
	if (priv->can.state != CAN_STATE_STOPPED)
		set_reset_mode(dev);

	/* Initialize chip if uninitialized at this stage */
	if (!(priv->read_reg(priv, SJA1000_CDR) & CDR_PELICAN))
		chipset_init(dev);

	/* Clear error counters and error code capture */
	priv->write_reg(priv, SJA1000_TXERR, 0x0);
	priv->write_reg(priv, SJA1000_RXERR, 0x0);
	priv->read_reg(priv, SJA1000_ECC);

	/* clear interrupt flags */
	priv->read_reg(priv, SJA1000_IR);

	/* leave reset mode */
	set_normal_mode(dev);
}