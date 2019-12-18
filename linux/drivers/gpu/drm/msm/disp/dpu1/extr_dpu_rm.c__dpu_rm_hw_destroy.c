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
typedef  enum dpu_hw_blk_type { ____Placeholder_dpu_hw_blk_type } dpu_hw_blk_type ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*,int) ; 
#define  DPU_HW_BLK_CTL 134 
#define  DPU_HW_BLK_INTF 133 
#define  DPU_HW_BLK_LM 132 
#define  DPU_HW_BLK_MAX 131 
#define  DPU_HW_BLK_PINGPONG 130 
#define  DPU_HW_BLK_SSPP 129 
#define  DPU_HW_BLK_TOP 128 
 int /*<<< orphan*/  dpu_hw_ctl_destroy (void*) ; 
 int /*<<< orphan*/  dpu_hw_intf_destroy (void*) ; 
 int /*<<< orphan*/  dpu_hw_lm_destroy (void*) ; 
 int /*<<< orphan*/  dpu_hw_pingpong_destroy (void*) ; 

__attribute__((used)) static void _dpu_rm_hw_destroy(enum dpu_hw_blk_type type, void *hw)
{
	switch (type) {
	case DPU_HW_BLK_LM:
		dpu_hw_lm_destroy(hw);
		break;
	case DPU_HW_BLK_CTL:
		dpu_hw_ctl_destroy(hw);
		break;
	case DPU_HW_BLK_PINGPONG:
		dpu_hw_pingpong_destroy(hw);
		break;
	case DPU_HW_BLK_INTF:
		dpu_hw_intf_destroy(hw);
		break;
	case DPU_HW_BLK_SSPP:
		/* SSPPs are not managed by the resource manager */
	case DPU_HW_BLK_TOP:
		/* Top is a singleton, not managed in hw_blks list */
	case DPU_HW_BLK_MAX:
	default:
		DPU_ERROR("unsupported block type %d\n", type);
		break;
	}
}