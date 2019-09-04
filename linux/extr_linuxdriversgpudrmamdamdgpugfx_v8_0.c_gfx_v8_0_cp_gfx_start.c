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
struct TYPE_5__ {int max_hw_contexts; TYPE_1__** rb_config; } ;
struct TYPE_6__ {TYPE_2__ config; struct amdgpu_ring* gfx_ring; } ;
struct amdgpu_device {TYPE_3__ gfx; } ;
struct TYPE_4__ {int raster_config; int raster_config_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_PARTITION_BASE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int PACKET3_BASE_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKET3_CLEAR_STATE ; 
 int /*<<< orphan*/  PACKET3_CONTEXT_CONTROL ; 
 int PACKET3_PREAMBLE_BEGIN_CLEAR_STATE ; 
 int /*<<< orphan*/  PACKET3_PREAMBLE_CNTL ; 
 int PACKET3_PREAMBLE_END_CLEAR_STATE ; 
 int /*<<< orphan*/  PACKET3_SET_BASE ; 
 int /*<<< orphan*/  PACKET3_SET_CONTEXT_REG ; 
 int PACKET3_SET_CONTEXT_REG_START ; 
 scalar_t__ SECT_CONTEXT ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int amdgpu_ring_alloc (struct amdgpu_ring*,scalar_t__) ; 
 int /*<<< orphan*/  amdgpu_ring_commit (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  gfx_v8_0_cp_gfx_enable (struct amdgpu_device*,int) ; 
 scalar_t__ gfx_v8_0_get_csb_size (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmCP_DEVICE_ID ; 
 int /*<<< orphan*/  mmCP_ENDIAN_SWAP ; 
 int /*<<< orphan*/  mmCP_MAX_CONTEXT ; 
 int mmPA_SC_RASTER_CONFIG ; 
 struct cs_section_def* vi_cs_data ; 

__attribute__((used)) static int gfx_v8_0_cp_gfx_start(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring = &adev->gfx.gfx_ring[0];
	const struct cs_section_def *sect = NULL;
	const struct cs_extent_def *ext = NULL;
	int r, i;

	/* init the CP */
	WREG32(mmCP_MAX_CONTEXT, adev->gfx.config.max_hw_contexts - 1);
	WREG32(mmCP_ENDIAN_SWAP, 0);
	WREG32(mmCP_DEVICE_ID, 1);

	gfx_v8_0_cp_gfx_enable(adev, true);

	r = amdgpu_ring_alloc(ring, gfx_v8_0_get_csb_size(adev) + 4);
	if (r) {
		DRM_ERROR("amdgpu: cp failed to lock ring (%d).\n", r);
		return r;
	}

	/* clear state buffer */
	amdgpu_ring_write(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	amdgpu_ring_write(ring, PACKET3_PREAMBLE_BEGIN_CLEAR_STATE);

	amdgpu_ring_write(ring, PACKET3(PACKET3_CONTEXT_CONTROL, 1));
	amdgpu_ring_write(ring, 0x80000000);
	amdgpu_ring_write(ring, 0x80000000);

	for (sect = vi_cs_data; sect->section != NULL; ++sect) {
		for (ext = sect->section; ext->extent != NULL; ++ext) {
			if (sect->id == SECT_CONTEXT) {
				amdgpu_ring_write(ring,
				       PACKET3(PACKET3_SET_CONTEXT_REG,
					       ext->reg_count));
				amdgpu_ring_write(ring,
				       ext->reg_index - PACKET3_SET_CONTEXT_REG_START);
				for (i = 0; i < ext->reg_count; i++)
					amdgpu_ring_write(ring, ext->extent[i]);
			}
		}
	}

	amdgpu_ring_write(ring, PACKET3(PACKET3_SET_CONTEXT_REG, 2));
	amdgpu_ring_write(ring, mmPA_SC_RASTER_CONFIG - PACKET3_SET_CONTEXT_REG_START);
	amdgpu_ring_write(ring, adev->gfx.config.rb_config[0][0].raster_config);
	amdgpu_ring_write(ring, adev->gfx.config.rb_config[0][0].raster_config_1);

	amdgpu_ring_write(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	amdgpu_ring_write(ring, PACKET3_PREAMBLE_END_CLEAR_STATE);

	amdgpu_ring_write(ring, PACKET3(PACKET3_CLEAR_STATE, 0));
	amdgpu_ring_write(ring, 0);

	/* init the CE partitions */
	amdgpu_ring_write(ring, PACKET3(PACKET3_SET_BASE, 2));
	amdgpu_ring_write(ring, PACKET3_BASE_INDEX(CE_PARTITION_BASE));
	amdgpu_ring_write(ring, 0x8000);
	amdgpu_ring_write(ring, 0x8000);

	amdgpu_ring_commit(ring);

	return 0;
}