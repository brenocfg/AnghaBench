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
struct TYPE_3__ {int max_shader_engines; int max_tile_pipes; int max_cu_per_sh; int max_sh_per_se; int max_backends_per_se; int max_texture_channel_caches; int max_gprs; int max_gs_threads; int max_hw_contexts; int sc_prim_fifo_size_frontend; int sc_prim_fifo_size_backend; int sc_hiz_tile_fifo_size; int sc_earlyz_tile_fifo_size; int num_tile_pipes; int mem_max_burst_length_bytes; int mem_row_size_in_kb; int shader_engine_tile_size; int num_gpus; int multi_gpu_tile_size; int tile_config; scalar_t__ active_cus; } ;
struct TYPE_4__ {TYPE_1__ si; } ;
struct radeon_device {int family; TYPE_2__ config; scalar_t__ has_uvd; } ;

/* Variables and functions */
 int AUTO_INVLD_EN (int /*<<< orphan*/ ) ; 
 int BIF_FB_EN ; 
 int CACHE_INVALIDATION (int /*<<< orphan*/ ) ; 
 int CB_PERFCOUNTER0_SELECT0 ; 
 int CB_PERFCOUNTER0_SELECT1 ; 
 int CB_PERFCOUNTER1_SELECT0 ; 
 int CB_PERFCOUNTER1_SELECT1 ; 
 int CB_PERFCOUNTER2_SELECT0 ; 
 int CB_PERFCOUNTER2_SELECT1 ; 
 int CB_PERFCOUNTER3_SELECT0 ; 
 int CB_PERFCOUNTER3_SELECT1 ; 
