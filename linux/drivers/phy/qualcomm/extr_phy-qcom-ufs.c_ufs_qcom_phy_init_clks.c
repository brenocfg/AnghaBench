#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ufs_qcom_phy {int /*<<< orphan*/  ref_clk; TYPE_1__* dev; int /*<<< orphan*/  ref_clk_parent; int /*<<< orphan*/  ref_clk_src; int /*<<< orphan*/  rx_iface_clk; int /*<<< orphan*/  tx_iface_clk; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ufs_qcom_phy_clk_get (TYPE_1__*,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int ufs_qcom_phy_clk_get (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 

int ufs_qcom_phy_init_clks(struct ufs_qcom_phy *phy_common)
{
	int err;

	if (of_device_is_compatible(phy_common->dev->of_node,
				"qcom,msm8996-ufs-phy-qmp-14nm"))
		goto skip_txrx_clk;

	err = ufs_qcom_phy_clk_get(phy_common->dev, "tx_iface_clk",
				   &phy_common->tx_iface_clk);
	if (err)
		goto out;

	err = ufs_qcom_phy_clk_get(phy_common->dev, "rx_iface_clk",
				   &phy_common->rx_iface_clk);
	if (err)
		goto out;

skip_txrx_clk:
	err = ufs_qcom_phy_clk_get(phy_common->dev, "ref_clk_src",
				   &phy_common->ref_clk_src);
	if (err)
		goto out;

	/*
	 * "ref_clk_parent" is optional hence don't abort init if it's not
	 * found.
	 */
	__ufs_qcom_phy_clk_get(phy_common->dev, "ref_clk_parent",
				   &phy_common->ref_clk_parent, false);

	err = ufs_qcom_phy_clk_get(phy_common->dev, "ref_clk",
				   &phy_common->ref_clk);

out:
	return err;
}