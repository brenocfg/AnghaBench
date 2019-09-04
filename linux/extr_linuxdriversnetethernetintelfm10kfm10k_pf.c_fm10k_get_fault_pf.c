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
struct fm10k_hw {int dummy; } ;
struct fm10k_fault {int address; int func; int type; void* specinfo; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 scalar_t__ FM10K_FAULT_ADDR_HI ; 
 scalar_t__ FM10K_FAULT_ADDR_LO ; 
 scalar_t__ FM10K_FAULT_FUNC ; 
 int FM10K_FAULT_FUNC_PF ; 
 int FM10K_FAULT_FUNC_TYPE_MASK ; 
 int FM10K_FAULT_FUNC_VALID ; 
 int FM10K_FAULT_FUNC_VF_MASK ; 
 int FM10K_FAULT_FUNC_VF_SHIFT ; 
 scalar_t__ FM10K_FAULT_SPECINFO ; 
#define  FM10K_FUM_FAULT 130 
#define  FM10K_PCA_FAULT 129 
#define  FM10K_THI_FAULT 128 
 void* fm10k_read_reg (struct fm10k_hw*,scalar_t__) ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,scalar_t__,int) ; 

__attribute__((used)) static s32 fm10k_get_fault_pf(struct fm10k_hw *hw, int type,
			      struct fm10k_fault *fault)
{
	u32 func;

	/* verify the fault register is in range and is aligned */
	switch (type) {
	case FM10K_PCA_FAULT:
	case FM10K_THI_FAULT:
	case FM10K_FUM_FAULT:
		break;
	default:
		return FM10K_ERR_PARAM;
	}

	/* only service faults that are valid */
	func = fm10k_read_reg(hw, type + FM10K_FAULT_FUNC);
	if (!(func & FM10K_FAULT_FUNC_VALID))
		return FM10K_ERR_PARAM;

	/* read remaining fields */
	fault->address = fm10k_read_reg(hw, type + FM10K_FAULT_ADDR_HI);
	fault->address <<= 32;
	fault->address = fm10k_read_reg(hw, type + FM10K_FAULT_ADDR_LO);
	fault->specinfo = fm10k_read_reg(hw, type + FM10K_FAULT_SPECINFO);

	/* clear valid bit to allow for next error */
	fm10k_write_reg(hw, type + FM10K_FAULT_FUNC, FM10K_FAULT_FUNC_VALID);

	/* Record which function triggered the error */
	if (func & FM10K_FAULT_FUNC_PF)
		fault->func = 0;
	else
		fault->func = 1 + ((func & FM10K_FAULT_FUNC_VF_MASK) >>
				   FM10K_FAULT_FUNC_VF_SHIFT);

	/* record fault type */
	fault->type = func & FM10K_FAULT_FUNC_TYPE_MASK;

	return 0;
}