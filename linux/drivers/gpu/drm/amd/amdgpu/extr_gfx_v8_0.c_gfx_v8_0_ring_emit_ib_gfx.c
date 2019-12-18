#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  unsigned int u32 ;
struct amdgpu_ring {int /*<<< orphan*/  adev; } ;
struct amdgpu_job {int dummy; } ;
struct amdgpu_ib {int flags; unsigned int length_dw; int gpu_addr; } ;

/* Variables and functions */
 int AMDGPU_IB_FLAG_CE ; 
 int AMDGPU_IB_FLAG_PREEMPT ; 
 unsigned int AMDGPU_JOB_GET_VMID (struct amdgpu_job*) ; 
 unsigned int INDIRECT_BUFFER_PRE_ENB (int) ; 
 unsigned int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_INDIRECT_BUFFER ; 
 int /*<<< orphan*/  PACKET3_INDIRECT_BUFFER_CONST ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,unsigned int) ; 
 scalar_t__ amdgpu_sriov_vf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfx_v8_0_ring_emit_de_meta (struct amdgpu_ring*) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void gfx_v8_0_ring_emit_ib_gfx(struct amdgpu_ring *ring,
					struct amdgpu_job *job,
					struct amdgpu_ib *ib,
					uint32_t flags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);
	u32 header, control = 0;

	if (ib->flags & AMDGPU_IB_FLAG_CE)
		header = PACKET3(PACKET3_INDIRECT_BUFFER_CONST, 2);
	else
		header = PACKET3(PACKET3_INDIRECT_BUFFER, 2);

	control |= ib->length_dw | (vmid << 24);

	if (amdgpu_sriov_vf(ring->adev) && (ib->flags & AMDGPU_IB_FLAG_PREEMPT)) {
		control |= INDIRECT_BUFFER_PRE_ENB(1);

		if (!(ib->flags & AMDGPU_IB_FLAG_CE))
			gfx_v8_0_ring_emit_de_meta(ring);
	}

	amdgpu_ring_write(ring, header);
	amdgpu_ring_write(ring,
#ifdef __BIG_ENDIAN
			  (2 << 0) |
#endif
			  (ib->gpu_addr & 0xFFFFFFFC));
	amdgpu_ring_write(ring, upper_32_bits(ib->gpu_addr) & 0xFFFF);
	amdgpu_ring_write(ring, control);
}