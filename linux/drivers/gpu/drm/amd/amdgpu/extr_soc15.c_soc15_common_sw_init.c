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
struct amdgpu_device {TYPE_1__* df_funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sw_init ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  xgpu_ai_mailbox_add_irq_id (struct amdgpu_device*) ; 

__attribute__((used)) static int soc15_common_sw_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (amdgpu_sriov_vf(adev))
		xgpu_ai_mailbox_add_irq_id(adev);

	adev->df_funcs->sw_init(adev);

	return 0;
}