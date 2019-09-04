#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cs_section_def {scalar_t__ id; struct cs_extent_def* section; } ;
struct cs_extent_def {int* extent; int reg_count; int reg_index; } ;
struct amdgpu_ring {int dummy; } ;
struct TYPE_5__ {struct cs_section_def* cs_data; } ;
struct TYPE_4__ {int max_hw_contexts; } ;
struct TYPE_6__ {TYPE_2__ rlc; TYPE_1__ config; struct amdgpu_ring* gfx_ring; } ;
struct amdgpu_device {TYPE_3__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_PARTITION_BASE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int PACKET3_BASE_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKET3_CLEAR_STATE ; 
 int /*<<< orphan*/  PACKET3_ME_INITIALIZE ; 
 int PACKET3_ME_INITIALIZE_DEVICE_ID (int) ; 
 int PACKET3_PREAMBLE_BEGIN_CLEAR_STATE ; 
 int /*<<< orphan*/  PACKET3_PREAMBLE_CNTL ; 
 int PACKET3_PREAMBLE_END_CLEAR_STATE ; 
 int /*<<< orphan*/  PACKET3_SET_BASE ; 
 int /*<<< orphan*/  PACKET3_SET_CONTEXT_REG ; 
 int PACKET3_SET_CONTEXT_REG_START ; 
 scalar_t__ SECT_CONTEXT ; 
 int amdgpu_ring_alloc (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  amdgpu_ring_commit (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  gfx_v6_0_cp_gfx_enable (struct amdgpu_device*,int) ; 
 int gfx_v6_0_get_csb_size (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v6_0_cp_gfx_start(struct amdgpu_device *adev)
{
	const struct cs_section_def *sect = NULL;
	const struct cs_extent_def *ext = NULL;
	struct amdgpu_ring *ring = &adev->gfx.gfx_ring[0];
	int r, i;

	r = amdgpu_ring_alloc(ring, 7 + 4);
	if (r) {
		DRM_ERROR("amdgpu: cp failed to lock ring (%d).\n", r);
		return r;
	}
	amdgpu_ring_write(ring, PACKET3(PACKET3_ME_INITIALIZE, 5));
	amdgpu_ring_write(ring, 0x1);
	amdgpu_ring_write(ring, 0x0);
	amdgpu_ring_write(ring, adev->gfx.config.max_hw_contexts - 1);
	amdgpu_ring_write(ring, PACKET3_ME_INITIALIZE_DEVICE_ID(1));
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, 0);

	amdgpu_ring_write(ring, PACKET3(PACKET3_SET_BASE, 2));
	amdgpu_ring_write(ring, PACKET3_BASE_INDEX(CE_PARTITION_BASE));
	amdgpu_ring_write(ring, 0xc000);
	amdgpu_ring_write(ring, 0xe000);
	amdgpu_ring_commit(ring);

	gfx_v6_0_cp_gfx_enable(adev, true);

	r = amdgpu_ring_alloc(ring, gfx_v6_0_get_csb_size(adev) + 10);
	if (r) {
		DRM_ERROR("amdgpu: cp failed to lock ring (%d).\n", r);
		return r;
	}

	amdgpu_ring_write(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	amdgpu_ring_write(ring, PACKET3_PREAMBLE_BEGIN_CLEAR_STATE);

	for (sect = adev->gfx.rlc.cs_data; sect->section != NULL; ++sect) {
		for (ext = sect->section; ext->extent != NULL; ++ext) {
			if (sect->id == SECT_CONTEXT) {
				amdgpu_ring_write(ring,
						  PACKET3(PACKET3_SET_CONTEXT_REG, ext->reg_count));
				amdgpu_ring_write(ring, ext->reg_index - PACKET3_SET_CONTEXT_REG_START);
				for (i = 0; i < ext->reg_count; i++)
					amdgpu_ring_write(ring, ext->extent[i]);
			}
		}
	}

	amdgpu_ring_write(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	amdgpu_ring_write(ring, PACKET3_PREAMBLE_END_CLEAR_STATE);

	amdgpu_ring_write(ring, PACKET3(PACKET3_CLEAR_STATE, 0));
	amdgpu_ring_write(ring, 0);

	amdgpu_ring_write(ring, PACKET3(PACKET3_SET_CONTEXT_REG, 2));
	amdgpu_ring_write(ring, 0x00000316);
	amdgpu_ring_write(ring, 0x0000000e);
	amdgpu_ring_write(ring, 0x00000010);

	amdgpu_ring_commit(ring);

	return 0;
}