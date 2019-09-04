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
struct amdgpu_ring {struct amdgpu_device* adev; } ;
struct amdgpu_sdma_instance {struct amdgpu_ring ring; } ;
struct TYPE_2__ {int num_instances; struct amdgpu_sdma_instance* instance; } ;
struct amdgpu_device {TYPE_1__ sdma; } ;

/* Variables and functions */
 int AMDGPU_MAX_SDMA_INSTANCES ; 

__attribute__((used)) static inline struct amdgpu_sdma_instance *
amdgpu_get_sdma_instance(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	int i;

	for (i = 0; i < adev->sdma.num_instances; i++)
		if (&adev->sdma.instance[i].ring == ring)
			break;

	if (i < AMDGPU_MAX_SDMA_INSTANCES)
		return &adev->sdma.instance[i];
	else
		return NULL;
}