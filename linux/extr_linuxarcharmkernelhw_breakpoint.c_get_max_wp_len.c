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
typedef  int u8 ;
typedef  int u32 ;
struct arch_hw_breakpoint_ctrl {int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  ctrl ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_BASE_WCR ; 
 int /*<<< orphan*/  ARM_BASE_WVR ; 
 int /*<<< orphan*/  ARM_BREAKPOINT_LEN_8 ; 
 scalar_t__ ARM_DEBUG_ARCH_V7_ECP14 ; 
 scalar_t__ debug_arch ; 
 int encode_ctrl_reg (struct arch_hw_breakpoint_ctrl) ; 
 int /*<<< orphan*/  memset (struct arch_hw_breakpoint_ctrl*,int /*<<< orphan*/ ,int) ; 
 int read_wb_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_wb_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 get_max_wp_len(void)
{
	u32 ctrl_reg;
	struct arch_hw_breakpoint_ctrl ctrl;
	u8 size = 4;

	if (debug_arch < ARM_DEBUG_ARCH_V7_ECP14)
		goto out;

	memset(&ctrl, 0, sizeof(ctrl));
	ctrl.len = ARM_BREAKPOINT_LEN_8;
	ctrl_reg = encode_ctrl_reg(ctrl);

	write_wb_reg(ARM_BASE_WVR, 0);
	write_wb_reg(ARM_BASE_WCR, ctrl_reg);
	if ((read_wb_reg(ARM_BASE_WCR) & ctrl_reg) == ctrl_reg)
		size = 8;

out:
	return size;
}