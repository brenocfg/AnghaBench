#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {int gb_addr_config; int sc_prim_fifo_size_frontend; int sc_prim_fifo_size_backend; int sc_hiz_tile_fifo_size; int sc_earlyz_tile_fifo_size; } ;
struct TYPE_10__ {TYPE_4__ config; } ;
struct TYPE_8__ {int shared_aperture_start; } ;
struct TYPE_7__ {TYPE_1__* id_mgr; } ;
struct amdgpu_device {int /*<<< orphan*/  grbm_idx_mutex; TYPE_5__ gfx; int /*<<< orphan*/  srbm_mutex; TYPE_3__ gmc; TYPE_2__ vm_manager; } ;
struct TYPE_6__ {int num_ids; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGNMENT_MODE ; 
 int /*<<< orphan*/  APE1_MTYPE ; 
 int CP_MEQ_THRESHOLDS__MEQ1_START__SHIFT ; 
 int CP_MEQ_THRESHOLDS__MEQ2_START__SHIFT ; 
 int /*<<< orphan*/  DEFAULT_MTYPE ; 
 int /*<<< orphan*/  ELEMENT_SIZE ; 
 int ES_AND_GS_AUTO ; 
 int GRBM_CNTL__READ_TIMEOUT__SHIFT ; 
 int /*<<< orphan*/  INDEX_STRIDE ; 
 int MTYPE_NC ; 
 int MTYPE_UC ; 
 int PA_CL_ENHANCE__CLIP_VTX_REORDER_ENA_MASK ; 
 int PA_CL_ENHANCE__NUM_CLIP_SEQ__SHIFT ; 
 int PA_SC_ENHANCE__ENABLE_PA_SC_OUT_OF_ORDER_MASK ; 
 int PA_SC_FIFO_SIZE__SC_BACKEND_PRIM_FIFO_SIZE__SHIFT ; 
 int PA_SC_FIFO_SIZE__SC_EARLYZ_TILE_FIFO_SIZE__SHIFT ; 
 int PA_SC_FIFO_SIZE__SC_FRONTEND_PRIM_FIFO_SIZE__SHIFT ; 
 int PA_SC_FIFO_SIZE__SC_HIZ_TILE_FIFO_SIZE__SHIFT ; 
 int PA_SC_FORCE_EOV_MAX_CNTS__FORCE_EOV_MAX_CLK_CNT__SHIFT ; 
 int PA_SC_FORCE_EOV_MAX_CNTS__FORCE_EOV_MAX_REZ_CNT__SHIFT ; 
 int /*<<< orphan*/  PIPE_ORDER_TS0 ; 
 int /*<<< orphan*/  PIPE_ORDER_TS1 ; 
 int /*<<< orphan*/  PIPE_ORDER_TS2 ; 
 int /*<<< orphan*/  PIPE_ORDER_TS3 ; 
 int /*<<< orphan*/  PRIVATE_ATC ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int SH_MEM_ALIGNMENT_MODE_UNALIGNED ; 
 int /*<<< orphan*/  SH_MEM_CONFIG ; 
 int /*<<< orphan*/  SH_STATIC_MEM_CONFIG ; 
 int /*<<< orphan*/  SPI_ARB_PRIORITY ; 
 int SPI_CONFIG_CNTL_1__VTX_DONE_DELAY__SHIFT ; 
 int /*<<< orphan*/  SWIZZLE_ENABLE ; 
 int VC_AND_TC ; 
 int VGT_CACHE_INVALIDATION__AUTO_INVLD_EN__SHIFT ; 
 int VGT_CACHE_INVALIDATION__CACHE_INVALIDATION__SHIFT ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cik_srbm_select (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfx_v7_0_config_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_get_cu_info (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_init_compute_vmid (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_init_gds_vmid (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_select_se_sh (struct amdgpu_device*,int,int,int) ; 
 int /*<<< orphan*/  gfx_v7_0_setup_rb (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_tiling_mode_table_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmCB_HW_CONTROL ; 
 int /*<<< orphan*/  mmCP_MEQ_THRESHOLDS ; 
 int /*<<< orphan*/  mmCP_PERFMON_CNTL ; 
 int /*<<< orphan*/  mmDB_DEBUG ; 
 int /*<<< orphan*/  mmDB_DEBUG2 ; 
 int /*<<< orphan*/  mmDB_DEBUG3 ; 
 int /*<<< orphan*/  mmDMIF_ADDR_CALC ; 
 int /*<<< orphan*/  mmGB_ADDR_CONFIG ; 
 int /*<<< orphan*/  mmGRBM_CNTL ; 
 int /*<<< orphan*/  mmHDP_ADDR_CONFIG ; 
 int /*<<< orphan*/  mmPA_CL_ENHANCE ; 
 int /*<<< orphan*/  mmPA_SC_ENHANCE ; 
 int /*<<< orphan*/  mmPA_SC_FIFO_SIZE ; 
 int /*<<< orphan*/  mmPA_SC_FORCE_EOV_MAX_CNTS ; 
 int /*<<< orphan*/  mmPA_SC_LINE_STIPPLE_STATE ; 
 int /*<<< orphan*/  mmSH_MEM_APE1_BASE ; 
 int /*<<< orphan*/  mmSH_MEM_APE1_LIMIT ; 
 int /*<<< orphan*/  mmSH_MEM_BASES ; 
 int /*<<< orphan*/  mmSH_MEM_CONFIG ; 
 int /*<<< orphan*/  mmSH_STATIC_MEM_CONFIG ; 
 int /*<<< orphan*/  mmSPI_ARB_PRIORITY ; 
 int /*<<< orphan*/  mmSPI_CONFIG_CNTL ; 
 int /*<<< orphan*/  mmSPI_CONFIG_CNTL_1 ; 
 int /*<<< orphan*/  mmSQ_CONFIG ; 
 int /*<<< orphan*/  mmSX_DEBUG_1 ; 
 int /*<<< orphan*/  mmTA_CNTL_AUX ; 
 int /*<<< orphan*/  mmVGT_CACHE_INVALIDATION ; 
 int /*<<< orphan*/  mmVGT_GS_VERTEX_REUSE ; 
 int /*<<< orphan*/  mmVGT_NUM_INSTANCES ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gfx_v7_0_constants_init(struct amdgpu_device *adev)
{
	u32 sh_mem_cfg, sh_static_mem_cfg, sh_mem_base;
	u32 tmp;
	int i;

	WREG32(mmGRBM_CNTL, (0xff << GRBM_CNTL__READ_TIMEOUT__SHIFT));

	WREG32(mmGB_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
	WREG32(mmHDP_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
	WREG32(mmDMIF_ADDR_CALC, adev->gfx.config.gb_addr_config);

	gfx_v7_0_tiling_mode_table_init(adev);

	gfx_v7_0_setup_rb(adev);
	gfx_v7_0_get_cu_info(adev);
	gfx_v7_0_config_init(adev);

	/* set HW defaults for 3D engine */
	WREG32(mmCP_MEQ_THRESHOLDS,
	       (0x30 << CP_MEQ_THRESHOLDS__MEQ1_START__SHIFT) |
	       (0x60 << CP_MEQ_THRESHOLDS__MEQ2_START__SHIFT));

	mutex_lock(&adev->grbm_idx_mutex);
	/*
	 * making sure that the following register writes will be broadcasted
	 * to all the shaders
	 */
	gfx_v7_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);

	/* XXX SH_MEM regs */
	/* where to put LDS, scratch, GPUVM in FSA64 space */
	sh_mem_cfg = REG_SET_FIELD(0, SH_MEM_CONFIG, ALIGNMENT_MODE,
				   SH_MEM_ALIGNMENT_MODE_UNALIGNED);
	sh_mem_cfg = REG_SET_FIELD(sh_mem_cfg, SH_MEM_CONFIG, DEFAULT_MTYPE,
				   MTYPE_NC);
	sh_mem_cfg = REG_SET_FIELD(sh_mem_cfg, SH_MEM_CONFIG, APE1_MTYPE,
				   MTYPE_UC);
	sh_mem_cfg = REG_SET_FIELD(sh_mem_cfg, SH_MEM_CONFIG, PRIVATE_ATC, 0);

	sh_static_mem_cfg = REG_SET_FIELD(0, SH_STATIC_MEM_CONFIG,
				   SWIZZLE_ENABLE, 1);
	sh_static_mem_cfg = REG_SET_FIELD(sh_static_mem_cfg, SH_STATIC_MEM_CONFIG,
				   ELEMENT_SIZE, 1);
	sh_static_mem_cfg = REG_SET_FIELD(sh_static_mem_cfg, SH_STATIC_MEM_CONFIG,
				   INDEX_STRIDE, 3);
	WREG32(mmSH_STATIC_MEM_CONFIG, sh_static_mem_cfg);

	mutex_lock(&adev->srbm_mutex);
	for (i = 0; i < adev->vm_manager.id_mgr[0].num_ids; i++) {
		if (i == 0)
			sh_mem_base = 0;
		else
			sh_mem_base = adev->gmc.shared_aperture_start >> 48;
		cik_srbm_select(adev, 0, 0, 0, i);
		/* CP and shaders */
		WREG32(mmSH_MEM_CONFIG, sh_mem_cfg);
		WREG32(mmSH_MEM_APE1_BASE, 1);
		WREG32(mmSH_MEM_APE1_LIMIT, 0);
		WREG32(mmSH_MEM_BASES, sh_mem_base);
	}
	cik_srbm_select(adev, 0, 0, 0, 0);
	mutex_unlock(&adev->srbm_mutex);

	gfx_v7_0_init_compute_vmid(adev);
	gfx_v7_0_init_gds_vmid(adev);

	WREG32(mmSX_DEBUG_1, 0x20);

	WREG32(mmTA_CNTL_AUX, 0x00010000);

	tmp = RREG32(mmSPI_CONFIG_CNTL);
	tmp |= 0x03000000;
	WREG32(mmSPI_CONFIG_CNTL, tmp);

	WREG32(mmSQ_CONFIG, 1);

	WREG32(mmDB_DEBUG, 0);

	tmp = RREG32(mmDB_DEBUG2) & ~0xf00fffff;
	tmp |= 0x00000400;
	WREG32(mmDB_DEBUG2, tmp);

	tmp = RREG32(mmDB_DEBUG3) & ~0x0002021c;
	tmp |= 0x00020200;
	WREG32(mmDB_DEBUG3, tmp);

	tmp = RREG32(mmCB_HW_CONTROL) & ~0x00010000;
	tmp |= 0x00018208;
	WREG32(mmCB_HW_CONTROL, tmp);

	WREG32(mmSPI_CONFIG_CNTL_1, (4 << SPI_CONFIG_CNTL_1__VTX_DONE_DELAY__SHIFT));

	WREG32(mmPA_SC_FIFO_SIZE,
		((adev->gfx.config.sc_prim_fifo_size_frontend << PA_SC_FIFO_SIZE__SC_FRONTEND_PRIM_FIFO_SIZE__SHIFT) |
		(adev->gfx.config.sc_prim_fifo_size_backend << PA_SC_FIFO_SIZE__SC_BACKEND_PRIM_FIFO_SIZE__SHIFT) |
		(adev->gfx.config.sc_hiz_tile_fifo_size << PA_SC_FIFO_SIZE__SC_HIZ_TILE_FIFO_SIZE__SHIFT) |
		(adev->gfx.config.sc_earlyz_tile_fifo_size << PA_SC_FIFO_SIZE__SC_EARLYZ_TILE_FIFO_SIZE__SHIFT)));

	WREG32(mmVGT_NUM_INSTANCES, 1);

	WREG32(mmCP_PERFMON_CNTL, 0);

	WREG32(mmSQ_CONFIG, 0);

	WREG32(mmPA_SC_FORCE_EOV_MAX_CNTS,
		((4095 << PA_SC_FORCE_EOV_MAX_CNTS__FORCE_EOV_MAX_CLK_CNT__SHIFT) |
		(255 << PA_SC_FORCE_EOV_MAX_CNTS__FORCE_EOV_MAX_REZ_CNT__SHIFT)));

	WREG32(mmVGT_CACHE_INVALIDATION,
		(VC_AND_TC << VGT_CACHE_INVALIDATION__CACHE_INVALIDATION__SHIFT) |
		(ES_AND_GS_AUTO << VGT_CACHE_INVALIDATION__AUTO_INVLD_EN__SHIFT));

	WREG32(mmVGT_GS_VERTEX_REUSE, 16);
	WREG32(mmPA_SC_LINE_STIPPLE_STATE, 0);

	WREG32(mmPA_CL_ENHANCE, PA_CL_ENHANCE__CLIP_VTX_REORDER_ENA_MASK |
			(3 << PA_CL_ENHANCE__NUM_CLIP_SEQ__SHIFT));
	WREG32(mmPA_SC_ENHANCE, PA_SC_ENHANCE__ENABLE_PA_SC_OUT_OF_ORDER_MASK);

	tmp = RREG32(mmSPI_ARB_PRIORITY);
	tmp = REG_SET_FIELD(tmp, SPI_ARB_PRIORITY, PIPE_ORDER_TS0, 2);
	tmp = REG_SET_FIELD(tmp, SPI_ARB_PRIORITY, PIPE_ORDER_TS1, 2);
	tmp = REG_SET_FIELD(tmp, SPI_ARB_PRIORITY, PIPE_ORDER_TS2, 2);
	tmp = REG_SET_FIELD(tmp, SPI_ARB_PRIORITY, PIPE_ORDER_TS3, 2);
	WREG32(mmSPI_ARB_PRIORITY, tmp);

	mutex_unlock(&adev->grbm_idx_mutex);

	udelay(50);
}