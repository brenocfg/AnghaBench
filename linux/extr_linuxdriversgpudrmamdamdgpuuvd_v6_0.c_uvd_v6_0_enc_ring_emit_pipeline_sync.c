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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  sync_seq; } ;
struct amdgpu_ring {TYPE_1__ fence_drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_ENC_CMD_WAIT_GE ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uvd_v6_0_enc_ring_emit_pipeline_sync(struct amdgpu_ring *ring)
{
	uint32_t seq = ring->fence_drv.sync_seq;
	uint64_t addr = ring->fence_drv.gpu_addr;

	amdgpu_ring_write(ring, HEVC_ENC_CMD_WAIT_GE);
	amdgpu_ring_write(ring, lower_32_bits(addr));
	amdgpu_ring_write(ring, upper_32_bits(addr));
	amdgpu_ring_write(ring, seq);
}