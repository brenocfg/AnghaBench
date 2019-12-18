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
struct TYPE_2__ {int harvest_config; int num_rings; } ;
struct amdgpu_device {TYPE_1__ vce; } ;

/* Variables and functions */
 int AMDGPU_VCE_HARVEST_VCE0 ; 
 int AMDGPU_VCE_HARVEST_VCE1 ; 
 int ENOENT ; 
 int vce_v3_0_get_harvest_config (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vce_v3_0_set_irq_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vce_v3_0_set_ring_funcs (struct amdgpu_device*) ; 

__attribute__((used)) static int vce_v3_0_early_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	adev->vce.harvest_config = vce_v3_0_get_harvest_config(adev);

	if ((adev->vce.harvest_config &
	     (AMDGPU_VCE_HARVEST_VCE0 | AMDGPU_VCE_HARVEST_VCE1)) ==
	    (AMDGPU_VCE_HARVEST_VCE0 | AMDGPU_VCE_HARVEST_VCE1))
		return -ENOENT;

	adev->vce.num_rings = 3;

	vce_v3_0_set_ring_funcs(adev);
	vce_v3_0_set_irq_funcs(adev);

	return 0;
}