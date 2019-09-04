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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct rvt_qp {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u64 hfi1_fault_tx(struct rvt_qp *qp, u8 opcode, u64 pbc)
{
#ifdef CONFIG_FAULT_INJECTION
	if ((opcode & IB_OPCODE_MSP) == IB_OPCODE_MSP)
		/*
		 * In order to drop non-IB traffic we
		 * set PbcInsertHrc to NONE (0x2).
		 * The packet will still be delivered
		 * to the receiving node but a
		 * KHdrHCRCErr (KDETH packet with a bad
		 * HCRC) will be triggered and the
		 * packet will not be delivered to the
		 * correct context.
		 */
		pbc |= (u64)PBC_IHCRC_NONE << PBC_INSERT_HCRC_SHIFT;
	else
		/*
		 * In order to drop regular verbs
		 * traffic we set the PbcTestEbp
		 * flag. The packet will still be
		 * delivered to the receiving node but
		 * a 'late ebp error' will be
		 * triggered and will be dropped.
		 */
		pbc |= PBC_TEST_EBP;
#endif
	return pbc;
}