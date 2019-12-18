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
struct amdgpu_device {int*** reg_offset; } ;

/* Variables and functions */
 size_t SDMA0_HWIP ; 
 size_t SDMA1_HWIP ; 
 size_t SDMA2_HWIP ; 
 size_t SDMA3_HWIP ; 
 size_t SDMA4_HWIP ; 
 size_t SDMA5_HWIP ; 
 size_t SDMA6_HWIP ; 
 size_t SDMA7_HWIP ; 

__attribute__((used)) static u32 sdma_v4_0_get_reg_offset(struct amdgpu_device *adev,
		u32 instance, u32 offset)
{
	switch (instance) {
	case 0:
		return (adev->reg_offset[SDMA0_HWIP][0][0] + offset);
	case 1:
		return (adev->reg_offset[SDMA1_HWIP][0][1] + offset);
	case 2:
		return (adev->reg_offset[SDMA2_HWIP][0][1] + offset);
	case 3:
		return (adev->reg_offset[SDMA3_HWIP][0][1] + offset);
	case 4:
		return (adev->reg_offset[SDMA4_HWIP][0][1] + offset);
	case 5:
		return (adev->reg_offset[SDMA5_HWIP][0][1] + offset);
	case 6:
		return (adev->reg_offset[SDMA6_HWIP][0][1] + offset);
	case 7:
		return (adev->reg_offset[SDMA7_HWIP][0][1] + offset);
	default:
		break;
	}
	return 0;
}