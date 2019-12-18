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
typedef  int u32 ;
struct TYPE_4__ {int num_pipes; int num_banks; int max_compress_frags; int num_rb_per_se; int num_se; int pipe_interleave_size; } ;
struct TYPE_6__ {int max_hw_contexts; int sc_prim_fifo_size_frontend; int sc_prim_fifo_size_backend; int sc_hiz_tile_fifo_size; int sc_earlyz_tile_fifo_size; int gb_addr_config; int max_tile_pipes; TYPE_1__ gb_addr_config_fields; } ;
struct TYPE_5__ {TYPE_3__ config; int /*<<< orphan*/ * funcs; } ;
struct amdgpu_device {int asic_type; int rev_id; TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CHIP_ARCTURUS 133 
#define  CHIP_RAVEN 132 
#define  CHIP_RENOIR 131 
#define  CHIP_VEGA10 130 
#define  CHIP_VEGA12 129 
#define  CHIP_VEGA20 128 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  GB_ADDR_CONFIG ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  MAX_COMPRESSED_FRAGS ; 
 int /*<<< orphan*/  NUM_BANKS ; 
 int /*<<< orphan*/  NUM_PIPES ; 
 int /*<<< orphan*/  NUM_RB_PER_SE ; 
 int /*<<< orphan*/  NUM_SHADER_ENGINES ; 
 int /*<<< orphan*/  PIPE_INTERLEAVE_SIZE ; 
 int RAVEN2_GB_ADDR_CONFIG_GOLDEN ; 
 int RAVEN_GB_ADDR_CONFIG_GOLDEN ; 
 int REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VEGA10_GB_ADDR_CONFIG_GOLDEN ; 
 int VEGA12_GB_ADDR_CONFIG_GOLDEN ; 
 int amdgpu_atomfirmware_get_gfx_info (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_gfx_funcs ; 
 int /*<<< orphan*/  mmGB_ADDR_CONFIG ; 

__attribute__((used)) static int gfx_v9_0_gpu_early_init(struct amdgpu_device *adev)
{
	u32 gb_addr_config;
	int err;

	adev->gfx.funcs = &gfx_v9_0_gfx_funcs;

	switch (adev->asic_type) {
	case CHIP_VEGA10:
		adev->gfx.config.max_hw_contexts = 8;
		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x4C0;
		gb_addr_config = VEGA10_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_VEGA12:
		adev->gfx.config.max_hw_contexts = 8;
		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x4C0;
		gb_addr_config = VEGA12_GB_ADDR_CONFIG_GOLDEN;
		DRM_INFO("fix gfx.config for vega12\n");
		break;
	case CHIP_VEGA20:
		adev->gfx.config.max_hw_contexts = 8;
		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x4C0;
		gb_addr_config = RREG32_SOC15(GC, 0, mmGB_ADDR_CONFIG);
		gb_addr_config &= ~0xf3e777ff;
		gb_addr_config |= 0x22014042;
		/* check vbios table if gpu info is not available */
		err = amdgpu_atomfirmware_get_gfx_info(adev);
		if (err)
			return err;
		break;
	case CHIP_RAVEN:
		adev->gfx.config.max_hw_contexts = 8;
		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x4C0;
		if (adev->rev_id >= 8)
			gb_addr_config = RAVEN2_GB_ADDR_CONFIG_GOLDEN;
		else
			gb_addr_config = RAVEN_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_ARCTURUS:
		adev->gfx.config.max_hw_contexts = 8;
		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x4C0;
		gb_addr_config = RREG32_SOC15(GC, 0, mmGB_ADDR_CONFIG);
		gb_addr_config &= ~0xf3e777ff;
		gb_addr_config |= 0x22014042;
		break;
	case CHIP_RENOIR:
		adev->gfx.config.max_hw_contexts = 8;
		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x80;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x4C0;
		gb_addr_config = RREG32_SOC15(GC, 0, mmGB_ADDR_CONFIG);
		gb_addr_config &= ~0xf3e777ff;
		gb_addr_config |= 0x22010042;
		break;
	default:
		BUG();
		break;
	}

	adev->gfx.config.gb_addr_config = gb_addr_config;

	adev->gfx.config.gb_addr_config_fields.num_pipes = 1 <<
			REG_GET_FIELD(
					adev->gfx.config.gb_addr_config,
					GB_ADDR_CONFIG,
					NUM_PIPES);

	adev->gfx.config.max_tile_pipes =
		adev->gfx.config.gb_addr_config_fields.num_pipes;

	adev->gfx.config.gb_addr_config_fields.num_banks = 1 <<
			REG_GET_FIELD(
					adev->gfx.config.gb_addr_config,
					GB_ADDR_CONFIG,
					NUM_BANKS);
	adev->gfx.config.gb_addr_config_fields.max_compress_frags = 1 <<
			REG_GET_FIELD(
					adev->gfx.config.gb_addr_config,
					GB_ADDR_CONFIG,
					MAX_COMPRESSED_FRAGS);
	adev->gfx.config.gb_addr_config_fields.num_rb_per_se = 1 <<
			REG_GET_FIELD(
					adev->gfx.config.gb_addr_config,
					GB_ADDR_CONFIG,
					NUM_RB_PER_SE);
	adev->gfx.config.gb_addr_config_fields.num_se = 1 <<
			REG_GET_FIELD(
					adev->gfx.config.gb_addr_config,
					GB_ADDR_CONFIG,
					NUM_SHADER_ENGINES);
	adev->gfx.config.gb_addr_config_fields.pipe_interleave_size = 1 << (8 +
			REG_GET_FIELD(
					adev->gfx.config.gb_addr_config,
					GB_ADDR_CONFIG,
					PIPE_INTERLEAVE_SIZE));

	return 0;
}