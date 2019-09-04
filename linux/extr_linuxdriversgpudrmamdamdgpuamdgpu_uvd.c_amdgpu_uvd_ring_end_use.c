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
struct amdgpu_ring {TYPE_2__* adev; } ;
struct TYPE_3__ {int /*<<< orphan*/  idle_work; } ;
struct TYPE_4__ {TYPE_1__ uvd; } ;

/* Variables and functions */
 int /*<<< orphan*/  UVD_IDLE_TIMEOUT ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (TYPE_2__*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void amdgpu_uvd_ring_end_use(struct amdgpu_ring *ring)
{
	if (!amdgpu_sriov_vf(ring->adev))
		schedule_delayed_work(&ring->adev->uvd.idle_work, UVD_IDLE_TIMEOUT);
}