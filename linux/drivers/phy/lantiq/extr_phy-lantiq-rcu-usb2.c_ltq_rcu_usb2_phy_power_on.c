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
struct phy {int dummy; } ;
struct ltq_rcu_usb2_priv {int /*<<< orphan*/  phy_gate_clk; int /*<<< orphan*/  phy_reset; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct ltq_rcu_usb2_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltq_rcu_usb2_phy_power_on(struct phy *phy)
{
	struct ltq_rcu_usb2_priv *priv = phy_get_drvdata(phy);
	struct device *dev = priv->dev;
	int ret;

	reset_control_deassert(priv->phy_reset);

	ret = clk_prepare_enable(priv->phy_gate_clk);
	if (ret)
		dev_err(dev, "failed to enable PHY gate\n");

	return ret;
}