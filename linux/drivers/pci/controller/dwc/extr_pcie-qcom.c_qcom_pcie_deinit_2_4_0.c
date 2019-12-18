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
struct qcom_pcie_resources_2_4_0 {int /*<<< orphan*/  clks; int /*<<< orphan*/  num_clks; int /*<<< orphan*/  ahb_reset; int /*<<< orphan*/  pwr_reset; int /*<<< orphan*/  axi_m_sticky_reset; int /*<<< orphan*/  phy_ahb_reset; int /*<<< orphan*/  phy_reset; int /*<<< orphan*/  pipe_sticky_reset; int /*<<< orphan*/  pipe_reset; int /*<<< orphan*/  axi_s_reset; int /*<<< orphan*/  axi_m_reset; } ;
struct TYPE_2__ {struct qcom_pcie_resources_2_4_0 v2_4_0; } ;
struct qcom_pcie {TYPE_1__ res; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_bulk_disable_unprepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcom_pcie_deinit_2_4_0(struct qcom_pcie *pcie)
{
	struct qcom_pcie_resources_2_4_0 *res = &pcie->res.v2_4_0;

	reset_control_assert(res->axi_m_reset);
	reset_control_assert(res->axi_s_reset);
	reset_control_assert(res->pipe_reset);
	reset_control_assert(res->pipe_sticky_reset);
	reset_control_assert(res->phy_reset);
	reset_control_assert(res->phy_ahb_reset);
	reset_control_assert(res->axi_m_sticky_reset);
	reset_control_assert(res->pwr_reset);
	reset_control_assert(res->ahb_reset);
	clk_bulk_disable_unprepare(res->num_clks, res->clks);
}