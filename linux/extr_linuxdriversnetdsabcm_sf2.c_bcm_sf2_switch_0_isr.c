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
struct dsa_switch {int dummy; } ;
struct bcm_sf2_priv {int irq0_stat; int irq0_mask; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTRL2_CPU_CLEAR ; 
 int /*<<< orphan*/  INTRL2_CPU_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct bcm_sf2_priv* bcm_sf2_to_priv (struct dsa_switch*) ; 
 int intrl2_0_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intrl2_0_writel (struct bcm_sf2_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bcm_sf2_switch_0_isr(int irq, void *dev_id)
{
	struct dsa_switch *ds = dev_id;
	struct bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);

	priv->irq0_stat = intrl2_0_readl(priv, INTRL2_CPU_STATUS) &
				~priv->irq0_mask;
	intrl2_0_writel(priv, priv->irq0_stat, INTRL2_CPU_CLEAR);

	return IRQ_HANDLED;
}