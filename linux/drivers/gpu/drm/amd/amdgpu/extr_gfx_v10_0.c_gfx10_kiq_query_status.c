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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u64 ;
struct amdgpu_ring {int /*<<< orphan*/  doorbell_index; TYPE_1__* funcs; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_RING_TYPE_GFX ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_QUERY_STATUS ; 
 int PACKET3_QUERY_STATUS_COMMAND (int) ; 
 int PACKET3_QUERY_STATUS_CONTEXT_ID (int /*<<< orphan*/ ) ; 
 int PACKET3_QUERY_STATUS_DOORBELL_OFFSET (int /*<<< orphan*/ ) ; 
 int PACKET3_QUERY_STATUS_ENG_SEL (int) ; 
 int PACKET3_QUERY_STATUS_INTERRUPT_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfx10_kiq_query_status(struct amdgpu_ring *kiq_ring,
				   struct amdgpu_ring *ring,
				   u64 addr,
				   u64 seq)
{
	uint32_t eng_sel = ring->funcs->type == AMDGPU_RING_TYPE_GFX ? 4 : 0;

	amdgpu_ring_write(kiq_ring, PACKET3(PACKET3_QUERY_STATUS, 5));
	amdgpu_ring_write(kiq_ring,
			  PACKET3_QUERY_STATUS_CONTEXT_ID(0) |
			  PACKET3_QUERY_STATUS_INTERRUPT_SEL(0) |
			  PACKET3_QUERY_STATUS_COMMAND(2));
	amdgpu_ring_write(kiq_ring, /* Q_sel: 0, vmid: 0, engine: 0, num_Q: 1 */
			  PACKET3_QUERY_STATUS_DOORBELL_OFFSET(ring->doorbell_index) |
			  PACKET3_QUERY_STATUS_ENG_SEL(eng_sel));
	amdgpu_ring_write(kiq_ring, lower_32_bits(addr));
	amdgpu_ring_write(kiq_ring, upper_32_bits(addr));
	amdgpu_ring_write(kiq_ring, lower_32_bits(seq));
	amdgpu_ring_write(kiq_ring, upper_32_bits(seq));
}