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

/* Variables and functions */
 int CMDQ_CODE_WFE ; 
 scalar_t__ CMDQ_OP_CODE_MASK ; 
 int CMDQ_OP_CODE_SHIFT ; 
 int CMDQ_WFE_UPDATE ; 
 int CMDQ_WFE_WAIT ; 
 int CMDQ_WFE_WAIT_VALUE ; 

__attribute__((used)) static bool cmdq_command_is_wfe(u64 cmd)
{
	u64 wfe_option = CMDQ_WFE_UPDATE | CMDQ_WFE_WAIT | CMDQ_WFE_WAIT_VALUE;
	u64 wfe_op = (u64)(CMDQ_CODE_WFE << CMDQ_OP_CODE_SHIFT) << 32;
	u64 wfe_mask = (u64)CMDQ_OP_CODE_MASK << 32 | 0xffffffff;

	return ((cmd & wfe_mask) == (wfe_op | wfe_option));
}