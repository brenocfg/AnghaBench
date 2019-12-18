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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u32 ;
struct dpu_rm {int dummy; } ;
struct dpu_encoder_hw_resources {scalar_t__* intfs; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  DPU_HW_BLK_INTF ; 
 scalar_t__ INTF_0 ; 
 scalar_t__ INTF_MODE_NONE ; 
 int _dpu_rm_reserve_intf (struct dpu_rm*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _dpu_rm_reserve_intf_related_hw(
		struct dpu_rm *rm,
		uint32_t enc_id,
		struct dpu_encoder_hw_resources *hw_res)
{
	int i, ret = 0;
	u32 id;

	for (i = 0; i < ARRAY_SIZE(hw_res->intfs); i++) {
		if (hw_res->intfs[i] == INTF_MODE_NONE)
			continue;
		id = i + INTF_0;
		ret = _dpu_rm_reserve_intf(rm, enc_id, id,
				DPU_HW_BLK_INTF);
		if (ret)
			return ret;
	}

	return ret;
}