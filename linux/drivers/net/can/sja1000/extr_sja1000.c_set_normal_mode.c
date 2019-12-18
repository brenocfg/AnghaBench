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
typedef  int u8 ;
struct TYPE_2__ {int ctrlmode; int /*<<< orphan*/  state; } ;
struct sja1000_priv {unsigned char (* read_reg ) (struct sja1000_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_reg ) (struct sja1000_priv*,int /*<<< orphan*/ ,int) ;TYPE_1__ can; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int CAN_CTRLMODE_BERR_REPORTING ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_PRESUME_ACK ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int IRQ_ALL ; 
 int IRQ_BEI ; 
 int MOD_LOM ; 
 unsigned char MOD_RM ; 
 int MOD_STM ; 
 int /*<<< orphan*/  SJA1000_IER ; 
 int /*<<< orphan*/  SJA1000_MOD ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 
 unsigned char stub1 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 unsigned char stub5 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void set_normal_mode(struct net_device *dev)
{
	struct sja1000_priv *priv = netdev_priv(dev);
	unsigned char status = priv->read_reg(priv, SJA1000_MOD);
	u8 mod_reg_val = 0x00;
	int i;

	for (i = 0; i < 100; i++) {
		/* check reset bit */
		if ((status & MOD_RM) == 0) {
			priv->can.state = CAN_STATE_ERROR_ACTIVE;
			/* enable interrupts */
			if (priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING)
				priv->write_reg(priv, SJA1000_IER, IRQ_ALL);
			else
				priv->write_reg(priv, SJA1000_IER,
						IRQ_ALL & ~IRQ_BEI);
			return;
		}

		/* set chip to normal mode */
		if (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
			mod_reg_val |= MOD_LOM;
		if (priv->can.ctrlmode & CAN_CTRLMODE_PRESUME_ACK)
			mod_reg_val |= MOD_STM;
		priv->write_reg(priv, SJA1000_MOD, mod_reg_val);

		udelay(10);

		status = priv->read_reg(priv, SJA1000_MOD);
	}

	netdev_err(dev, "setting SJA1000 into normal mode failed!\n");
}