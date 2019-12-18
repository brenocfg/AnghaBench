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
struct TYPE_2__ {int num_uvd_inst; } ;
struct amdgpu_device {TYPE_1__ uvd; } ;

/* Variables and functions */
 int /*<<< orphan*/  uvd_v4_2_set_irq_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  uvd_v4_2_set_ring_funcs (struct amdgpu_device*) ; 

__attribute__((used)) static int uvd_v4_2_early_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	adev->uvd.num_uvd_inst = 1;

	uvd_v4_2_set_ring_funcs(adev);
	uvd_v4_2_set_irq_funcs(adev);

	return 0;
}