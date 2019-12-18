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
struct dsa_switch {int dummy; } ;
struct bcm_sf2_priv {int irq1_stat; int irq1_mask; TYPE_1__* port_sts; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int link; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTRL2_CPU_CLEAR ; 
 int /*<<< orphan*/  INTRL2_CPU_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  P7_IRQ_OFF ; 
 int P_LINK_DOWN_IRQ (int /*<<< orphan*/ ) ; 
 int P_LINK_UP_IRQ (int /*<<< orphan*/ ) ; 
 struct bcm_sf2_priv* bcm_sf2_to_priv (struct dsa_switch*) ; 
 int /*<<< orphan*/  dsa_port_phylink_mac_change (struct dsa_switch*,int,int) ; 
 int intrl2_1_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intrl2_1_writel (struct bcm_sf2_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bcm_sf2_switch_1_isr(int irq, void *dev_id)
{
	struct dsa_switch *ds = dev_id;
	struct bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);

	priv->irq1_stat = intrl2_1_readl(priv, INTRL2_CPU_STATUS) &
				~priv->irq1_mask;
	intrl2_1_writel(priv, priv->irq1_stat, INTRL2_CPU_CLEAR);

	if (priv->irq1_stat & P_LINK_UP_IRQ(P7_IRQ_OFF)) {
		priv->port_sts[7].link = true;
		dsa_port_phylink_mac_change(ds, 7, true);
	}
	if (priv->irq1_stat & P_LINK_DOWN_IRQ(P7_IRQ_OFF)) {
		priv->port_sts[7].link = false;
		dsa_port_phylink_mac_change(ds, 7, false);
	}

	return IRQ_HANDLED;
}