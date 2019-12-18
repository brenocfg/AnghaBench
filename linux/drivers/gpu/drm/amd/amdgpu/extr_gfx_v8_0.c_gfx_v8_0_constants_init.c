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
 int /*<<< orphan*/  DEFAULT_MTYPE ; 
 int /*<<< orphan*/  ELEMENT_SIZE ; 
 int /*<<< orphan*/  GRBM_CNTL ; 
 int /*<<< orphan*/  INDEX_STRIDE ; 
 int MTYPE_NC ; 
 int MTYPE_UC ; 
 int PA_SC_FIFO_SIZE__SC_BACKEND_PRIM_FIFO_SIZE__SHIFT ; 
 int PA_SC_FIFO_SIZE__SC_EARLYZ_TILE_FIFO_SIZE__SHIFT ; 
 int PA_SC_FIFO_SIZE__SC_FRONTEND_PRIM_FIFO_SIZE__SHIFT ; 
 int PA_SC_FIFO_SIZE__SC_HIZ_TILE_FIFO_SIZE__SHIFT ; 
 int /*<<< orphan*/  PIPE_ORDER_TS0 ; 
 int /*<<< orphan*/  PIPE_ORDER_TS1 ; 
 int /*<<< orphan*/  PIPE_ORDER_TS2 ; 
 int /*<<< orphan*/  PIPE_ORDER_TS3 ; 
 int /*<<< orphan*/  READ_TIMEOUT ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int SH_MEM_ALIGNMENT_MODE_UNALIGNED ; 
 int /*<<< orphan*/  SH_MEM_CONFIG ; 
 int /*<<< orphan*/  SH_STATIC_MEM_CONFIG ; 
 int /*<<< orphan*/  SPI_ARB_PRIORITY ; 
 int /*<<< orphan*/  SWIZZLE_ENABLE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfx_v8_0_config_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_get_cu_info (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_init_compute_vmid (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_init_gds_vmid (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_select_se_sh (struct amdgpu_device*,int,int,int) ; 
 int /*<<< orphan*/  gfx_v8_0_setup_rb (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_tiling_mode_table_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmDMIF_ADDR_CALC ; 
 int /*<<< orphan*/  mmGB_ADDR_CONFIG ; 
 int /*<<< orphan*/  mmHDP_ADDR_CONFIG ; 
 int /*<<< orphan*/  mmPA_SC_FIFO_SIZE ; 
 int /*<<< orphan*/  mmSH_MEM_APE1_BASE ; 
 int /*<<< orphan*/  mmSH_MEM_APE1_LIMIT ; 
 int /*<<< orphan*/  mmSH_MEM_BASES ; 
 int /*<<< orphan*/  mmSH_MEM_CONFIG ; 
 int /*<<< orphan*/  mmSH_STATIC_MEM_CONFIG ; 
 int /*<<< orphan*/  mmSPI_ARB_PRIORITY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vi_srbm_select (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gfx_v8_0_constants_init(struct amdgpu_device *adev)
{
	u32 tmp, sh_static_mem_cfg;
	int i;

	WREG32_FIELD(GRBM_CNTL, READ_TIMEOUT, 0xFF);
	WREG32(mmGB_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
	WREG32(mmHDP_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
	WREG32(mmDMIF_ADDR_CALC, adev->gfx.config.gb_addr_config);

	gfx_v8_0_tiling_mode_table_init(adev);
	gfx_v8_0_setup_rb(adev);
	gfx_v8_0_get_cu_info(adev);
	gfx_v8_0_config_init(adev);

	/* XXX SH_MEM regs */
	/* where to put LDS, scratch, GPUVM in FSA64 space */
	sh_static_mem_cfg = REG_SET_FIELD(0, SH_STATIC_MEM_CONFIG,
				   SWIZZLE_ENABLE, 1);
	sh_static_mem_cfg = REG_SET_FIELD(sh_static_mem_cfg, SH_STATIC_MEM_CONFIG,
				   ELEMENT_SIZE, 1);
	sh_static_mem_cfg = REG_SET_FIELD(sh_static_mem_cfg, SH_STATIC_MEM_CONFIG,
				   INDEX_STRIDE, 3);
	WREG32(mmSH_STATIC_MEM_CONFIG, sh_static_mem_cfg);

	mutex_lock(&adev->srbm_mutex);
	for (i = 0; i < adev->vm_manager.id_mgr[0].num_ids; i++) {
		vi_srbm_select(adev, 0, 0, 0, i);
		/* CP and shaders */
		if (i == 0) {
			tmp = REG_SET_FIELD(0, SH_MEM_CONFIG, DEFAULT_MTYPE, MTYPE_UC);
			tmp = REG_SET_FIELD(tmp, SH_MEM_CONFIG, APE1_MTYPE, MTYPE_UC);
			tmp = REG_SET_FIELD(tmp, SH_MEM_CONFIG, ALIGNMENT_MODE,
					    SH_MEM_ALIGNMENT_MODE_UNALIGNED);
			WREG32(mmSH_MEM_CONFIG, tmp);
			WREG32(mmSH_MEM_BASES, 0);
		} else {
			tmp = REG_SET_FIELD(0, SH_MEM_CONFIG, DEFAULT_MTYPE, MTYPE_NC);
			tmp = REG_SET_FIELD(tmp, SH_MEM_CONFIG, APE1_MTYPE, MTYPE_UC);
			tmp = REG_SET_FIELD(tmp, SH_MEM_CONFIG, ALIGNMENT_MODE,
					    SH_MEM_ALIGNMENT_MODE_UNALIGNED);
			WREG32(mmSH_MEM_CONFIG, tmp);
			tmp = adev->gmc.shared_aperture_start >> 48;
			WREG32(mmSH_MEM_BASES, tmp);
		}

		WREG32(mmSH_MEM_APE1_BASE, 1);
		WREG32(mmSH_MEM_APE1_LIMIT, 0);
	}
	vi_srbm_select(adev, 0, 0, 0, 0);
	mutex_unlock(&adev->srbm_mutex);

	gfx_v8_0_init_compute_vmid(adev);
	gfx_v8_0_init_gds_vmid(adev);

	mutex_lock(&adev->grbm_idx_mutex);
	/*
	 * making sure that the following register writes will be broadcasted
	 * to all the shaders
	 */
	gfx_v8_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);

	WREG32(mmPA_SC_FIFO_SIZE,
		   (adev->gfx.config.sc_prim_fifo_size_frontend <<
			PA_SC_FIFO_SIZE__SC_FRONTEND_PRIM_FIFO_SIZE__SHIFT) |
		   (adev->gfx.config.sc_prim_fifo_size_backend <<
			PA_SC_FIFO_SIZE__SC_BACKEND_PRIM_FIFO_SIZE__SHIFT) |
		   (adev->gfx.config.sc_hiz_tile_fifo_size <<
			PA_SC_FIFO_SIZE__SC_HIZ_TILE_FIFO_SIZE__SHIFT) |
		   (adev->gfx.config.sc_earlyz_tile_fifo_size <<
			PA_SC_FIFO_SIZE__SC_EARLYZ_TILE_FIFO_SIZE__SHIFT));

	tmp = RREG32(mmSPI_ARB_PRIORITY);
	tmp = REG_SET_FIELD(tmp, SPI_ARB_PRIORITY, PIPE_ORDER_TS0, 2);
	tmp = REG_SET_FIELD(tmp, SPI_ARB_PRIORITY, PIPE_ORDER_TS1, 2);
	tmp = REG_SET_FIELD(tmp, SPI_ARB_PRIORITY, PIPE_ORDER_TS2, 2);
	tmp = REG_SET_FIELD(tmp, SPI_ARB_PRIORITY, PIPE_ORDER_TS3, 2);
	WREG32(mmSPI_ARB_PRIORITY, tmp);

	mutex_unlock(&adev->grbm_idx_mutex);

}