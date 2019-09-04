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
struct TYPE_4__ {int num_rings; TYPE_1__* ring; } ;
struct amdgpu_device {TYPE_2__ vce; } ;
struct TYPE_3__ {int me; int /*<<< orphan*/ * funcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  vce_v2_0_ring_funcs ; 

__attribute__((used)) static void vce_v2_0_set_ring_funcs(struct amdgpu_device *adev)
{
	int i;

	for (i = 0; i < adev->vce.num_rings; i++) {
		adev->vce.ring[i].funcs = &vce_v2_0_ring_funcs;
		adev->vce.ring[i].me = i;
	}
}