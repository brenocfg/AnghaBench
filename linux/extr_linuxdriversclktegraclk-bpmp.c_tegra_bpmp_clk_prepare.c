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
struct tegra_bpmp_clk_message {int /*<<< orphan*/  id; int /*<<< orphan*/  cmd; } ;
struct tegra_bpmp_clk {int /*<<< orphan*/  bpmp; int /*<<< orphan*/  id; } ;
struct clk_hw {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CLK_ENABLE ; 
 int /*<<< orphan*/  memset (struct tegra_bpmp_clk_message*,int /*<<< orphan*/ ,int) ; 
 int tegra_bpmp_clk_transfer (int /*<<< orphan*/ ,struct tegra_bpmp_clk_message*) ; 
 struct tegra_bpmp_clk* to_tegra_bpmp_clk (struct clk_hw*) ; 

__attribute__((used)) static int tegra_bpmp_clk_prepare(struct clk_hw *hw)
{
	struct tegra_bpmp_clk *clk = to_tegra_bpmp_clk(hw);
	struct tegra_bpmp_clk_message msg;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = CMD_CLK_ENABLE;
	msg.id = clk->id;

	return tegra_bpmp_clk_transfer(clk->bpmp, &msg);
}