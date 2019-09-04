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
typedef  int u64 ;
typedef  int u32 ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 scalar_t__ GTT_BAR0_MAP_REG_IGU_CMD ; 
 int IGU_CMD_INT_ACK_BASE ; 
 int IGU_REG_SISR_MDPC_WMASK_LSB_UPPER ; 
 int IGU_REG_SISR_MDPC_WMASK_MSB_UPPER ; 
 int REG_RD (struct qed_hwfn*,scalar_t__) ; 

u64 qed_int_igu_read_sisr_reg(struct qed_hwfn *p_hwfn)
{
	u32 lsb_igu_cmd_addr = IGU_REG_SISR_MDPC_WMASK_LSB_UPPER -
			       IGU_CMD_INT_ACK_BASE;
	u32 msb_igu_cmd_addr = IGU_REG_SISR_MDPC_WMASK_MSB_UPPER -
			       IGU_CMD_INT_ACK_BASE;
	u32 intr_status_hi = 0, intr_status_lo = 0;
	u64 intr_status = 0;

	intr_status_lo = REG_RD(p_hwfn,
				GTT_BAR0_MAP_REG_IGU_CMD +
				lsb_igu_cmd_addr * 8);
	intr_status_hi = REG_RD(p_hwfn,
				GTT_BAR0_MAP_REG_IGU_CMD +
				msb_igu_cmd_addr * 8);
	intr_status = ((u64)intr_status_hi << 32) + (u64)intr_status_lo;

	return intr_status;
}