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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct sja1000_priv {unsigned char (* read_reg ) (struct sja1000_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_reg ) (struct sja1000_priv*,int /*<<< orphan*/ ,unsigned char) ;TYPE_1__ can; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 unsigned char IRQ_OFF ; 
 unsigned char MOD_RM ; 
 int /*<<< orphan*/  SJA1000_IER ; 
 int /*<<< orphan*/  SJA1000_MOD ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 
 unsigned char stub1 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct sja1000_priv*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  stub3 (struct sja1000_priv*,int /*<<< orphan*/ ,unsigned char) ; 
 unsigned char stub4 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void set_reset_mode(struct net_device *dev)
{
	struct sja1000_priv *priv = netdev_priv(dev);
	unsigned char status = priv->read_reg(priv, SJA1000_MOD);
	int i;

	/* disable interrupts */
	priv->write_reg(priv, SJA1000_IER, IRQ_OFF);

	for (i = 0; i < 100; i++) {
		/* check reset bit */
		if (status & MOD_RM) {
			priv->can.state = CAN_STATE_STOPPED;
			return;
		}

		/* reset chip */
		priv->write_reg(priv, SJA1000_MOD, MOD_RM);
		udelay(10);
		status = priv->read_reg(priv, SJA1000_MOD);
	}

	netdev_err(dev, "setting SJA1000 into reset mode failed!\n");
}