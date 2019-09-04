#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_instances; TYPE_1__* instance; } ;
struct amdgpu_device {TYPE_2__ sdma; } ;
struct TYPE_3__ {int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_ring_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cik_sdma_free_microcode (struct amdgpu_device*) ; 

__attribute__((used)) static int cik_sdma_sw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int i;

	for (i = 0; i < adev->sdma.num_instances; i++)
		amdgpu_ring_fini(&adev->sdma.instance[i].ring);

	cik_sdma_free_microcode(adev);
	return 0;
}