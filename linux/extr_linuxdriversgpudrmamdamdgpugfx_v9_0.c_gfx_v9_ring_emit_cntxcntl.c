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
typedef  int uint32_t ;
struct amdgpu_ring {int /*<<< orphan*/  adev; } ;

/* Variables and functions */
 int AMDGPU_HAVE_CTX_SWITCH ; 
 int AMDGPU_PREAMBLE_IB_PRESENT ; 
 int AMDGPU_PREAMBLE_IB_PRESENT_FIRST ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_CONTEXT_CONTROL ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 scalar_t__ amdgpu_sriov_vf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfx_v9_0_ring_emit_ce_meta (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  gfx_v9_0_ring_emit_tmz (struct amdgpu_ring*,int) ; 

__attribute__((used)) static void gfx_v9_ring_emit_cntxcntl(struct amdgpu_ring *ring, uint32_t flags)
{
	uint32_t dw2 = 0;

	if (amdgpu_sriov_vf(ring->adev))
		gfx_v9_0_ring_emit_ce_meta(ring);

	gfx_v9_0_ring_emit_tmz(ring, true);

	dw2 |= 0x80000000; /* set load_enable otherwise this package is just NOPs */
	if (flags & AMDGPU_HAVE_CTX_SWITCH) {
		/* set load_global_config & load_global_uconfig */
		dw2 |= 0x8001;
		/* set load_cs_sh_regs */
		dw2 |= 0x01000000;
		/* set load_per_context_state & load_gfx_sh_regs for GFX */
		dw2 |= 0x10002;

		/* set load_ce_ram if preamble presented */
		if (AMDGPU_PREAMBLE_IB_PRESENT & flags)
			dw2 |= 0x10000000;
	} else {
		/* still load_ce_ram if this is the first time preamble presented
		 * although there is no context switch happens.
		 */
		if (AMDGPU_PREAMBLE_IB_PRESENT_FIRST & flags)
			dw2 |= 0x10000000;
	}

	amdgpu_ring_write(ring, PACKET3(PACKET3_CONTEXT_CONTROL, 1));
	amdgpu_ring_write(ring, dw2);
	amdgpu_ring_write(ring, 0);
}