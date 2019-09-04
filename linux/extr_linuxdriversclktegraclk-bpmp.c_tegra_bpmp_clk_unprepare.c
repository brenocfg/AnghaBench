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
struct tegra_bpmp_clk_message {int /*<<< orphan*/  id; int /*<<< orphan*/  cmd; } ;
struct tegra_bpmp_clk {TYPE_1__* bpmp; int /*<<< orphan*/  id; } ;
struct clk_hw {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CLK_DISABLE ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct tegra_bpmp_clk_message*,int /*<<< orphan*/ ,int) ; 
 int tegra_bpmp_clk_transfer (TYPE_1__*,struct tegra_bpmp_clk_message*) ; 
 struct tegra_bpmp_clk* to_tegra_bpmp_clk (struct clk_hw*) ; 

__attribute__((used)) static void tegra_bpmp_clk_unprepare(struct clk_hw *hw)
{
	struct tegra_bpmp_clk *clk = to_tegra_bpmp_clk(hw);
	struct tegra_bpmp_clk_message msg;
	int err;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = CMD_CLK_DISABLE;
	msg.id = clk->id;

	err = tegra_bpmp_clk_transfer(clk->bpmp, &msg);
	if (err < 0)
		dev_err(clk->bpmp->dev, "failed to disable clock %s: %d\n",
			clk_hw_get_name(hw), err);
}