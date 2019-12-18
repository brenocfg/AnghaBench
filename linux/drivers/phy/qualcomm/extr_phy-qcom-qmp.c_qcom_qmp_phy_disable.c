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
struct qmp_phy_cfg {scalar_t__ has_lane_rst; int /*<<< orphan*/  pwrdn_ctrl; int /*<<< orphan*/  start_ctrl; int /*<<< orphan*/ * regs; int /*<<< orphan*/  no_pcs_sw_reset; } ;
struct qmp_phy {int /*<<< orphan*/  lane_rst; int /*<<< orphan*/  pcs; int /*<<< orphan*/  pipe_clk; struct qcom_qmp* qmp; } ;
struct qcom_qmp {int phy_initialized; struct qmp_phy_cfg* cfg; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QPHY_POWER_DOWN_CONTROL ; 
 size_t QPHY_START_CTRL ; 
 size_t QPHY_SW_RESET ; 
 int /*<<< orphan*/  SW_RESET ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct qmp_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  qcom_qmp_phy_com_exit (struct qcom_qmp*) ; 
 int /*<<< orphan*/  qphy_clrbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qphy_setbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_qmp_phy_disable(struct phy *phy)
{
	struct qmp_phy *qphy = phy_get_drvdata(phy);
	struct qcom_qmp *qmp = qphy->qmp;
	const struct qmp_phy_cfg *cfg = qmp->cfg;

	clk_disable_unprepare(qphy->pipe_clk);

	/* PHY reset */
	if (!cfg->no_pcs_sw_reset)
		qphy_setbits(qphy->pcs, cfg->regs[QPHY_SW_RESET], SW_RESET);

	/* stop SerDes and Phy-Coding-Sublayer */
	qphy_clrbits(qphy->pcs, cfg->regs[QPHY_START_CTRL], cfg->start_ctrl);

	/* Put PHY into POWER DOWN state: active low */
	qphy_clrbits(qphy->pcs, QPHY_POWER_DOWN_CONTROL, cfg->pwrdn_ctrl);

	if (cfg->has_lane_rst)
		reset_control_assert(qphy->lane_rst);

	qcom_qmp_phy_com_exit(qmp);

	qmp->phy_initialized = false;

	return 0;
}