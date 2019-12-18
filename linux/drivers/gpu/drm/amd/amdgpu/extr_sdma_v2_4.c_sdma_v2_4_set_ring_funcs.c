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
struct TYPE_6__ {int num_instances; TYPE_2__* instance; } ;
struct amdgpu_device {TYPE_3__ sdma; } ;
struct TYPE_4__ {int me; int /*<<< orphan*/ * funcs; } ;
struct TYPE_5__ {TYPE_1__ ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdma_v2_4_ring_funcs ; 

__attribute__((used)) static void sdma_v2_4_set_ring_funcs(struct amdgpu_device *adev)
{
	int i;

	for (i = 0; i < adev->sdma.num_instances; i++) {
		adev->sdma.instance[i].ring.funcs = &sdma_v2_4_ring_funcs;
		adev->sdma.instance[i].ring.me = i;
	}
}