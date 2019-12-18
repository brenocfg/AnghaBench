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
struct amdgpu_ring {int dummy; } ;
struct amdgpu_job {int dummy; } ;
struct amdgpu_ib {unsigned int length_dw; int /*<<< orphan*/  gpu_addr; } ;

/* Variables and functions */
 unsigned int AMDGPU_JOB_GET_VMID (struct amdgpu_job*) ; 
 unsigned int VCN_ENC_CMD_IB ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,unsigned int) ; 
 unsigned int lower_32_bits (int /*<<< orphan*/ ) ; 
 unsigned int upper_32_bits (int /*<<< orphan*/ ) ; 

void vcn_v2_0_enc_ring_emit_ib(struct amdgpu_ring *ring,
			       struct amdgpu_job *job,
			       struct amdgpu_ib *ib,
			       uint32_t flags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_ring_write(ring, VCN_ENC_CMD_IB);
	amdgpu_ring_write(ring, vmid);
	amdgpu_ring_write(ring, lower_32_bits(ib->gpu_addr));
	amdgpu_ring_write(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_write(ring, ib->length_dw);
}