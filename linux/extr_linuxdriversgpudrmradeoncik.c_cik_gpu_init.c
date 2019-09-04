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
struct TYPE_4__ {TYPE_1__ cik; } ;
struct radeon_device {int family; TYPE_2__ config; } ;

/* Variables and functions */
 int AUTO_INVLD_EN (int /*<<< orphan*/ ) ; 
 int BIF_FB_EN ; 
 int BONAIRE_GB_ADDR_CONFIG_GOLDEN ; 
 int CACHE_INVALIDATION (int /*<<< orphan*/ ) ; 
 int CB_HW_CONTROL ; 
#define  CHIP_BONAIRE 132 
#define  CHIP_HAWAII 131 
#define  CHIP_KABINI 130 
#define  CHIP_KAVERI 129 
#define  CHIP_MULLINS 128 
 int CLIP_VTX_REORDER_ENA ; 
 int CP_MEQ_THRESHOLDS ; 
 int CP_PERFMON_CNTL ; 
 int DB_DEBUG ; 
 int DB_DEBUG2 ; 
 int DB_DEBUG3 ; 
 int DMIF_ADDR_CALC ; 
 int ENABLE_PA_SC_OUT_OF_ORDER ; 
 int /*<<< orphan*/  ES_AND_GS_AUTO ; 
 int FB_READ_EN ; 
 int FB_WRITE_EN ; 
 int FORCE_EOV_MAX_CLK_CNT (int) ; 
 int FORCE_EOV_MAX_REZ_CNT (int) ; 
 int GB_ADDR_CONFIG ; 
 int GRBM_CNTL ; 
 int GRBM_READ_TIMEOUT (int) ; 
 int HAWAII_GB_ADDR_CONFIG_GOLDEN ; 
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
 int PA_SC_ENHANCE ; 
 int PA_SC_FIFO_SIZE ; 
 int PA_SC_FORCE_EOV_MAX_CNTS ; 
 int PA_SC_LINE_STIPPLE_STATE ; 
 int PIPE_INTERLEAVE_SIZE_MASK ; 
 int PIPE_INTERLEAVE_SIZE_SHIFT ; 
 int ROW_SIZE (int) ; 
 int ROW_SIZE_MASK ; 
 int ROW_SIZE_SHIFT ; 
 int RREG32 (int) ; 
 int SC_BACKEND_PRIM_FIFO_SIZE (int) ; 
 int SC_EARLYZ_TILE_FIFO_SIZE (int) ; 
 int SC_FRONTEND_PRIM_FIFO_SIZE (int) ; 
 int SC_HIZ_TILE_FIFO_SIZE (int) ; 
 int SDMA0_REGISTER_OFFSET ; 
 int SDMA0_TILING_CONFIG ; 
 int SDMA1_REGISTER_OFFSET ; 
 int SPI_CONFIG_CNTL ; 
 int SPI_CONFIG_CNTL_1 ; 
 int SQ_CONFIG ; 
 int SRBM_INT_ACK ; 
 int SRBM_INT_CNTL ; 
 int SX_DEBUG_1 ; 
 int TA_CNTL_AUX ; 
 int UVD_UDEC_ADDR_CONFIG ; 
 int UVD_UDEC_DBW_ADDR_CONFIG ; 
 int UVD_UDEC_DB_ADDR_CONFIG ; 
 int /*<<< orphan*/  VC_AND_TC ; 
 int VGT_CACHE_INVALIDATION ; 
 int VGT_GS_VERTEX_REUSE ; 
 int VGT_NUM_INSTANCES ; 
 int VTX_DONE_DELAY (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  cik_get_cu_active_bitmap (struct radeon_device*,int,int) ; 
 int /*<<< orphan*/  cik_setup_rb (struct radeon_device*,int,int,int) ; 
 int /*<<< orphan*/  cik_tiling_mode_table_init (struct radeon_device*) ; 
 scalar_t__ hweight32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cik_gpu_init(struct radeon_device *rdev)
{
	u32 gb_addr_config = RREG32(GB_ADDR_CONFIG);
	u32 mc_shared_chmap, mc_arb_ramcfg;
	u32 hdp_host_path_cntl;
	u32 tmp;
	int i, j;

	switch (rdev->family) {
	case CHIP_BONAIRE:
		rdev->config.cik.max_shader_engines = 2;
		rdev->config.cik.max_tile_pipes = 4;
		rdev->config.cik.max_cu_per_sh = 7;
		rdev->config.cik.max_sh_per_se = 1;
		rdev->config.cik.max_backends_per_se = 2;
		rdev->config.cik.max_texture_channel_caches = 4;
		rdev->config.cik.max_gprs = 256;
		rdev->config.cik.max_gs_threads = 32;
		rdev->config.cik.max_hw_contexts = 8;

		rdev->config.cik.sc_prim_fifo_size_frontend = 0x20;
		rdev->config.cik.sc_prim_fifo_size_backend = 0x100;
		rdev->config.cik.sc_hiz_tile_fifo_size = 0x30;
		rdev->config.cik.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = BONAIRE_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_HAWAII:
		rdev->config.cik.max_shader_engines = 4;
		rdev->config.cik.max_tile_pipes = 16;
		rdev->config.cik.max_cu_per_sh = 11;
		rdev->config.cik.max_sh_per_se = 1;
		rdev->config.cik.max_backends_per_se = 4;
		rdev->config.cik.max_texture_channel_caches = 16;
		rdev->config.cik.max_gprs = 256;
		rdev->config.cik.max_gs_threads = 32;
		rdev->config.cik.max_hw_contexts = 8;

		rdev->config.cik.sc_prim_fifo_size_frontend = 0x20;
		rdev->config.cik.sc_prim_fifo_size_backend = 0x100;
		rdev->config.cik.sc_hiz_tile_fifo_size = 0x30;
		rdev->config.cik.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = HAWAII_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_KAVERI:
		rdev->config.cik.max_shader_engines = 1;
		rdev->config.cik.max_tile_pipes = 4;
		rdev->config.cik.max_cu_per_sh = 8;
		rdev->config.cik.max_backends_per_se = 2;
		rdev->config.cik.max_sh_per_se = 1;
		rdev->config.cik.max_texture_channel_caches = 4;
		rdev->config.cik.max_gprs = 256;
		rdev->config.cik.max_gs_threads = 16;
		rdev->config.cik.max_hw_contexts = 8;

		rdev->config.cik.sc_prim_fifo_size_frontend = 0x20;
		rdev->config.cik.sc_prim_fifo_size_backend = 0x100;
		rdev->config.cik.sc_hiz_tile_fifo_size = 0x30;
		rdev->config.cik.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = BONAIRE_GB_ADDR_CONFIG_GOLDEN;
		break;
	case CHIP_KABINI:
	case CHIP_MULLINS:
	default:
		rdev->config.cik.max_shader_engines = 1;
		rdev->config.cik.max_tile_pipes = 2;
		rdev->config.cik.max_cu_per_sh = 2;
		rdev->config.cik.max_sh_per_se = 1;
		rdev->config.cik.max_backends_per_se = 1;
		rdev->config.cik.max_texture_channel_caches = 2;
		rdev->config.cik.max_gprs = 256;
		rdev->config.cik.max_gs_threads = 16;
		rdev->config.cik.max_hw_contexts = 8;

		rdev->config.cik.sc_prim_fifo_size_frontend = 0x20;
		rdev->config.cik.sc_prim_fifo_size_backend = 0x100;
		rdev->config.cik.sc_hiz_tile_fifo_size = 0x30;
		rdev->config.cik.sc_earlyz_tile_fifo_size = 0x130;
		gb_addr_config = BONAIRE_GB_ADDR_CONFIG_GOLDEN;
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
	WREG32(SRBM_INT_CNTL, 0x1);
	WREG32(SRBM_INT_ACK, 0x1);

	WREG32(BIF_FB_EN, FB_READ_EN | FB_WRITE_EN);

	mc_shared_chmap = RREG32(MC_SHARED_CHMAP);
	mc_arb_ramcfg = RREG32(MC_ARB_RAMCFG);

	rdev->config.cik.num_tile_pipes = rdev->config.cik.max_tile_pipes;
	rdev->config.cik.mem_max_burst_length_bytes = 256;
	tmp = (mc_arb_ramcfg & NOOFCOLS_MASK) >> NOOFCOLS_SHIFT;
	rdev->config.cik.mem_row_size_in_kb = (4 * (1 << (8 + tmp))) / 1024;
	if (rdev->config.cik.mem_row_size_in_kb > 4)
		rdev->config.cik.mem_row_size_in_kb = 4;
	/* XXX use MC settings? */
	rdev->config.cik.shader_engine_tile_size = 32;
	rdev->config.cik.num_gpus = 1;
	rdev->config.cik.multi_gpu_tile_size = 64;

	/* fix up row size */
	gb_addr_config &= ~ROW_SIZE_MASK;
	switch (rdev->config.cik.mem_row_size_in_kb) {
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
	rdev->config.cik.tile_config = 0;
	switch (rdev->config.cik.num_tile_pipes) {
	case 1:
		rdev->config.cik.tile_config |= (0 << 0);
		break;
	case 2:
		rdev->config.cik.tile_config |= (1 << 0);
		break;
	case 4:
		rdev->config.cik.tile_config |= (2 << 0);
		break;
	case 8:
	default:
		/* XXX what about 12? */
		rdev->config.cik.tile_config |= (3 << 0);
		break;
	}
	rdev->config.cik.tile_config |=
		((mc_arb_ramcfg & NOOFBANK_MASK) >> NOOFBANK_SHIFT) << 4;
	rdev->config.cik.tile_config |=
		((gb_addr_config & PIPE_INTERLEAVE_SIZE_MASK) >> PIPE_INTERLEAVE_SIZE_SHIFT) << 8;
	rdev->config.cik.tile_config |=
		((gb_addr_config & ROW_SIZE_MASK) >> ROW_SIZE_SHIFT) << 12;

	WREG32(GB_ADDR_CONFIG, gb_addr_config);
	WREG32(HDP_ADDR_CONFIG, gb_addr_config);
	WREG32(DMIF_ADDR_CALC, gb_addr_config);
	WREG32(SDMA0_TILING_CONFIG + SDMA0_REGISTER_OFFSET, gb_addr_config & 0x70);
	WREG32(SDMA0_TILING_CONFIG + SDMA1_REGISTER_OFFSET, gb_addr_config & 0x70);
	WREG32(UVD_UDEC_ADDR_CONFIG, gb_addr_config);
	WREG32(UVD_UDEC_DB_ADDR_CONFIG, gb_addr_config);
	WREG32(UVD_UDEC_DBW_ADDR_CONFIG, gb_addr_config);

	cik_tiling_mode_table_init(rdev);

	cik_setup_rb(rdev, rdev->config.cik.max_shader_engines,
		     rdev->config.cik.max_sh_per_se,
		     rdev->config.cik.max_backends_per_se);

	rdev->config.cik.active_cus = 0;
	for (i = 0; i < rdev->config.cik.max_shader_engines; i++) {
		for (j = 0; j < rdev->config.cik.max_sh_per_se; j++) {
			rdev->config.cik.active_cus +=
				hweight32(cik_get_cu_active_bitmap(rdev, i, j));
		}
	}

	/* set HW defaults for 3D engine */
	WREG32(CP_MEQ_THRESHOLDS, MEQ1_START(0x30) | MEQ2_START(0x60));

	WREG32(SX_DEBUG_1, 0x20);

	WREG32(TA_CNTL_AUX, 0x00010000);

	tmp = RREG32(SPI_CONFIG_CNTL);
	tmp |= 0x03000000;
	WREG32(SPI_CONFIG_CNTL, tmp);

	WREG32(SQ_CONFIG, 1);

	WREG32(DB_DEBUG, 0);

	tmp = RREG32(DB_DEBUG2) & ~0xf00fffff;
	tmp |= 0x00000400;
	WREG32(DB_DEBUG2, tmp);

	tmp = RREG32(DB_DEBUG3) & ~0x0002021c;
	tmp |= 0x00020200;
	WREG32(DB_DEBUG3, tmp);

	tmp = RREG32(CB_HW_CONTROL) & ~0x00010000;
	tmp |= 0x00018208;
	WREG32(CB_HW_CONTROL, tmp);

	WREG32(SPI_CONFIG_CNTL_1, VTX_DONE_DELAY(4));

	WREG32(PA_SC_FIFO_SIZE, (SC_FRONTEND_PRIM_FIFO_SIZE(rdev->config.cik.sc_prim_fifo_size_frontend) |
				 SC_BACKEND_PRIM_FIFO_SIZE(rdev->config.cik.sc_prim_fifo_size_backend) |
				 SC_HIZ_TILE_FIFO_SIZE(rdev->config.cik.sc_hiz_tile_fifo_size) |
				 SC_EARLYZ_TILE_FIFO_SIZE(rdev->config.cik.sc_earlyz_tile_fifo_size)));

	WREG32(VGT_NUM_INSTANCES, 1);

	WREG32(CP_PERFMON_CNTL, 0);

	WREG32(SQ_CONFIG, 0);

	WREG32(PA_SC_FORCE_EOV_MAX_CNTS, (FORCE_EOV_MAX_CLK_CNT(4095) |
					  FORCE_EOV_MAX_REZ_CNT(255)));

	WREG32(VGT_CACHE_INVALIDATION, CACHE_INVALIDATION(VC_AND_TC) |
	       AUTO_INVLD_EN(ES_AND_GS_AUTO));

	WREG32(VGT_GS_VERTEX_REUSE, 16);
	WREG32(PA_SC_LINE_STIPPLE_STATE, 0);

	tmp = RREG32(HDP_MISC_CNTL);
	tmp |= HDP_FLUSH_INVALIDATE_CACHE;
	WREG32(HDP_MISC_CNTL, tmp);

	hdp_host_path_cntl = RREG32(HDP_HOST_PATH_CNTL);
	WREG32(HDP_HOST_PATH_CNTL, hdp_host_path_cntl);

	WREG32(PA_CL_ENHANCE, CLIP_VTX_REORDER_ENA | NUM_CLIP_SEQ(3));
	WREG32(PA_SC_ENHANCE, ENABLE_PA_SC_OUT_OF_ORDER);

	udelay(50);
}