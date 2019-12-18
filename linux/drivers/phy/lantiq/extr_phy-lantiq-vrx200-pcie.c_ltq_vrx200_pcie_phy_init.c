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
struct phy {int dummy; } ;
struct ltq_vrx200_pcie_phy_priv {int rcu_ahb_endian_big_endian_mask; int /*<<< orphan*/  phy_reset; int /*<<< orphan*/  pcie_reset; int /*<<< orphan*/  rcu_ahb_endian_offset; int /*<<< orphan*/  rcu_regmap; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 scalar_t__ of_device_is_big_endian (int /*<<< orphan*/ ) ; 
 struct ltq_vrx200_pcie_phy_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ltq_vrx200_pcie_phy_init(struct phy *phy)
{
	struct ltq_vrx200_pcie_phy_priv *priv = phy_get_drvdata(phy);
	int ret;

	if (of_device_is_big_endian(priv->dev->of_node))
		regmap_update_bits(priv->rcu_regmap,
				   priv->rcu_ahb_endian_offset,
				   priv->rcu_ahb_endian_big_endian_mask,
				   priv->rcu_ahb_endian_big_endian_mask);
	else
		regmap_update_bits(priv->rcu_regmap,
				   priv->rcu_ahb_endian_offset,
				   priv->rcu_ahb_endian_big_endian_mask, 0x0);

	ret = reset_control_assert(priv->phy_reset);
	if (ret)
		goto err;

	udelay(1);

	ret = reset_control_deassert(priv->phy_reset);
	if (ret)
		goto err;

	udelay(1);

	ret = reset_control_deassert(priv->pcie_reset);
	if (ret)
		goto err_assert_phy_reset;

	/* Make sure PHY PLL is stable */
	usleep_range(20, 40);

	return 0;

err_assert_phy_reset:
	reset_control_assert(priv->phy_reset);
err:
	return ret;
}