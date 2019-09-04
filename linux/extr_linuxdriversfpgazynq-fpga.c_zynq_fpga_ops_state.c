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
typedef  int u32 ;
struct zynq_fpga_priv {int /*<<< orphan*/  clk; } ;
struct fpga_manager {struct zynq_fpga_priv* priv; } ;
typedef  enum fpga_mgr_states { ____Placeholder_fpga_mgr_states } fpga_mgr_states ;

/* Variables and functions */
 int FPGA_MGR_STATE_OPERATING ; 
 int FPGA_MGR_STATE_UNKNOWN ; 
 int /*<<< orphan*/  INT_STS_OFFSET ; 
 int IXR_PCFG_DONE_MASK ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int zynq_fpga_read (struct zynq_fpga_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum fpga_mgr_states zynq_fpga_ops_state(struct fpga_manager *mgr)
{
	int err;
	u32 intr_status;
	struct zynq_fpga_priv *priv;

	priv = mgr->priv;

	err = clk_enable(priv->clk);
	if (err)
		return FPGA_MGR_STATE_UNKNOWN;

	intr_status = zynq_fpga_read(priv, INT_STS_OFFSET);
	clk_disable(priv->clk);

	if (intr_status & IXR_PCFG_DONE_MASK)
		return FPGA_MGR_STATE_OPERATING;

	return FPGA_MGR_STATE_UNKNOWN;
}