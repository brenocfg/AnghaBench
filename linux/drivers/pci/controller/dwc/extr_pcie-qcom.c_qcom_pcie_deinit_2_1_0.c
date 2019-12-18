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
struct qcom_pcie_resources_2_1_0 {int /*<<< orphan*/  supplies; int /*<<< orphan*/  phy_clk; int /*<<< orphan*/  core_clk; int /*<<< orphan*/  iface_clk; int /*<<< orphan*/  pci_reset; int /*<<< orphan*/  por_reset; int /*<<< orphan*/  ahb_reset; int /*<<< orphan*/  axi_reset; } ;
struct TYPE_2__ {struct qcom_pcie_resources_2_1_0 v2_1_0; } ;
struct qcom_pcie {TYPE_1__ res; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcom_pcie_deinit_2_1_0(struct qcom_pcie *pcie)
{
	struct qcom_pcie_resources_2_1_0 *res = &pcie->res.v2_1_0;

	reset_control_assert(res->pci_reset);
	reset_control_assert(res->axi_reset);
	reset_control_assert(res->ahb_reset);
	reset_control_assert(res->por_reset);
	reset_control_assert(res->pci_reset);
	clk_disable_unprepare(res->iface_clk);
	clk_disable_unprepare(res->core_clk);
	clk_disable_unprepare(res->phy_clk);
	regulator_bulk_disable(ARRAY_SIZE(res->supplies), res->supplies);
}