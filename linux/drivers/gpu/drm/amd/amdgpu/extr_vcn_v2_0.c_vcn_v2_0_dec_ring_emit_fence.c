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
typedef  int u64 ;
struct amdgpu_ring {struct amdgpu_device* adev; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  data1; int /*<<< orphan*/  data0; int /*<<< orphan*/  context_id; } ;
struct TYPE_4__ {TYPE_1__ internal; } ;
struct amdgpu_device {TYPE_2__ vcn; } ;

/* Variables and functions */
 unsigned int AMDGPU_FENCE_FLAG_64BIT ; 
 int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VCN_DEC_CMD_FENCE ; 
 int VCN_DEC_CMD_TRAP ; 
 int VCN_DEC_KMD_CMD ; 
 int /*<<< orphan*/  WARN_ON (unsigned int) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int upper_32_bits (int) ; 

void vcn_v2_0_dec_ring_emit_fence(struct amdgpu_ring *ring, u64 addr, u64 seq,
				unsigned flags)
{
	struct amdgpu_device *adev = ring->adev;

	WARN_ON(flags & AMDGPU_FENCE_FLAG_64BIT);
	amdgpu_ring_write(ring, PACKET0(adev->vcn.internal.context_id, 0));
	amdgpu_ring_write(ring, seq);

	amdgpu_ring_write(ring, PACKET0(adev->vcn.internal.data0, 0));
	amdgpu_ring_write(ring, addr & 0xffffffff);

	amdgpu_ring_write(ring, PACKET0(adev->vcn.internal.data1, 0));
	amdgpu_ring_write(ring, upper_32_bits(addr) & 0xff);

	amdgpu_ring_write(ring, PACKET0(adev->vcn.internal.cmd, 0));
	amdgpu_ring_write(ring, VCN_DEC_KMD_CMD | (VCN_DEC_CMD_FENCE << 1));

	amdgpu_ring_write(ring, PACKET0(adev->vcn.internal.data0, 0));
	amdgpu_ring_write(ring, 0);

	amdgpu_ring_write(ring, PACKET0(adev->vcn.internal.data1, 0));
	amdgpu_ring_write(ring, 0);

	amdgpu_ring_write(ring, PACKET0(adev->vcn.internal.cmd, 0));

	amdgpu_ring_write(ring, VCN_DEC_KMD_CMD | (VCN_DEC_CMD_TRAP << 1));
}