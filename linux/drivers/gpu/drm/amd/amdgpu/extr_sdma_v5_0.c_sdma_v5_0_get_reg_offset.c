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
typedef  scalar_t__ u32 ;
struct amdgpu_device {scalar_t__*** reg_offset; } ;

/* Variables and functions */
 size_t GC_HWIP ; 
 scalar_t__ SDMA0_HYP_DEC_REG_END ; 
 scalar_t__ SDMA0_HYP_DEC_REG_START ; 
 scalar_t__ SDMA1_HYP_DEC_REG_OFFSET ; 
 scalar_t__ SDMA1_REG_OFFSET ; 

__attribute__((used)) static u32 sdma_v5_0_get_reg_offset(struct amdgpu_device *adev, u32 instance, u32 internal_offset)
{
	u32 base;

	if (internal_offset >= SDMA0_HYP_DEC_REG_START &&
	    internal_offset <= SDMA0_HYP_DEC_REG_END) {
		base = adev->reg_offset[GC_HWIP][0][1];
		if (instance == 1)
			internal_offset += SDMA1_HYP_DEC_REG_OFFSET;
	} else {
		base = adev->reg_offset[GC_HWIP][0][0];
		if (instance == 1)
			internal_offset += SDMA1_REG_OFFSET;
	}

	return base + internal_offset;
}