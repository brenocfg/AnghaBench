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
struct phy {int dummy; } ;
struct histb_combphy_priv {scalar_t__ mmio; int /*<<< orphan*/  por_rst; int /*<<< orphan*/  ref_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMBPHY_BYPASS_CODEC ; 
 scalar_t__ COMBPHY_CFG_REG ; 
 int /*<<< orphan*/  COMBPHY_CLKREF_OUT_OEN ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int histb_combphy_set_mode (struct histb_combphy_priv*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  nano_register_write (struct histb_combphy_priv*,int,int) ; 
 struct histb_combphy_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int histb_combphy_init(struct phy *phy)
{
	struct histb_combphy_priv *priv = phy_get_drvdata(phy);
	u32 val;
	int ret;

	ret = histb_combphy_set_mode(priv);
	if (ret)
		return ret;

	/* Clear bypass bit to enable encoding/decoding */
	val = readl(priv->mmio + COMBPHY_CFG_REG);
	val &= ~COMBPHY_BYPASS_CODEC;
	writel(val, priv->mmio + COMBPHY_CFG_REG);

	ret = clk_prepare_enable(priv->ref_clk);
	if (ret)
		return ret;

	reset_control_deassert(priv->por_rst);

	/* Enable EP clock */
	val = readl(priv->mmio + COMBPHY_CFG_REG);
	val |= COMBPHY_CLKREF_OUT_OEN;
	writel(val, priv->mmio + COMBPHY_CFG_REG);

	/* Need to wait for EP clock stable */
	mdelay(5);

	/* Configure nano phy registers as suggested by vendor */
	nano_register_write(priv, 0x1, 0x8);
	nano_register_write(priv, 0xc, 0x9);
	nano_register_write(priv, 0x1a, 0x4);

	return 0;
}