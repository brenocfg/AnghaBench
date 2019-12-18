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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_ring {struct amdgpu_device* adev; } ;
struct amdgpu_job {int dummy; } ;
struct amdgpu_ib {unsigned int length_dw; int /*<<< orphan*/  gpu_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ib_size; int /*<<< orphan*/  ib_bar_high; int /*<<< orphan*/  ib_bar_low; int /*<<< orphan*/  ib_vmid; } ;
struct TYPE_4__ {TYPE_1__ internal; } ;
struct amdgpu_device {TYPE_2__ vcn; } ;

/* Variables and functions */
 unsigned int AMDGPU_JOB_GET_VMID (struct amdgpu_job*) ; 
 unsigned int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,unsigned int) ; 
 unsigned int lower_32_bits (int /*<<< orphan*/ ) ; 
 unsigned int upper_32_bits (int /*<<< orphan*/ ) ; 

void vcn_v2_0_dec_ring_emit_ib(struct amdgpu_ring *ring,
			       struct amdgpu_job *job,
			       struct amdgpu_ib *ib,
			       uint32_t flags)
{
	struct amdgpu_device *adev = ring->adev;
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_ring_write(ring, PACKET0(adev->vcn.internal.ib_vmid, 0));
	amdgpu_ring_write(ring, vmid);

	amdgpu_ring_write(ring,	PACKET0(adev->vcn.internal.ib_bar_low, 0));
	amdgpu_ring_write(ring, lower_32_bits(ib->gpu_addr));
	amdgpu_ring_write(ring,	PACKET0(adev->vcn.internal.ib_bar_high, 0));
	amdgpu_ring_write(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_write(ring,	PACKET0(adev->vcn.internal.ib_size, 0));
	amdgpu_ring_write(ring, ib->length_dw);
}