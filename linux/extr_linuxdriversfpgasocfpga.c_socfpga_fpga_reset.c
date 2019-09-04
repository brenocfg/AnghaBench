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
typedef  scalar_t__ u32 ;
struct socfpga_fpga_priv {int dummy; } ;
struct fpga_manager {struct socfpga_fpga_priv* priv; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_CTL_EN ; 
 scalar_t__ SOCFPGA_FPGMGR_CTL_NCFGPULL ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_CTL_OFST ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_STAT_RESET ; 
 int socfpga_fpga_cfg_mode_set (struct socfpga_fpga_priv*) ; 
 scalar_t__ socfpga_fpga_readl (struct socfpga_fpga_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socfpga_fpga_set_bitsl (struct socfpga_fpga_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ socfpga_fpga_wait_for_state (struct socfpga_fpga_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socfpga_fpga_writel (struct socfpga_fpga_priv*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int socfpga_fpga_reset(struct fpga_manager *mgr)
{
	struct socfpga_fpga_priv *priv = mgr->priv;
	u32 ctrl_reg, status;
	int ret;

	/*
	 * Step 1:
	 *  - Set CTRL.CFGWDTH, CTRL.CDRATIO to match cfg mode
	 *  - Set CTRL.NCE to 0
	 */
	ret = socfpga_fpga_cfg_mode_set(priv);
	if (ret)
		return ret;

	/* Step 2: Set CTRL.EN to 1 */
	socfpga_fpga_set_bitsl(priv, SOCFPGA_FPGMGR_CTL_OFST,
			       SOCFPGA_FPGMGR_CTL_EN);

	/* Step 3: Set CTRL.NCONFIGPULL to 1 to put FPGA in reset */
	ctrl_reg = socfpga_fpga_readl(priv, SOCFPGA_FPGMGR_CTL_OFST);
	ctrl_reg |= SOCFPGA_FPGMGR_CTL_NCFGPULL;
	socfpga_fpga_writel(priv, SOCFPGA_FPGMGR_CTL_OFST, ctrl_reg);

	/* Step 4: Wait for STATUS.MODE to report FPGA is in reset phase */
	status = socfpga_fpga_wait_for_state(priv, SOCFPGA_FPGMGR_STAT_RESET);

	/* Step 5: Set CONTROL.NCONFIGPULL to 0 to release FPGA from reset */
	ctrl_reg &= ~SOCFPGA_FPGMGR_CTL_NCFGPULL;
	socfpga_fpga_writel(priv, SOCFPGA_FPGMGR_CTL_OFST, ctrl_reg);

	/* Timeout waiting for reset */
	if (status)
		return -ETIMEDOUT;

	return 0;
}