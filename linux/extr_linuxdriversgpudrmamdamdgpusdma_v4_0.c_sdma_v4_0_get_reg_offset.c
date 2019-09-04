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
 size_t SDMA0_HWIP ; 
 size_t SDMA1_HWIP ; 

__attribute__((used)) static u32 sdma_v4_0_get_reg_offset(struct amdgpu_device *adev,
		u32 instance, u32 offset)
{
	return ( 0 == instance ? (adev->reg_offset[SDMA0_HWIP][0][0] + offset) :
			(adev->reg_offset[SDMA1_HWIP][0][0] + offset));
}