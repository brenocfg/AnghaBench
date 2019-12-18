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
struct gswip_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  rcu_regmap; } ;
struct gswip_gphy_fw {int /*<<< orphan*/  reset; int /*<<< orphan*/  clk_gate; int /*<<< orphan*/  fw_addr_offset; int /*<<< orphan*/  fw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gswip_gphy_fw_remove(struct gswip_priv *priv,
				 struct gswip_gphy_fw *gphy_fw)
{
	int ret;

	/* check if the device was fully probed */
	if (!gphy_fw->fw_name)
		return;

	ret = regmap_write(priv->rcu_regmap, gphy_fw->fw_addr_offset, 0);
	if (ret)
		dev_err(priv->dev, "can not reset GPHY FW pointer");

	clk_disable_unprepare(gphy_fw->clk_gate);

	reset_control_put(gphy_fw->reset);
}