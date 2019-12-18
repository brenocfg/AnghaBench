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
struct qcom_phy {int /*<<< orphan*/  pipe_reset; int /*<<< orphan*/  pipe_clk; scalar_t__ base; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ PCIE2_PHY_RESET_CTRL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct qcom_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int qcom_pcie2_phy_power_off(struct phy *phy)
{
	struct qcom_phy *qphy = phy_get_drvdata(phy);
	u32 val;

	val = readl(qphy->base + PCIE2_PHY_RESET_CTRL);
	val |= BIT(0);
	writel(val, qphy->base + PCIE2_PHY_RESET_CTRL);

	clk_disable_unprepare(qphy->pipe_clk);
	reset_control_assert(qphy->pipe_reset);

	return 0;
}