#define  CHIP_HAINAN 132 
#define  CHIP_OLAND 131 
#define  CHIP_PITCAIRN 130 
#define  CHIP_TAHITI 129 
#define  CHIP_VERDE 128 
 int CLIP_VTX_REORDER_ENA ; 
 int CP_MEQ_THRESHOLDS ; 
 int CP_PERFMON_CNTL ; 
 int CP_QUEUE_THRESHOLDS ; 
 int DMA0_REGISTER_OFFSET ; 
 int DMA1_REGISTER_OFFSET ; 
 int DMA_TILING_CONFIG ; 
 int DMIF_ADDR_CALC ; 
 int DMIF_ADDR_CONFIG ; 
 int /*<<< orphan*/  ES_AND_GS_AUTO ; 
 int FB_READ_EN ; 
 int FB_WRITE_EN ; 
 int FORCE_EOV_MAX_CLK_CNT (int) ; 
 int FORCE_EOV_MAX_REZ_CNT (int) ; 
 int GB_ADDR_CONFIG ; 
 int GRBM_CNTL ; 
 int GRBM_READ_TIMEOUT (int) ; 
 int HAINAN_GB_ADDR_CONFIG_GOLDEN ; 
 int HDP_ADDR_CONFIG ; 
 int HDP_FLUSH_INVALIDATE_CACHE ; 
 int HDP_HOST_PATH_CNTL ; 
 int HDP_MISC_CNTL ; 
 int MC_ARB_RAMCFG ; 
 int MC_SHARED_CHMAP ; 
 int MEQ1_START (int) ; 
 int MEQ2_START (int) ; 
 int NOOFBANK_MASK ; 
 int NOOFBANK_SHIFT ; 
 int NOOFCOLS_MASK ; 
 int NOOFCOLS_SHIFT ; 
 int NUM_CLIP_SEQ (int) ; 
 int PA_CL_ENHANCE ; 
 int PA_SC_FIFO_SIZE ; 
 int PA_SC_FORCE_EOV_MAX_CNTS ; 
 int PA_SC_LINE_STIPPLE_STATE ; 
 int PIPE_INTERLEAVE_SIZE_MASK ; 
 int PIPE_INTERLEAVE_SIZE_SHIFT ; 
 int ROQ_IB1_START (int) ; 
 int ROQ_IB2_START (int) ; 
 int ROW_SIZE (int) ; 
 int ROW_SIZE_MASK ; 
 int ROW_SIZE_SHIFT ; 
 int RREG32 (int) ; 
 int SC_BACKEND_PRIM_FIFO_SIZE (int) ; 
 int SC_EARLYZ_TILE_FIFO_SIZE (int) ; 
 int SC_FRONTEND_PRIM_FIFO_SIZE (int) ; 
 int SC_HIZ_TILE_FIFO_SIZE (int) ; 
 int SPI_CONFIG_CNTL_1 ; 
 int SQ_CONFIG ; 
 int SRBM_INT_ACK ; 
 int SRBM_INT_CNTL ; 
 int SX_DEBUG_1 ; 
 int TAHITI_GB_ADDR_CONFIG_GOLDEN ; 
 int UVD_UDEC_ADDR_CONFIG ; 
 int UVD_UDEC_DBW_ADDR_CONFIG ; 
 int UVD_UDEC_DB_ADDR_CONFIG ; 
 int /*<<< orphan*/  VC_AND_TC ; 
 int VERDE_GB_ADDR_CONFIG_GOLDEN ; 
 int VGT_CACHE_INVALIDATION ; 
 int VGT_GS_VERTEX_REUSE ; 
 int VGT_NUM_INSTANCES ; 
 int VTX_DONE_DELAY (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  evergreen_fix_pci_max_read_req_size (struct radeon_device*) ; 
 scalar_t__ hweight32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_get_cu_active_bitmap (struct radeon_device*,int,int) ; 
 int /*<<< orphan*/  si_setup_rb (struct radeon_device*,int,int,int) ; 
 int /*<<< orphan*/  si_setup_spi (struct radeon_device*,int,int,int) ; 
 int /*<<< orphan*/  si_tiling_mode_table_init (struct radeon_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void si_gpu_init(struct radeon_device *rdev)
{
	u32 gb_addr_config = 0;
	u32 mc_shared_chmap, mc_arb_ramcfg;
	u32 sx_debug_1;
	u32 hdp_host_path_cntl;
	u32 tmp;
	int i, j;

	switch (rdev->family) {
	case CHIP_TAHITI:
		rdev->config.si.max_shader_engines = 2;
		rdev->config.si.max_tile_pipes = 12;
		rdev->config.si.max_cu_per_sh = 8;
		rdev->config.si.max_sh_per_se = 2;
		rdev->config.si.max_backends_per_se = 4;
		rdev->config.si.max_texture_channel_caches = 12;
		rdev->config.si.max_gprs = 256;
		rdev->config.si.max_gs_threads = 32;
		rdev->config.si.max_hw_contexts = 8;

		rdev->config.si.sc_prim_fifo_size_frontend = 0x20;
		rdev->config.si.sc_prim_fifo_size_backend = 0x100;
		rdev->config.si.sc_hiz_tile_fifo_size = 0x30;
		rdev->config.si.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = TAHITI_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_PITCAIRN:
		rdev->config.si.max_shader_engines = 2;
		rdev->config.si.max_tile_pipes = 8;
		rdev->config.si.max_cu_per_sh = 5;
		rdev->config.si.max_sh_per_se = 2;
		rdev->config.si.max_backends_per_se = 4;
		rdev->config.si.max_texture_channel_caches = 8;
		rdev->config.si.max_gprs = 256;
		rdev->config.si.max_gs_threads = 32;
		rdev->config.si.max_hw_contexts = 8;

		rdev->config.si.sc_prim_fifo_size_frontend = 0x20;
		rdev->config.si.sc_prim_fifo_size_backend = 0x100;
		rdev->config.si.sc_hiz_tile_fifo_size = 0x30;
		rdev->config.si.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = TAHITI_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_VERDE:
	default:
		rdev->config.si.max_shader_engines = 1;
		rdev->config.si.max_tile_pipes = 4;
		rdev->config.si.max_cu_per_sh = 5;
		rdev->config.si.max_sh_per_se = 2;
		rdev->config.si.max_backends_per_se = 4;
		rdev->config.si.max_texture_channel_caches = 4;
		rdev->config.si.max_gprs = 256;
		rdev->config.si.max_gs_threads = 32;
		rdev->config.si.max_hw_contexts = 8;

		rdev->config.si.sc_prim_fifo_size_frontend = 0x20;
		rdev->config.si.sc_prim_fifo_size_backend = 0x40;
		rdev->config.si.sc_hiz_tile_fifo_size = 0x30;
		rdev->config.si.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = VERDE_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_OLAND:
		rdev->config.si.max_shader_engines = 1;
		rdev->config.si.max_tile_pipes = 4;
		rdev->config.si.max_cu_per_sh = 6;
		rdev->config.si.max_sh_per_se = 1;
		rdev->config.si.max_backends_per_se = 2;
		rdev->config.si.max_texture_channel_caches = 4;
		rdev->config.si.max_gprs = 256;
		rdev->config.si.max_gs_threads = 16;
		rdev->config.si.max_hw_contexts = 8;

		rdev->config.si.sc_prim_fifo_size_frontend = 0x20;
		rdev->config.si.sc_prim_fifo_size_backend = 0x40;
		rdev->config.si.sc_hiz_tile_fifo_size = 0x30;
		rdev->config.si.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = VERDE_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_HAINAN:
		rdev->config.si.max_shader_engines = 1;
		rdev->config.si.max_tile_pipes = 4;
		rdev->config.si.max_cu_per_sh = 5;
		rdev->config.si.max_sh_per_se = 1;
		rdev->config.si.max_backends_per_se = 1;
		rdev->config.si.max_texture_channel_caches = 2;
		rdev->config.si.max_gprs = 256;
		rdev->config.si.max_gs_threads = 16;
		rdev->config.si.max_hw_contexts = 8;

		rdev->config.si.sc_prim_fifo_size_frontend = 0x20;
		rdev->config.si.sc_prim_fifo_size_backend = 0x40;
		rdev->config.si.sc_hiz_tile_fifo_size = 0x30;
		rdev->config.si.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = HAINAN_GB_ADDR_CONFIG_GOLDEN;
		break;
	}

	/* Initialize HDP */
	for (i = 0, j = 0; i < 32; i++, j += 0x18) {
		WREG32((0x2c14 + j), 0x00000000);
		WREG32((0x2c18 + j), 0x00000000);
		WREG32((0x2c1c + j), 0x00000000);
		WREG32((0x2c20 + j), 0x00000000);
		WREG32((0x2c24 + j), 0x00000000);
	}

	WREG32(GRBM_CNTL, GRBM_READ_TIMEOUT(0xff));
	WREG32(SRBM_INT_CNTL, 1);
	WREG32(SRBM_INT_ACK, 1);

	evergreen_fix_pci_max_read_req_size(rdev);

	WREG32(BIF_FB_EN, FB_READ_EN | FB_WRITE_EN);

	mc_shared_chmap = RREG32(MC_SHARED_CHMAP);
	mc_arb_ramcfg = RREG32(MC_ARB_RAMCFG);

	rdev->config.si.num_tile_pipes = rdev->config.si.max_tile_pipes;
	rdev->config.si.mem_max_burst_length_bytes = 256;
	tmp = (mc_arb_ramcfg & NOOFCOLS_MASK) >> NOOFCOLS_SHIFT;
	rdev->config.si.mem_row_size_in_kb = (4 * (1 << (8 + tmp))) / 1024;
	if (rdev->config.si.mem_row_size_in_kb > 4)
		rdev->config.si.mem_row_size_in_kb = 4;
	/* XXX use MC settings? */
	rdev->config.si.shader_engine_tile_size = 32;
	rdev->config.si.num_gpus = 1;
	rdev->config.si.multi_gpu_tile_size = 64;

	/* fix up row size */
	gb_addr_config &= ~ROW_SIZE_MASK;
	switch (rdev->config.si.mem_row_size_in_kb) {
	case 1:
	default:
		gb_addr_config |= ROW_SIZE(0);
		break;
	case 2:
		gb_addr_config |= ROW_SIZE(1);
		break;
	case 4:
		gb_addr_config |= ROW_SIZE(2);
		break;
	}

	/* setup tiling info dword.  gb_addr_config is not adequate since it does
	 * not have bank info, so create a custom tiling dword.
	 * bits 3:0   num_pipes
	 * bits 7:4   num_banks
	 * bits 11:8  group_size
	 * bits 15:12 row_size
	 */
	rdev->config.si.tile_config = 0;
	switch (rdev->config.si.num_tile_pipes) {
	case 1:
		rdev->config.si.tile_config |= (0 << 0);
		break;
	case 2:
		rdev->config.si.tile_config |= (1 << 0);
		break;
	case 4:
		rdev->config.si.tile_config |= (2 << 0);
		break;
	case 8:
	default:
		/* XXX what about 12? */
		rdev->config.si.tile_config |= (3 << 0);
		break;
	}	
	switch ((mc_arb_ramcfg & NOOFBANK_MASK) >> NOOFBANK_SHIFT) {
	case 0: /* four banks */
		rdev->config.si.tile_config |= 0 << 4;
		break;
	case 1: /* eight banks */
		rdev->config.si.tile_config |= 1 << 4;
		break;
	case 2: /* sixteen banks */
	default:
		rdev->config.si.tile_config |= 2 << 4;
		break;
	}
	rdev->config.si.tile_config |=
		((gb_addr_config & PIPE_INTERLEAVE_SIZE_MASK) >> PIPE_INTERLEAVE_SIZE_SHIFT) << 8;
	rdev->config.si.tile_config |=
		((gb_addr_config & ROW_SIZE_MASK) >> ROW_SIZE_SHIFT) << 12;

	WREG32(GB_ADDR_CONFIG, gb_addr_config);
	WREG32(DMIF_ADDR_CONFIG, gb_addr_config);
	WREG32(DMIF_ADDR_CALC, gb_addr_config);
	WREG32(HDP_ADDR_CONFIG, gb_addr_config);
	WREG32(DMA_TILING_CONFIG + DMA0_REGISTER_OFFSET, gb_addr_config);
	WREG32(DMA_TILING_CONFIG + DMA1_REGISTER_OFFSET, gb_addr_config);
	if (rdev->has_uvd) {
		WREG32(UVD_UDEC_ADDR_CONFIG, gb_addr_config);
		WREG32(UVD_UDEC_DB_ADDR_CONFIG, gb_addr_config);
		WREG32(UVD_UDEC_DBW_ADDR_CONFIG, gb_addr_config);
	}

	si_tiling_mode_table_init(rdev);

	si_setup_rb(rdev, rdev->config.si.max_shader_engines,
		    rdev->config.si.max_sh_per_se,
		    rdev->config.si.max_backends_per_se);

	si_setup_spi(rdev, rdev->config.si.max_shader_engines,
		     rdev->config.si.max_sh_per_se,
		     rdev->config.si.max_cu_per_sh);

	rdev->config.si.active_cus = 0;
	for (i = 0; i < rdev->config.si.max_shader_engines; i++) {
		for (j = 0; j < rdev->config.si.max_sh_per_se; j++) {
			rdev->config.si.active_cus +=
				hweight32(si_get_cu_active_bitmap(rdev, i, j));
		}
	}

	/* set HW defaults for 3D engine */
	WREG32(CP_QUEUE_THRESHOLDS, (ROQ_IB1_START(0x16) |
				     ROQ_IB2_START(0x2b)));
	WREG32(CP_MEQ_THRESHOLDS, MEQ1_START(0x30) | MEQ2_START(0x60));

	sx_debug_1 = RREG32(SX_DEBUG_1);
	WREG32(SX_DEBUG_1, sx_debug_1);

	WREG32(SPI_CONFIG_CNTL_1, VTX_DONE_DELAY(4));

	WREG32(PA_SC_FIFO_SIZE, (SC_FRONTEND_PRIM_FIFO_SIZE(rdev->config.si.sc_prim_fifo_size_frontend) |
				 SC_BACKEND_PRIM_FIFO_SIZE(rdev->config.si.sc_prim_fifo_size_backend) |
				 SC_HIZ_TILE_FIFO_SIZE(rdev->config.si.sc_hiz_tile_fifo_size) |
				 SC_EARLYZ_TILE_FIFO_SIZE(rdev->config.si.sc_earlyz_tile_fifo_size)));

	WREG32(VGT_NUM_INSTANCES, 1);

	WREG32(CP_PERFMON_CNTL, 0);

	WREG32(SQ_CONFIG, 0);

	WREG32(PA_SC_FORCE_EOV_MAX_CNTS, (FORCE_EOV_MAX_CLK_CNT(4095) |
					  FORCE_EOV_MAX_REZ_CNT(255)));

	WREG32(VGT_CACHE_INVALIDATION, CACHE_INVALIDATION(VC_AND_TC) |
	       AUTO_INVLD_EN(ES_AND_GS_AUTO));

	WREG32(VGT_GS_VERTEX_REUSE, 16);
	WREG32(PA_SC_LINE_STIPPLE_STATE, 0);

	WREG32(CB_PERFCOUNTER0_SELECT0, 0);
	WREG32(CB_PERFCOUNTER0_SELECT1, 0);
	WREG32(CB_PERFCOUNTER1_SELECT0, 0);
	WREG32(CB_PERFCOUNTER1_SELECT1, 0);
	WREG32(CB_PERFCOUNTER2_SELECT0, 0);
	WREG32(CB_PERFCOUNTER2_SELECT1, 0);
	WREG32(CB_PERFCOUNTER3_SELECT0, 0);
	WREG32(CB_PERFCOUNTER3_SELECT1, 0);

	tmp = RREG32(HDP_MISC_CNTL);
	tmp |= HDP_FLUSH_INVALIDATE_CACHE;
	WREG32(HDP_MISC_CNTL, tmp);

	hdp_host_path_cntl = RREG32(HDP_HOST_PATH_CNTL);
	WREG32(HDP_HOST_PATH_CNTL, hdp_host_path_cntl);

	WREG32(PA_CL_ENHANCE, CLIP_VTX_REORDER_ENA | NUM_CLIP_SEQ(3));

	udelay(50);
}