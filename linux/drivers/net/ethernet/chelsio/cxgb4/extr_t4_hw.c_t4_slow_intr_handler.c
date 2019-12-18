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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int CIM_F ; 
 int CPL_SWITCH_F ; 
 int EDC0_F ; 
 int EDC1_F ; 
 int GLBL_INTR_MASK ; 
 int LE_F ; 
 int MA_F ; 
 int MC1_F ; 
 int MC_F ; 
 int /*<<< orphan*/  MEM_EDC0 ; 
 int /*<<< orphan*/  MEM_EDC1 ; 
 int /*<<< orphan*/  MEM_MC ; 
 int /*<<< orphan*/  MEM_MC1 ; 
 int MPS_F ; 
 int NCSI_F ; 
 int PCIE_F ; 
 int PL_F ; 
 int /*<<< orphan*/  PL_INT_CAUSE_A ; 
 int /*<<< orphan*/  PL_INT_ENABLE_A ; 
 int PM_RX_F ; 
 int PM_TX_F ; 
 int SGE_F ; 
 int SMB_F ; 
 int TP_F ; 
 int ULP_RX_F ; 
 int ULP_TX_F ; 
 int XGMAC0_F ; 
 int XGMAC1_F ; 
 int XGMAC_KR0_F ; 
 int XGMAC_KR1_F ; 
 int /*<<< orphan*/  cim_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  cplsw_intr_handler (struct adapter*) ; 
 scalar_t__ is_t5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  ma_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  mem_intr_handler (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  ncsi_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  pcie_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  pl_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  pmrx_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  pmtx_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  sge_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  smb_intr_handler (struct adapter*) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tp_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  ulprx_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  ulptx_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  xgmac_intr_handler (struct adapter*,int) ; 

int t4_slow_intr_handler(struct adapter *adapter)
{
	/* There are rare cases where a PL_INT_CAUSE bit may end up getting
	 * set when the corresponding PL_INT_ENABLE bit isn't set.  It's
	 * easiest just to mask that case here.
	 */
	u32 raw_cause = t4_read_reg(adapter, PL_INT_CAUSE_A);
	u32 enable = t4_read_reg(adapter, PL_INT_ENABLE_A);
	u32 cause = raw_cause & enable;

	if (!(cause & GLBL_INTR_MASK))
		return 0;
	if (cause & CIM_F)
		cim_intr_handler(adapter);
	if (cause & MPS_F)
		mps_intr_handler(adapter);
	if (cause & NCSI_F)
		ncsi_intr_handler(adapter);
	if (cause & PL_F)
		pl_intr_handler(adapter);
	if (cause & SMB_F)
		smb_intr_handler(adapter);
	if (cause & XGMAC0_F)
		xgmac_intr_handler(adapter, 0);
	if (cause & XGMAC1_F)
		xgmac_intr_handler(adapter, 1);
	if (cause & XGMAC_KR0_F)
		xgmac_intr_handler(adapter, 2);
	if (cause & XGMAC_KR1_F)
		xgmac_intr_handler(adapter, 3);
	if (cause & PCIE_F)
		pcie_intr_handler(adapter);
	if (cause & MC_F)
		mem_intr_handler(adapter, MEM_MC);
	if (is_t5(adapter->params.chip) && (cause & MC1_F))
		mem_intr_handler(adapter, MEM_MC1);
	if (cause & EDC0_F)
		mem_intr_handler(adapter, MEM_EDC0);
	if (cause & EDC1_F)
		mem_intr_handler(adapter, MEM_EDC1);
	if (cause & LE_F)
		le_intr_handler(adapter);
	if (cause & TP_F)
		tp_intr_handler(adapter);
	if (cause & MA_F)
		ma_intr_handler(adapter);
	if (cause & PM_TX_F)
		pmtx_intr_handler(adapter);
	if (cause & PM_RX_F)
		pmrx_intr_handler(adapter);
	if (cause & ULP_RX_F)
		ulprx_intr_handler(adapter);
	if (cause & CPL_SWITCH_F)
		cplsw_intr_handler(adapter);
	if (cause & SGE_F)
		sge_intr_handler(adapter);
	if (cause & ULP_TX_F)
		ulptx_intr_handler(adapter);

	/* Clear the interrupts just processed for which we are the master. */
	t4_write_reg(adapter, PL_INT_CAUSE_A, raw_cause & GLBL_INTR_MASK);
	(void)t4_read_reg(adapter, PL_INT_CAUSE_A); /* flush */
	return 1;
}