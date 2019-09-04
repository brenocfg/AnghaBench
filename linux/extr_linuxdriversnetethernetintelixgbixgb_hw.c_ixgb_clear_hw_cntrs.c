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
struct ixgb_hw {scalar_t__ adapter_stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPRCH ; 
 int /*<<< orphan*/  BPRCL ; 
 int /*<<< orphan*/  BPTCH ; 
 int /*<<< orphan*/  BPTCL ; 
 int /*<<< orphan*/  CRCERRS ; 
 int /*<<< orphan*/  DC ; 
 int /*<<< orphan*/  ECBC ; 
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  GORCH ; 
 int /*<<< orphan*/  GORCL ; 
 int /*<<< orphan*/  GOTCH ; 
 int /*<<< orphan*/  GOTCL ; 
 int /*<<< orphan*/  GPRCH ; 
 int /*<<< orphan*/  GPRCL ; 
 int /*<<< orphan*/  GPTCH ; 
 int /*<<< orphan*/  GPTCL ; 
 int /*<<< orphan*/  IBIC ; 
 int /*<<< orphan*/  ICBC ; 
 int /*<<< orphan*/  IXGB_READ_REG (struct ixgb_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JPRCH ; 
 int /*<<< orphan*/  JPRCL ; 
 int /*<<< orphan*/  JPTCH ; 
 int /*<<< orphan*/  JPTCL ; 
 int /*<<< orphan*/  LFC ; 
 int /*<<< orphan*/  MCFRC ; 
 int /*<<< orphan*/  MCFTC ; 
 int /*<<< orphan*/  MPC ; 
 int /*<<< orphan*/  MPRCH ; 
 int /*<<< orphan*/  MPRCL ; 
 int /*<<< orphan*/  MPTCH ; 
 int /*<<< orphan*/  MPTCL ; 
 int /*<<< orphan*/  PFRC ; 
 int /*<<< orphan*/  PFTC ; 
 int /*<<< orphan*/  PLT64C ; 
 int /*<<< orphan*/  RFC ; 
 int /*<<< orphan*/  RJC ; 
 int /*<<< orphan*/  RLEC ; 
 int /*<<< orphan*/  RNBC ; 
 int /*<<< orphan*/  ROC ; 
 int /*<<< orphan*/  RUC ; 
 int /*<<< orphan*/  TORH ; 
 int /*<<< orphan*/  TORL ; 
 int /*<<< orphan*/  TOTH ; 
 int /*<<< orphan*/  TOTL ; 
 int /*<<< orphan*/  TPRH ; 
 int /*<<< orphan*/  TPRL ; 
 int /*<<< orphan*/  TPTH ; 
 int /*<<< orphan*/  TPTL ; 
 int /*<<< orphan*/  TSCTC ; 
 int /*<<< orphan*/  TSCTFC ; 
 int /*<<< orphan*/  UPRCH ; 
 int /*<<< orphan*/  UPRCL ; 
 int /*<<< orphan*/  UPTCH ; 
 int /*<<< orphan*/  UPTCL ; 
 int /*<<< orphan*/  VPRCH ; 
 int /*<<< orphan*/  VPRCL ; 
 int /*<<< orphan*/  VPTCH ; 
 int /*<<< orphan*/  VPTCL ; 
 int /*<<< orphan*/  XOFFRXC ; 
 int /*<<< orphan*/  XOFFTXC ; 
 int /*<<< orphan*/  XONRXC ; 
 int /*<<< orphan*/  XONTXC ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void
ixgb_clear_hw_cntrs(struct ixgb_hw *hw)
{
	volatile u32 temp_reg;

	ENTER();

	/* if we are stopped or resetting exit gracefully */
	if (hw->adapter_stopped) {
		pr_debug("Exiting because the adapter is stopped!!!\n");
		return;
	}

	temp_reg = IXGB_READ_REG(hw, TPRL);
	temp_reg = IXGB_READ_REG(hw, TPRH);
	temp_reg = IXGB_READ_REG(hw, GPRCL);
	temp_reg = IXGB_READ_REG(hw, GPRCH);
	temp_reg = IXGB_READ_REG(hw, BPRCL);
	temp_reg = IXGB_READ_REG(hw, BPRCH);
	temp_reg = IXGB_READ_REG(hw, MPRCL);
	temp_reg = IXGB_READ_REG(hw, MPRCH);
	temp_reg = IXGB_READ_REG(hw, UPRCL);
	temp_reg = IXGB_READ_REG(hw, UPRCH);
	temp_reg = IXGB_READ_REG(hw, VPRCL);
	temp_reg = IXGB_READ_REG(hw, VPRCH);
	temp_reg = IXGB_READ_REG(hw, JPRCL);
	temp_reg = IXGB_READ_REG(hw, JPRCH);
	temp_reg = IXGB_READ_REG(hw, GORCL);
	temp_reg = IXGB_READ_REG(hw, GORCH);
	temp_reg = IXGB_READ_REG(hw, TORL);
	temp_reg = IXGB_READ_REG(hw, TORH);
	temp_reg = IXGB_READ_REG(hw, RNBC);
	temp_reg = IXGB_READ_REG(hw, RUC);
	temp_reg = IXGB_READ_REG(hw, ROC);
	temp_reg = IXGB_READ_REG(hw, RLEC);
	temp_reg = IXGB_READ_REG(hw, CRCERRS);
	temp_reg = IXGB_READ_REG(hw, ICBC);
	temp_reg = IXGB_READ_REG(hw, ECBC);
	temp_reg = IXGB_READ_REG(hw, MPC);
	temp_reg = IXGB_READ_REG(hw, TPTL);
	temp_reg = IXGB_READ_REG(hw, TPTH);
	temp_reg = IXGB_READ_REG(hw, GPTCL);
	temp_reg = IXGB_READ_REG(hw, GPTCH);
	temp_reg = IXGB_READ_REG(hw, BPTCL);
	temp_reg = IXGB_READ_REG(hw, BPTCH);
	temp_reg = IXGB_READ_REG(hw, MPTCL);
	temp_reg = IXGB_READ_REG(hw, MPTCH);
	temp_reg = IXGB_READ_REG(hw, UPTCL);
	temp_reg = IXGB_READ_REG(hw, UPTCH);
	temp_reg = IXGB_READ_REG(hw, VPTCL);
	temp_reg = IXGB_READ_REG(hw, VPTCH);
	temp_reg = IXGB_READ_REG(hw, JPTCL);
	temp_reg = IXGB_READ_REG(hw, JPTCH);
	temp_reg = IXGB_READ_REG(hw, GOTCL);
	temp_reg = IXGB_READ_REG(hw, GOTCH);
	temp_reg = IXGB_READ_REG(hw, TOTL);
	temp_reg = IXGB_READ_REG(hw, TOTH);
	temp_reg = IXGB_READ_REG(hw, DC);
	temp_reg = IXGB_READ_REG(hw, PLT64C);
	temp_reg = IXGB_READ_REG(hw, TSCTC);
	temp_reg = IXGB_READ_REG(hw, TSCTFC);
	temp_reg = IXGB_READ_REG(hw, IBIC);
	temp_reg = IXGB_READ_REG(hw, RFC);
	temp_reg = IXGB_READ_REG(hw, LFC);
	temp_reg = IXGB_READ_REG(hw, PFRC);
	temp_reg = IXGB_READ_REG(hw, PFTC);
	temp_reg = IXGB_READ_REG(hw, MCFRC);
	temp_reg = IXGB_READ_REG(hw, MCFTC);
	temp_reg = IXGB_READ_REG(hw, XONRXC);
	temp_reg = IXGB_READ_REG(hw, XONTXC);
	temp_reg = IXGB_READ_REG(hw, XOFFRXC);
	temp_reg = IXGB_READ_REG(hw, XOFFTXC);
	temp_reg = IXGB_READ_REG(hw, RJC);
}