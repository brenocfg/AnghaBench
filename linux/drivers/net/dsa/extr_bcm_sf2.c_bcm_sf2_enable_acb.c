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
struct dsa_switch {int dummy; } ;
struct bcm_sf2_priv {int dummy; } ;

/* Variables and functions */
 int ACB_ALGORITHM ; 
 int /*<<< orphan*/  ACB_CONTROL ; 
 int ACB_EN ; 
 int ACB_FLUSH_MASK ; 
 int ACB_FLUSH_SHIFT ; 
 int acb_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acb_writel (struct bcm_sf2_priv*,int,int /*<<< orphan*/ ) ; 
 struct bcm_sf2_priv* bcm_sf2_to_priv (struct dsa_switch*) ; 

__attribute__((used)) static void bcm_sf2_enable_acb(struct dsa_switch *ds)
{
	struct bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	u32 reg;

	/* Enable ACB globally */
	reg = acb_readl(priv, ACB_CONTROL);
	reg |= (ACB_FLUSH_MASK << ACB_FLUSH_SHIFT);
	acb_writel(priv, reg, ACB_CONTROL);
	reg &= ~(ACB_FLUSH_MASK << ACB_FLUSH_SHIFT);
	reg |= ACB_EN | ACB_ALGORITHM;
	acb_writel(priv, reg, ACB_CONTROL);
}