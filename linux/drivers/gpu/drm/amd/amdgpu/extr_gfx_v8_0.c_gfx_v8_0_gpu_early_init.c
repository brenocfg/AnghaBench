#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int max_shader_engines; int max_tile_pipes; int max_cu_per_sh; int max_sh_per_se; int max_backends_per_se; int max_texture_channel_caches; int max_gprs; int max_gs_threads; int max_hw_contexts; int sc_prim_fifo_size_frontend; int sc_prim_fifo_size_backend; int sc_hiz_tile_fifo_size; int sc_earlyz_tile_fifo_size; int mc_arb_ramcfg; int num_tile_pipes; int mem_max_burst_length_bytes; int mem_row_size_in_kb; int shader_engine_tile_size; int num_gpus; int multi_gpu_tile_size; int gb_addr_config; } ;
struct TYPE_4__ {TYPE_1__ config; } ;
struct amdgpu_device {int asic_type; int flags; TYPE_2__ gfx; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int CARRIZO_GB_ADDR_CONFIG_GOLDEN ; 
#define  CHIP_CARRIZO 136 
#define  CHIP_FIJI 135 
#define  CHIP_POLARIS10 134 
#define  CHIP_POLARIS11 133 
#define  CHIP_POLARIS12 132 
#define  CHIP_STONEY 131 
#define  CHIP_TONGA 130 
#define  CHIP_TOPAZ 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  DIMM0ADDRMAP ; 
 int /*<<< orphan*/  DIMM1ADDRMAP ; 
 int /*<<< orphan*/  GB_ADDR_CONFIG ; 
 int /*<<< orphan*/  MC_ARB_RAMCFG ; 
 int /*<<< orphan*/  MC_FUS_DRAM0_BANK_ADDR_MAPPING ; 
 int /*<<< orphan*/  MC_FUS_DRAM1_BANK_ADDR_MAPPING ; 
 int /*<<< orphan*/  NOOFCOLS ; 
 int POLARIS11_GB_ADDR_CONFIG_GOLDEN ; 
 int REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ROW_SIZE ; 
 void* RREG32 (int /*<<< orphan*/ ) ; 
 int TONGA_GB_ADDR_CONFIG_GOLDEN ; 
 int TOPAZ_GB_ADDR_CONFIG_GOLDEN ; 
 int amdgpu_atombios_get_gfx_info (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmMC_ARB_RAMCFG ; 
 int /*<<< orphan*/  mmMC_FUS_DRAM0_BANK_ADDR_MAPPING ; 
 int /*<<< orphan*/  mmMC_FUS_DRAM1_BANK_ADDR_MAPPING ; 
 int /*<<< orphan*/  mmMC_SHARED_CHMAP ; 

__attribute__((used)) static int gfx_v8_0_gpu_early_init(struct amdgpu_device *adev)
{
	u32 gb_addr_config;
	u32 mc_shared_chmap, mc_arb_ramcfg;
	u32 dimm00_addr_map, dimm01_addr_map, dimm10_addr_map, dimm11_addr_map;
	u32 tmp;
	int ret;

	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		adev->gfx.config.max_shader_engines = 1;
		adev->gfx.config.max_tile_pipes = 2;
		adev->gfx.config.max_cu_per_sh = 6;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_backends_per_se = 2;
		adev->gfx.config.max_texture_channel_caches = 2;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_threads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = TOPAZ_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_FIJI:
		adev->gfx.config.max_shader_engines = 4;
		adev->gfx.config.max_tile_pipes = 16;
		adev->gfx.config.max_cu_per_sh = 16;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_backends_per_se = 4;
		adev->gfx.config.max_texture_channel_caches = 16;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_threads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = TONGA_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_POLARIS11:
	case CHIP_POLARIS12:
		ret = amdgpu_atombios_get_gfx_info(adev);
		if (ret)
			return ret;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_threads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = POLARIS11_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_POLARIS10:
	case CHIP_VEGAM:
		ret = amdgpu_atombios_get_gfx_info(adev);
		if (ret)
			return ret;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_threads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = TONGA_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_TONGA:
		adev->gfx.config.max_shader_engines = 4;
		adev->gfx.config.max_tile_pipes = 8;
		adev->gfx.config.max_cu_per_sh = 8;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_backends_per_se = 2;
		adev->gfx.config.max_texture_channel_caches = 8;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_threads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = TONGA_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_CARRIZO:
		adev->gfx.config.max_shader_engines = 1;
		adev->gfx.config.max_tile_pipes = 2;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_backends_per_se = 2;
		adev->gfx.config.max_cu_per_sh = 8;
		adev->gfx.config.max_texture_channel_caches = 2;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_threads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = CARRIZO_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_STONEY:
		adev->gfx.config.max_shader_engines = 1;
		adev->gfx.config.max_tile_pipes = 2;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_backends_per_se = 1;
		adev->gfx.config.max_cu_per_sh = 3;
		adev->gfx.config.max_texture_channel_caches = 2;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_threads = 16;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = CARRIZO_GB_ADDR_CONFIG_GOLDEN;
		break;
	default:
		adev->gfx.config.max_shader_engines = 2;
		adev->gfx.config.max_tile_pipes = 4;
		adev->gfx.config.max_cu_per_sh = 2;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_backends_per_se = 2;
		adev->gfx.config.max_texture_channel_caches = 4;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_threads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = TONGA_GB_ADDR_CONFIG_GOLDEN;
		break;
	}

	mc_shared_chmap = RREG32(mmMC_SHARED_CHMAP);
	adev->gfx.config.mc_arb_ramcfg = RREG32(mmMC_ARB_RAMCFG);
	mc_arb_ramcfg = adev->gfx.config.mc_arb_ramcfg;

	adev->gfx.config.num_tile_pipes = adev->gfx.config.max_tile_pipes;
	adev->gfx.config.mem_max_burst_length_bytes = 256;
	if (adev->flags & AMD_IS_APU) {
		/* Get memory bank mapping mode. */
		tmp = RREG32(mmMC_FUS_DRAM0_BANK_ADDR_MAPPING);
		dimm00_addr_map = REG_GET_FIELD(tmp, MC_FUS_DRAM0_BANK_ADDR_MAPPING, DIMM0ADDRMAP);
		dimm01_addr_map = REG_GET_FIELD(tmp, MC_FUS_DRAM0_BANK_ADDR_MAPPING, DIMM1ADDRMAP);

		tmp = RREG32(mmMC_FUS_DRAM1_BANK_ADDR_MAPPING);
		dimm10_addr_map = REG_GET_FIELD(tmp, MC_FUS_DRAM1_BANK_ADDR_MAPPING, DIMM0ADDRMAP);
		dimm11_addr_map = REG_GET_FIELD(tmp, MC_FUS_DRAM1_BANK_ADDR_MAPPING, DIMM1ADDRMAP);

		/* Validate settings in case only one DIMM installed. */
		if ((dimm00_addr_map == 0) || (dimm00_addr_map == 3) || (dimm00_addr_map == 4) || (dimm00_addr_map > 12))
			dimm00_addr_map = 0;
		if ((dimm01_addr_map == 0) || (dimm01_addr_map == 3) || (dimm01_addr_map == 4) || (dimm01_addr_map > 12))
			dimm01_addr_map = 0;
		if ((dimm10_addr_map == 0) || (dimm10_addr_map == 3) || (dimm10_addr_map == 4) || (dimm10_addr_map > 12))
			dimm10_addr_map = 0;
		if ((dimm11_addr_map == 0) || (dimm11_addr_map == 3) || (dimm11_addr_map == 4) || (dimm11_addr_map > 12))
			dimm11_addr_map = 0;

		/* If DIMM Addr map is 8GB, ROW size should be 2KB. Otherwise 1KB. */
		/* If ROW size(DIMM1) != ROW size(DMIMM0), ROW size should be larger one. */
		if ((dimm00_addr_map == 11) || (dimm01_addr_map == 11) || (dimm10_addr_map == 11) || (dimm11_addr_map == 11))
			adev->gfx.config.mem_row_size_in_kb = 2;
		else
			adev->gfx.config.mem_row_size_in_kb = 1;
	} else {
		tmp = REG_GET_FIELD(mc_arb_ramcfg, MC_ARB_RAMCFG, NOOFCOLS);
		adev->gfx.config.mem_row_size_in_kb = (4 * (1 << (8 + tmp))) / 1024;
		if (adev->gfx.config.mem_row_size_in_kb > 4)
			adev->gfx.config.mem_row_size_in_kb = 4;
	}

	adev->gfx.config.shader_engine_tile_size = 32;
	adev->gfx.config.num_gpus = 1;
	adev->gfx.config.multi_gpu_tile_size = 64;

	/* fix up row size */
	switch (adev->gfx.config.mem_row_size_in_kb) {
	case 1:
	default:
		gb_addr_config = REG_SET_FIELD(gb_addr_config, GB_ADDR_CONFIG, ROW_SIZE, 0);
		break;
	case 2:
		gb_addr_config = REG_SET_FIELD(gb_addr_config, GB_ADDR_CONFIG, ROW_SIZE, 1);
		break;
	case 4:
		gb_addr_config = REG_SET_FIELD(gb_addr_config, GB_ADDR_CONFIG, ROW_SIZE, 2);
		break;
	}
	adev->gfx.config.gb_addr_config = gb_addr_config;

	return 0;
}