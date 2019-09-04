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
struct intr_info {int member_0; char* member_1; int member_2; int member_3; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
#define  BLKRDCTLINT_F 163 
#define  BLKRDEEPROMINT_F 162 
#define  BLKRDPLINT_F 161 
#define  BLKWRBOOTINT_F 160 
#define  BLKWRCTLINT_F 159 
#define  BLKWREEPROMINT_F 158 
#define  BLKWRFLASHINT_F 157 
#define  BLKWRPLINT_F 156 
 int /*<<< orphan*/  CIM_HOST_INT_CAUSE_A ; 
 int /*<<< orphan*/  CIM_HOST_UPACC_INT_CAUSE_A ; 
#define  CIM_IBQ_INTR 155 
#define  CIM_OBQ_INTR 154 
#define  ILLRDBEINT_F 153 
#define  ILLRDINT_F 152 
#define  ILLTRANSINT_F 151 
#define  ILLWRBEINT_F 150 
#define  ILLWRINT_F 149 
#define  MBHOSTPARERR_F 148 
#define  MBUPPARERR_F 147 
 int /*<<< orphan*/  PCIE_FW_A ; 
 int PCIE_FW_ERR_F ; 
 scalar_t__ PCIE_FW_EVAL_CRASH ; 
 scalar_t__ PCIE_FW_EVAL_G (int) ; 
#define  PREFDROPINT_F 146 
#define  REQOVRLOOKUPINT_F 145 
#define  RSPOVRLOOKUPINT_F 144 
#define  RSVDSPACEINT_F 143 
#define  SGLRDBOOTINT_F 142 
#define  SGLRDCTLINT_F 141 
#define  SGLRDEEPROMINT_F 140 
#define  SGLRDFLASHINT_F 139 
#define  SGLRDPLINT_F 138 
#define  SGLWRBOOTINT_F 137 
#define  SGLWRCTLINT_F 136 
#define  SGLWREEPROMINT_F 135 
#define  SGLWRFLASHINT_F 134 
#define  SGLWRPLINT_F 133 
#define  TIEQINPARERRINT_F 132 
#define  TIEQOUTPARERRINT_F 131 
#define  TIMEOUTINT_F 130 
#define  TIMEOUTMAINT_F 129 
#define  TIMER0INT_F 128 
 int /*<<< orphan*/  t4_fatal_err (struct adapter*) ; 
 int t4_handle_intr_status (struct adapter*,int /*<<< orphan*/ ,struct intr_info const*) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_report_fw_error (struct adapter*) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void cim_intr_handler(struct adapter *adapter)
{
	static const struct intr_info cim_intr_info[] = {
		{ PREFDROPINT_F, "CIM control register prefetch drop", -1, 1 },
		{ CIM_OBQ_INTR, "CIM OBQ parity error", -1, 1 },
		{ CIM_IBQ_INTR, "CIM IBQ parity error", -1, 1 },
		{ MBUPPARERR_F, "CIM mailbox uP parity error", -1, 1 },
		{ MBHOSTPARERR_F, "CIM mailbox host parity error", -1, 1 },
		{ TIEQINPARERRINT_F, "CIM TIEQ outgoing parity error", -1, 1 },
		{ TIEQOUTPARERRINT_F, "CIM TIEQ incoming parity error", -1, 1 },
		{ TIMER0INT_F, "CIM TIMER0 interrupt", -1, 1 },
		{ 0 }
	};
	static const struct intr_info cim_upintr_info[] = {
		{ RSVDSPACEINT_F, "CIM reserved space access", -1, 1 },
		{ ILLTRANSINT_F, "CIM illegal transaction", -1, 1 },
		{ ILLWRINT_F, "CIM illegal write", -1, 1 },
		{ ILLRDINT_F, "CIM illegal read", -1, 1 },
		{ ILLRDBEINT_F, "CIM illegal read BE", -1, 1 },
		{ ILLWRBEINT_F, "CIM illegal write BE", -1, 1 },
		{ SGLRDBOOTINT_F, "CIM single read from boot space", -1, 1 },
		{ SGLWRBOOTINT_F, "CIM single write to boot space", -1, 1 },
		{ BLKWRBOOTINT_F, "CIM block write to boot space", -1, 1 },
		{ SGLRDFLASHINT_F, "CIM single read from flash space", -1, 1 },
		{ SGLWRFLASHINT_F, "CIM single write to flash space", -1, 1 },
		{ BLKWRFLASHINT_F, "CIM block write to flash space", -1, 1 },
		{ SGLRDEEPROMINT_F, "CIM single EEPROM read", -1, 1 },
		{ SGLWREEPROMINT_F, "CIM single EEPROM write", -1, 1 },
		{ BLKRDEEPROMINT_F, "CIM block EEPROM read", -1, 1 },
		{ BLKWREEPROMINT_F, "CIM block EEPROM write", -1, 1 },
		{ SGLRDCTLINT_F, "CIM single read from CTL space", -1, 1 },
		{ SGLWRCTLINT_F, "CIM single write to CTL space", -1, 1 },
		{ BLKRDCTLINT_F, "CIM block read from CTL space", -1, 1 },
		{ BLKWRCTLINT_F, "CIM block write to CTL space", -1, 1 },
		{ SGLRDPLINT_F, "CIM single read from PL space", -1, 1 },
		{ SGLWRPLINT_F, "CIM single write to PL space", -1, 1 },
		{ BLKRDPLINT_F, "CIM block read from PL space", -1, 1 },
		{ BLKWRPLINT_F, "CIM block write to PL space", -1, 1 },
		{ REQOVRLOOKUPINT_F, "CIM request FIFO overwrite", -1, 1 },
		{ RSPOVRLOOKUPINT_F, "CIM response FIFO overwrite", -1, 1 },
		{ TIMEOUTINT_F, "CIM PIF timeout", -1, 1 },
		{ TIMEOUTMAINT_F, "CIM PIF MA timeout", -1, 1 },
		{ 0 }
	};

	u32 val, fw_err;
	int fat;

	fw_err = t4_read_reg(adapter, PCIE_FW_A);
	if (fw_err & PCIE_FW_ERR_F)
		t4_report_fw_error(adapter);

	/* When the Firmware detects an internal error which normally
	 * wouldn't raise a Host Interrupt, it forces a CIM Timer0 interrupt
	 * in order to make sure the Host sees the Firmware Crash.  So
	 * if we have a Timer0 interrupt and don't see a Firmware Crash,
	 * ignore the Timer0 interrupt.
	 */

	val = t4_read_reg(adapter, CIM_HOST_INT_CAUSE_A);
	if (val & TIMER0INT_F)
		if (!(fw_err & PCIE_FW_ERR_F) ||
		    (PCIE_FW_EVAL_G(fw_err) != PCIE_FW_EVAL_CRASH))
			t4_write_reg(adapter, CIM_HOST_INT_CAUSE_A,
				     TIMER0INT_F);

	fat = t4_handle_intr_status(adapter, CIM_HOST_INT_CAUSE_A,
				    cim_intr_info) +
	      t4_handle_intr_status(adapter, CIM_HOST_UPACC_INT_CAUSE_A,
				    cim_upintr_info);
	if (fat)
		t4_fatal_err(adapter);
}