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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdma_v3_0_ctx_switch_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  sdma_v3_0_enable (struct amdgpu_device*,int) ; 

__attribute__((used)) static int sdma_v3_0_hw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	sdma_v3_0_ctx_switch_enable(adev, false);
	sdma_v3_0_enable(adev, false);

	return 0;
}