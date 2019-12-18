#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ num_instances; } ;
struct amdgpu_device {TYPE_1__ sdma; } ;

/* Variables and functions */
 scalar_t__ RREG32_SDMA (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SDMA0_STATUS_REG__IDLE_MASK ; 
 int /*<<< orphan*/  mmSDMA0_STATUS_REG ; 

__attribute__((used)) static bool sdma_v4_0_is_idle(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	u32 i;

	for (i = 0; i < adev->sdma.num_instances; i++) {
		u32 tmp = RREG32_SDMA(i, mmSDMA0_STATUS_REG);

		if (!(tmp & SDMA0_STATUS_REG__IDLE_MASK))
			return false;
	}

	return true;
}