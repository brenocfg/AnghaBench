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
struct socfpga_fpga_priv {int dummy; } ;

/* Variables and functions */
 int SOCFPGA_FPGMGR_MON_FPGA_POWER_ON ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_STAT_OFST ; 
 int SOCFPGA_FPGMGR_STAT_POWER_OFF ; 
 int SOCFPGA_FPGMGR_STAT_STATE_MASK ; 
 int socfpga_fpga_mon_status_get (struct socfpga_fpga_priv*) ; 
 int socfpga_fpga_readl (struct socfpga_fpga_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 socfpga_fpga_state_get(struct socfpga_fpga_priv *priv)
{
	u32 status = socfpga_fpga_mon_status_get(priv);

	if ((status & SOCFPGA_FPGMGR_MON_FPGA_POWER_ON) == 0)
		return SOCFPGA_FPGMGR_STAT_POWER_OFF;

	return socfpga_fpga_readl(priv, SOCFPGA_FPGMGR_STAT_OFST) &
		SOCFPGA_FPGMGR_STAT_STATE_MASK;
}