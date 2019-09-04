#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* instance; } ;
struct TYPE_4__ {int /*<<< orphan*/ * buffer_funcs_ring; int /*<<< orphan*/ * buffer_funcs; } ;
struct amdgpu_device {TYPE_3__ sdma; TYPE_1__ mman; } ;
struct TYPE_5__ {int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdma_v3_0_buffer_funcs ; 

__attribute__((used)) static void sdma_v3_0_set_buffer_funcs(struct amdgpu_device *adev)
{
	if (adev->mman.buffer_funcs == NULL) {
		adev->mman.buffer_funcs = &sdma_v3_0_buffer_funcs;
		adev->mman.buffer_funcs_ring = &adev->sdma.instance[0].ring;
	}
}