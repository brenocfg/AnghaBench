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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct bcm_enet_priv {int /*<<< orphan*/  mib_update_task; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_IRMASK_REG ; 
 int ENET_IR_MIB ; 
 int /*<<< orphan*/  ENET_IR_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int enet_readl (struct bcm_enet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_writel (struct bcm_enet_priv*,int,int /*<<< orphan*/ ) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t bcm_enet_isr_mac(int irq, void *dev_id)
{
	struct net_device *dev;
	struct bcm_enet_priv *priv;
	u32 stat;

	dev = dev_id;
	priv = netdev_priv(dev);

	stat = enet_readl(priv, ENET_IR_REG);
	if (!(stat & ENET_IR_MIB))
		return IRQ_NONE;

	/* clear & mask interrupt */
	enet_writel(priv, ENET_IR_MIB, ENET_IR_REG);
	enet_writel(priv, 0, ENET_IRMASK_REG);

	/* read mib registers in workqueue */
	schedule_work(&priv->mib_update_task);

	return IRQ_HANDLED;
}