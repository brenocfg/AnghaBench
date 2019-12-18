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
typedef  int /*<<< orphan*/  u8 ;
struct brcms_phy {TYPE_1__* sh; int /*<<< orphan*/  d11core; int /*<<< orphan*/  nphy_txpwrctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  physhim; int /*<<< orphan*/  corerev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 scalar_t__ D11REV_IS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MCTL_PHYLOCK ; 
 int /*<<< orphan*/  bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wlapi_bmac_mctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_txpwr_limit_to_tbl_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txpwrctrl_enable_nphy (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_txpwrctrl_pwr_setup_nphy (struct brcms_phy*) ; 

void wlc_phy_txpower_recalc_target_nphy(struct brcms_phy *pi)
{
	u8 tx_pwr_ctrl_state;
	wlc_phy_txpwr_limit_to_tbl_nphy(pi);
	wlc_phy_txpwrctrl_pwr_setup_nphy(pi);

	tx_pwr_ctrl_state = pi->nphy_txpwrctrl;

	if (D11REV_IS(pi->sh->corerev, 11) || D11REV_IS(pi->sh->corerev, 12)) {
		wlapi_bmac_mctrl(pi->sh->physhim, MCTL_PHYLOCK, MCTL_PHYLOCK);
		(void)bcma_read32(pi->d11core, D11REGOFFS(maccontrol));
		udelay(1);
	}

	wlc_phy_txpwrctrl_enable_nphy(pi, tx_pwr_ctrl_state);

	if (D11REV_IS(pi->sh->corerev, 11) || D11REV_IS(pi->sh->corerev, 12))
		wlapi_bmac_mctrl(pi->sh->physhim, MCTL_PHYLOCK, 0);
}