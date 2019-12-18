#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  max_texture_channel_caches; int /*<<< orphan*/  max_backends_per_se; int /*<<< orphan*/  max_sh_per_se; int /*<<< orphan*/  max_cu_per_sh; int /*<<< orphan*/  max_tile_pipes; int /*<<< orphan*/  max_shader_engines; } ;
union gfx_info {TYPE_3__ info; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct amdgpu_mode_info {TYPE_4__* atom_context; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_texture_channel_caches; int /*<<< orphan*/  max_backends_per_se; int /*<<< orphan*/  max_sh_per_se; int /*<<< orphan*/  max_cu_per_sh; int /*<<< orphan*/  max_tile_pipes; int /*<<< orphan*/  max_shader_engines; } ;
struct TYPE_6__ {TYPE_1__ config; } ;
struct amdgpu_device {TYPE_2__ gfx; struct amdgpu_mode_info mode_info; } ;
struct TYPE_8__ {scalar_t__ bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFX_Info ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_atom_parse_data_header (TYPE_4__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 

int amdgpu_atombios_get_gfx_info(struct amdgpu_device *adev)
{
	struct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, GFX_Info);
	uint8_t frev, crev;
	uint16_t data_offset;
	int ret = -EINVAL;

	if (amdgpu_atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset)) {
		union gfx_info *gfx_info = (union gfx_info *)
			(mode_info->atom_context->bios + data_offset);

		adev->gfx.config.max_shader_engines = gfx_info->info.max_shader_engines;
		adev->gfx.config.max_tile_pipes = gfx_info->info.max_tile_pipes;
		adev->gfx.config.max_cu_per_sh = gfx_info->info.max_cu_per_sh;
		adev->gfx.config.max_sh_per_se = gfx_info->info.max_sh_per_se;
		adev->gfx.config.max_backends_per_se = gfx_info->info.max_backends_per_se;
		adev->gfx.config.max_texture_channel_caches =
			gfx_info->info.max_texture_channel_caches;

		ret = 0;
	}
	return ret;
}