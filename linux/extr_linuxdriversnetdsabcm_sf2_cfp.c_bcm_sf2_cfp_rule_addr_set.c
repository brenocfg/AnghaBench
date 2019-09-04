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
typedef  unsigned int u32 ;
struct bcm_sf2_priv {unsigned int num_cfp_rules; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_CFP_ACC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int XCESS_ADDR_MASK ; 
 unsigned int XCESS_ADDR_SHIFT ; 
 unsigned int core_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_writel (struct bcm_sf2_priv*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bcm_sf2_cfp_rule_addr_set(struct bcm_sf2_priv *priv,
					     unsigned int addr)
{
	u32 reg;

	WARN_ON(addr >= priv->num_cfp_rules);

	reg = core_readl(priv, CORE_CFP_ACC);
	reg &= ~(XCESS_ADDR_MASK << XCESS_ADDR_SHIFT);
	reg |= addr << XCESS_ADDR_SHIFT;
	core_writel(priv, reg, CORE_CFP_ACC);
}