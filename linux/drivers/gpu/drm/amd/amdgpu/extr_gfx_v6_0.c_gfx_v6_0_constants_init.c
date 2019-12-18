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
struct amdgpu_device {int asic_type; TYPE_2__ gfx; scalar_t__ has_uvd; } ;

/* Variables and functions */
 int BIF_FB_EN__FB_READ_EN_MASK ; 
 int BIF_FB_EN__FB_WRITE_EN_MASK ; 
 int /*<<< orphan*/  BUG () ; 
#define  CHIP_HAINAN 132 
#define  CHIP_OLAND 131 
#define  CHIP_PITCAIRN 130 
#define  CHIP_TAHITI 129 
#define  CHIP_VERDE 128 
 int CP_MEQ_THRESHOLDS__MEQ1_START__SHIFT ; 
 int CP_MEQ_THRESHOLDS__MEQ2_START__SHIFT ; 
 int CP_QUEUE_THRESHOLDS__ROQ_IB1_START__SHIFT ; 
 int CP_QUEUE_THRESHOLDS__ROQ_IB2_START__SHIFT ; 
 scalar_t__ DMA0_REGISTER_OFFSET ; 
 scalar_t__ DMA1_REGISTER_OFFSET ; 
 int ES_AND_GS_AUTO ; 
 int GB_ADDR_CONFIG__NUM_SHADER_ENGINES_MASK ; 
 int GB_ADDR_CONFIG__NUM_SHADER_ENGINES__SHIFT ; 
 int GB_ADDR_CONFIG__ROW_SIZE_MASK ; 
 int GB_ADDR_CONFIG__ROW_SIZE__SHIFT ; 
 int GRBM_CNTL__READ_TIMEOUT__SHIFT ; 
 int HAINAN_GB_ADDR_CONFIG_GOLDEN ; 
 int MC_ARB_RAMCFG__NOOFCOLS_MASK ; 
 int MC_ARB_RAMCFG__NOOFCOLS__SHIFT ; 
 int PA_CL_ENHANCE__CLIP_VTX_REORDER_ENA_MASK ; 
 int PA_CL_ENHANCE__NUM_CLIP_SEQ__SHIFT ; 
 int PA_SC_FIFO_SIZE__SC_BACKEND_PRIM_FIFO_SIZE__SHIFT ; 
 int PA_SC_FIFO_SIZE__SC_EARLYZ_TILE_FIFO_SIZE__SHIFT ; 
 int PA_SC_FIFO_SIZE__SC_FRONTEND_PRIM_FIFO_SIZE__SHIFT ; 
 int PA_SC_FIFO_SIZE__SC_HIZ_TILE_FIFO_SIZE__SHIFT ; 
 int PA_SC_FORCE_EOV_MAX_CNTS__FORCE_EOV_MAX_CLK_CNT__SHIFT ; 
 int PA_SC_FORCE_EOV_MAX_CNTS__FORCE_EOV_MAX_REZ_CNT__SHIFT ; 
 void* RREG32 (scalar_t__) ; 
 int SPI_CONFIG_CNTL_1__VTX_DONE_DELAY__SHIFT ; 
 int TAHITI_GB_ADDR_CONFIG_GOLDEN ; 
 int VC_AND_TC ; 
 int VERDE_GB_ADDR_CONFIG_GOLDEN ; 
 int VGT_CACHE_INVALIDATION__AUTO_INVLD_EN__SHIFT ; 
 int VGT_CACHE_INVALIDATION__CACHE_INVALIDATION__SHIFT ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int /*<<< orphan*/  gfx_v6_0_config_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v6_0_get_cu_info (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v6_0_setup_rb (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v6_0_setup_spi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v6_0_tiling_mode_table_init (struct amdgpu_device*) ; 
 scalar_t__ mmBIF_FB_EN ; 
 scalar_t__ mmCB_PERFCOUNTER0_SELECT0 ; 
 scalar_t__ mmCB_PERFCOUNTER0_SELECT1 ; 
 scalar_t__ mmCB_PERFCOUNTER1_SELECT0 ; 
 scalar_t__ mmCB_PERFCOUNTER1_SELECT1 ; 
 scalar_t__ mmCB_PERFCOUNTER2_SELECT0 ; 
 scalar_t__ mmCB_PERFCOUNTER2_SELECT1 ; 
 scalar_t__ mmCB_PERFCOUNTER3_SELECT0 ; 
 scalar_t__ mmCB_PERFCOUNTER3_SELECT1 ; 
 scalar_t__ mmCP_MEQ_THRESHOLDS ; 
 scalar_t__ mmCP_PERFMON_CNTL ; 
 scalar_t__ mmCP_QUEUE_THRESHOLDS ; 
 scalar_t__ mmDMA_TILING_CONFIG ; 
 scalar_t__ mmDMIF_ADDR_CALC ; 
 scalar_t__ mmDMIF_ADDR_CONFIG ; 
 scalar_t__ mmGB_ADDR_CONFIG ; 
 scalar_t__ mmGRBM_CNTL ; 
 scalar_t__ mmHDP_ADDR_CONFIG ; 
 scalar_t__ mmHDP_HOST_PATH_CNTL ; 
 scalar_t__ mmMC_ARB_RAMCFG ; 
 scalar_t__ mmMC_SHARED_CHMAP ; 
 scalar_t__ mmPA_CL_ENHANCE ; 
 scalar_t__ mmPA_SC_FIFO_SIZE ; 
 scalar_t__ mmPA_SC_FORCE_EOV_MAX_CNTS ; 
 scalar_t__ mmPA_SC_LINE_STIPPLE_STATE ; 
 scalar_t__ mmSPI_CONFIG_CNTL_1 ; 
 scalar_t__ mmSQ_CONFIG ; 
 scalar_t__ mmSRBM_INT_ACK ; 
 scalar_t__ mmSRBM_INT_CNTL ; 
 scalar_t__ mmSX_DEBUG_1 ; 
 scalar_t__ mmUVD_UDEC_ADDR_CONFIG ; 
 scalar_t__ mmUVD_UDEC_DBW_ADDR_CONFIG ; 
 scalar_t__ mmUVD_UDEC_DB_ADDR_CONFIG ; 
 scalar_t__ mmVGT_CACHE_INVALIDATION ; 
 scalar_t__ mmVGT_GS_VERTEX_REUSE ; 
 scalar_t__ mmVGT_NUM_INSTANCES ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gfx_v6_0_constants_init(struct amdgpu_device *adev)
{
	u32 gb_addr_config = 0;
	u32 mc_shared_chmap, mc_arb_ramcfg;
	u32 sx_debug_1;
	u32 hdp_host_path_cntl;
	u32 tmp;

	switch (adev->asic_type) {
	case CHIP_TAHITI:
		adev->gfx.config.max_shader_engines = 2;
		adev->gfx.config.max_tile_pipes = 12;
		adev->gfx.config.max_cu_per_sh = 8;
		adev->gfx.config.max_sh_per_se = 2;
		adev->gfx.config.max_backends_per_se = 4;
		adev->gfx.config.max_texture_channel_caches = 12;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_threads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = TAHITI_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_PITCAIRN:
		adev->gfx.config.max_shader_engines = 2;
		adev->gfx.config.max_tile_pipes = 8;
		adev->gfx.config.max_cu_per_sh = 5;
		adev->gfx.config.max_sh_per_se = 2;
		adev->gfx.config.max_backends_per_se = 4;
		adev->gfx.config.max_texture_channel_caches = 8;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_threads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = TAHITI_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_VERDE:
		adev->gfx.config.max_shader_engines = 1;
		adev->gfx.config.max_tile_pipes = 4;
		adev->gfx.config.max_cu_per_sh = 5;
		adev->gfx.config.max_sh_per_se = 2;
		adev->gfx.config.max_backends_per_se = 4;
		adev->gfx.config.max_texture_channel_caches = 4;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_threads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x40;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = VERDE_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_OLAND:
		adev->gfx.config.max_shader_engines = 1;
		adev->gfx.config.max_tile_pipes = 4;
		adev->gfx.config.max_cu_per_sh = 6;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_backends_per_se = 2;
		adev->gfx.config.max_texture_channel_caches = 4;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_threads = 16;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x40;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = VERDE_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_HAINAN:
		adev->gfx.config.max_shader_engines = 1;
		adev->gfx.config.max_tile_pipes = 4;
		adev->gfx.config.max_cu_per_sh = 5;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_backends_per_se = 1;
		adev->gfx.config.max_texture_channel_caches = 2;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_threads = 16;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fifo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fifo_size_backend = 0x40;
		adev->gfx.config.sc_hiz_tile_fifo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = HAINAN_GB_ADDR_CONFIG_GOLDEN;
		break;
	default:
		BUG();
		break;
	}

	WREG32(mmGRBM_CNTL, (0xff << GRBM_CNTL__READ_TIMEOUT__SHIFT));
	WREG32(mmSRBM_INT_CNTL, 1);
	WREG32(mmSRBM_INT_ACK, 1);

	WREG32(mmBIF_FB_EN, BIF_FB_EN__FB_READ_EN_MASK | BIF_FB_EN__FB_WRITE_EN_MASK);

	mc_shared_chmap = RREG32(mmMC_SHARED_CHMAP);
	adev->gfx.config.mc_arb_ramcfg = RREG32(mmMC_ARB_RAMCFG);
	mc_arb_ramcfg = adev->gfx.config.mc_arb_ramcfg;

	adev->gfx.config.num_tile_pipes = adev->gfx.config.max_tile_pipes;
	adev->gfx.config.mem_max_burst_length_bytes = 256;
	tmp = (mc_arb_ramcfg & MC_ARB_RAMCFG__NOOFCOLS_MASK) >> MC_ARB_RAMCFG__NOOFCOLS__SHIFT;
	adev->gfx.config.mem_row_size_in_kb = (4 * (1 << (8 + tmp))) / 1024;
	if (adev->gfx.config.mem_row_size_in_kb > 4)
		adev->gfx.config.mem_row_size_in_kb = 4;
	adev->gfx.config.shader_engine_tile_size = 32;
	adev->gfx.config.num_gpus = 1;
	adev->gfx.config.multi_gpu_tile_size = 64;

	gb_addr_config &= ~GB_ADDR_CONFIG__ROW_SIZE_MASK;
	switch (adev->gfx.config.mem_row_size_in_kb) {
	case 1:
	default:
		gb_addr_config |= 0 << GB_ADDR_CONFIG__ROW_SIZE__SHIFT;
		break;
	case 2:
		gb_addr_config |= 1 << GB_ADDR_CONFIG__ROW_SIZE__SHIFT;
		break;
	case 4:
		gb_addr_config |= 2 << GB_ADDR_CONFIG__ROW_SIZE__SHIFT;
		break;
	}
	gb_addr_config &= ~GB_ADDR_CONFIG__NUM_SHADER_ENGINES_MASK;
	if (adev->gfx.config.max_shader_engines == 2)
		gb_addr_config |= 1 << GB_ADDR_CONFIG__NUM_SHADER_ENGINES__SHIFT;
	adev->gfx.config.gb_addr_config = gb_addr_config;

	WREG32(mmGB_ADDR_CONFIG, gb_addr_config);
	WREG32(mmDMIF_ADDR_CONFIG, gb_addr_config);
	WREG32(mmDMIF_ADDR_CALC, gb_addr_config);
	WREG32(mmHDP_ADDR_CONFIG, gb_addr_config);
	WREG32(mmDMA_TILING_CONFIG + DMA0_REGISTER_OFFSET, gb_addr_config);
	WREG32(mmDMA_TILING_CONFIG + DMA1_REGISTER_OFFSET, gb_addr_config);

#if 0
	if (adev->has_uvd) {
		WREG32(mmUVD_UDEC_ADDR_CONFIG, gb_addr_config);
		WREG32(mmUVD_UDEC_DB_ADDR_CONFIG, gb_addr_config);
		WREG32(mmUVD_UDEC_DBW_ADDR_CONFIG, gb_addr_config);
	}
#endif
	gfx_v6_0_tiling_mode_table_init(adev);

	gfx_v6_0_setup_rb(adev);

	gfx_v6_0_setup_spi(adev);

	gfx_v6_0_get_cu_info(adev);
	gfx_v6_0_config_init(adev);

	WREG32(mmCP_QUEUE_THRESHOLDS, ((0x16 << CP_QUEUE_THRESHOLDS__ROQ_IB1_START__SHIFT) |
				       (0x2b << CP_QUEUE_THRESHOLDS__ROQ_IB2_START__SHIFT)));
	WREG32(mmCP_MEQ_THRESHOLDS, (0x30 << CP_MEQ_THRESHOLDS__MEQ1_START__SHIFT) |
				    (0x60 << CP_MEQ_THRESHOLDS__MEQ2_START__SHIFT));

	sx_debug_1 = RREG32(mmSX_DEBUG_1);
	WREG32(mmSX_DEBUG_1, sx_debug_1);

	WREG32(mmSPI_CONFIG_CNTL_1, (4 << SPI_CONFIG_CNTL_1__VTX_DONE_DELAY__SHIFT));

	WREG32(mmPA_SC_FIFO_SIZE, ((adev->gfx.config.sc_prim_fifo_size_frontend << PA_SC_FIFO_SIZE__SC_FRONTEND_PRIM_FIFO_SIZE__SHIFT) |
				   (adev->gfx.config.sc_prim_fifo_size_backend << PA_SC_FIFO_SIZE__SC_BACKEND_PRIM_FIFO_SIZE__SHIFT) |
				   (adev->gfx.config.sc_hiz_tile_fifo_size << PA_SC_FIFO_SIZE__SC_HIZ_TILE_FIFO_SIZE__SHIFT) |
				   (adev->gfx.config.sc_earlyz_tile_fifo_size << PA_SC_FIFO_SIZE__SC_EARLYZ_TILE_FIFO_SIZE__SHIFT)));

	WREG32(mmVGT_NUM_INSTANCES, 1);
	WREG32(mmCP_PERFMON_CNTL, 0);
	WREG32(mmSQ_CONFIG, 0);
	WREG32(mmPA_SC_FORCE_EOV_MAX_CNTS, ((4095 << PA_SC_FORCE_EOV_MAX_CNTS__FORCE_EOV_MAX_CLK_CNT__SHIFT) |
					  (255 << PA_SC_FORCE_EOV_MAX_CNTS__FORCE_EOV_MAX_REZ_CNT__SHIFT)));

	WREG32(mmVGT_CACHE_INVALIDATION,
		(VC_AND_TC << VGT_CACHE_INVALIDATION__CACHE_INVALIDATION__SHIFT) |
		(ES_AND_GS_AUTO << VGT_CACHE_INVALIDATION__AUTO_INVLD_EN__SHIFT));

	WREG32(mmVGT_GS_VERTEX_REUSE, 16);
	WREG32(mmPA_SC_LINE_STIPPLE_STATE, 0);

	WREG32(mmCB_PERFCOUNTER0_SELECT0, 0);
	WREG32(mmCB_PERFCOUNTER0_SELECT1, 0);
	WREG32(mmCB_PERFCOUNTER1_SELECT0, 0);
	WREG32(mmCB_PERFCOUNTER1_SELECT1, 0);
	WREG32(mmCB_PERFCOUNTER2_SELECT0, 0);
	WREG32(mmCB_PERFCOUNTER2_SELECT1, 0);
	WREG32(mmCB_PERFCOUNTER3_SELECT0, 0);
	WREG32(mmCB_PERFCOUNTER3_SELECT1, 0);

	hdp_host_path_cntl = RREG32(mmHDP_HOST_PATH_CNTL);
	WREG32(mmHDP_HOST_PATH_CNTL, hdp_host_path_cntl);

	WREG32(mmPA_CL_ENHANCE, PA_CL_ENHANCE__CLIP_VTX_REORDER_ENA_MASK |
				(3 << PA_CL_ENHANCE__NUM_CLIP_SEQ__SHIFT));

	udelay(50);
}