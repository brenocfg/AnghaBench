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
struct TYPE_2__ {scalar_t__ load_type; } ;
struct amdgpu_device {TYPE_1__ firmware; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_DIRECT ; 
 int /*<<< orphan*/  mes_v10_1_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mes_v10_1_free_ucode_buffers (struct amdgpu_device*) ; 

__attribute__((used)) static int mes_v10_1_hw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	mes_v10_1_enable(adev, false);

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_DIRECT)
		mes_v10_1_free_ucode_buffers(adev);

	return 0;
}