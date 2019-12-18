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
struct unimac_mdio_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_CMD ; 
 int /*<<< orphan*/  MDIO_START_BUSY ; 
 int /*<<< orphan*/  unimac_mdio_readl (struct unimac_mdio_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unimac_mdio_writel (struct unimac_mdio_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void unimac_mdio_start(struct unimac_mdio_priv *priv)
{
	u32 reg;

	reg = unimac_mdio_readl(priv, MDIO_CMD);
	reg |= MDIO_START_BUSY;
	unimac_mdio_writel(priv, reg, MDIO_CMD);
}