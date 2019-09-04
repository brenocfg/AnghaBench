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
typedef  int /*<<< orphan*/  u32 ;
struct bcm_sysport_priv {scalar_t__ is_lite; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SW_RESET ; 
 int /*<<< orphan*/  UMAC_CMD ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  umac_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umac_writel (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void umac_reset(struct bcm_sysport_priv *priv)
{
	u32 reg;

	if (priv->is_lite)
		return;

	reg = umac_readl(priv, UMAC_CMD);
	reg |= CMD_SW_RESET;
	umac_writel(priv, reg, UMAC_CMD);
	udelay(10);
	reg = umac_readl(priv, UMAC_CMD);
	reg &= ~CMD_SW_RESET;
	umac_writel(priv, reg, UMAC_CMD);
}