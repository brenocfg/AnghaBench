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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int sync_seq; int /*<<< orphan*/  gpu_addr; } ;
struct amdgpu_ring {TYPE_1__ fence_drv; } ;

/* Variables and functions */
 int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_CMD ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_DATA0 ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_DATA1 ; 
 int /*<<< orphan*/  mmUVD_GP_SCRATCH8 ; 
 int /*<<< orphan*/  mmUVD_GP_SCRATCH9 ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uvd_v6_0_ring_emit_pipeline_sync(struct amdgpu_ring *ring)
{
	uint32_t seq = ring->fence_drv.sync_seq;
	uint64_t addr = ring->fence_drv.gpu_addr;

	amdgpu_ring_write(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA0, 0));
	amdgpu_ring_write(ring, lower_32_bits(addr));
	amdgpu_ring_write(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA1, 0));
	amdgpu_ring_write(ring, upper_32_bits(addr));
	amdgpu_ring_write(ring, PACKET0(mmUVD_GP_SCRATCH8, 0));
	amdgpu_ring_write(ring, 0xffffffff); /* mask */
	amdgpu_ring_write(ring, PACKET0(mmUVD_GP_SCRATCH9, 0));
	amdgpu_ring_write(ring, seq);
	amdgpu_ring_write(ring, PACKET0(mmUVD_GPCOM_VCPU_CMD, 0));
	amdgpu_ring_write(ring, 0xE);
}