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
struct TYPE_9__ {int sc_prim_fifo_size_frontend; int sc_prim_fifo_size_backend; int sc_hiz_tile_fifo_size; int sc_earlyz_tile_fifo_size; int /*<<< orphan*/  db_debug2; } ;
struct TYPE_10__ {TYPE_4__ config; int /*<<< orphan*/  cu_info; } ;
struct TYPE_8__ {int private_aperture_start; int shared_aperture_start; } ;
struct TYPE_7__ {TYPE_1__* id_mgr; } ;
struct amdgpu_device {int /*<<< orphan*/  grbm_idx_mutex; TYPE_5__ gfx; int /*<<< orphan*/  srbm_mutex; TYPE_3__ gmc; TYPE_2__ vm_manager; } ;
struct TYPE_6__ {int num_ids; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGNMENT_MODE ; 
 size_t AMDGPU_GFXHUB ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  GRBM_CNTL ; 
 int PA_SC_FIFO_SIZE__SC_BACKEND_PRIM_FIFO_SIZE__SHIFT ; 
 int PA_SC_FIFO_SIZE__SC_EARLYZ_TILE_FIFO_SIZE__SHIFT ; 
 int PA_SC_FIFO_SIZE__SC_FRONTEND_PRIM_FIFO_SIZE__SHIFT ; 
 int PA_SC_FIFO_SIZE__SC_HIZ_TILE_FIFO_SIZE__SHIFT ; 
 int /*<<< orphan*/  PRIVATE_BASE ; 
 int /*<<< orphan*/  READ_TIMEOUT ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHARED_BASE ; 
 int SH_MEM_ALIGNMENT_MODE_UNALIGNED ; 
 int /*<<< orphan*/  SH_MEM_BASES ; 
 int /*<<< orphan*/  SH_MEM_CONFIG ; 
 int /*<<< orphan*/  WREG32_FIELD15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfx_v9_0_get_cu_info (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfx_v9_0_init_compute_vmid (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_select_se_sh (struct amdgpu_device*,int,int,int) ; 
 int /*<<< orphan*/  gfx_v9_0_setup_rb (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_tiling_mode_table_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmDB_DEBUG2 ; 
 int /*<<< orphan*/  mmPA_SC_FIFO_SIZE ; 
 int /*<<< orphan*/  mmSH_MEM_BASES ; 
 int /*<<< orphan*/  mmSH_MEM_CONFIG ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc15_grbm_select (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gfx_v9_0_gpu_init(struct amdgpu_device *adev)
{
	u32 tmp;
	int i;

	WREG32_FIELD15(GC, 0, GRBM_CNTL, READ_TIMEOUT, 0xff);

	gfx_v9_0_tiling_mode_table_init(adev);

	gfx_v9_0_setup_rb(adev);
	gfx_v9_0_get_cu_info(adev, &adev->gfx.cu_info);
	adev->gfx.config.db_debug2 = RREG32_SOC15(GC, 0, mmDB_DEBUG2);

	/* XXX SH_MEM regs */
	/* where to put LDS, scratch, GPUVM in FSA64 space */
	mutex_lock(&adev->srbm_mutex);
	for (i = 0; i < adev->vm_manager.id_mgr[AMDGPU_GFXHUB].num_ids; i++) {
		soc15_grbm_select(adev, 0, 0, 0, i);
		/* CP and shaders */
		if (i == 0) {
			tmp = REG_SET_FIELD(0, SH_MEM_CONFIG, ALIGNMENT_MODE,
					    SH_MEM_ALIGNMENT_MODE_UNALIGNED);
			WREG32_SOC15(GC, 0, mmSH_MEM_CONFIG, tmp);
			WREG32_SOC15(GC, 0, mmSH_MEM_BASES, 0);
		} else {
			tmp = REG_SET_FIELD(0, SH_MEM_CONFIG, ALIGNMENT_MODE,
					    SH_MEM_ALIGNMENT_MODE_UNALIGNED);
			WREG32_SOC15(GC, 0, mmSH_MEM_CONFIG, tmp);
			tmp = REG_SET_FIELD(0, SH_MEM_BASES, PRIVATE_BASE,
				(adev->gmc.private_aperture_start >> 48));
			tmp = REG_SET_FIELD(tmp, SH_MEM_BASES, SHARED_BASE,
				(adev->gmc.shared_aperture_start >> 48));
			WREG32_SOC15(GC, 0, mmSH_MEM_BASES, tmp);
		}
	}
	soc15_grbm_select(adev, 0, 0, 0, 0);

	mutex_unlock(&adev->srbm_mutex);

	gfx_v9_0_init_compute_vmid(adev);

	mutex_lock(&adev->grbm_idx_mutex);
	/*
	 * making sure that the following register writes will be broadcasted
	 * to all the shaders
	 */
	gfx_v9_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);

	WREG32_SOC15(GC, 0, mmPA_SC_FIFO_SIZE,
		   (adev->gfx.config.sc_prim_fifo_size_frontend <<
			PA_SC_FIFO_SIZE__SC_FRONTEND_PRIM_FIFO_SIZE__SHIFT) |
		   (adev->gfx.config.sc_prim_fifo_size_backend <<
			PA_SC_FIFO_SIZE__SC_BACKEND_PRIM_FIFO_SIZE__SHIFT) |
		   (adev->gfx.config.sc_hiz_tile_fifo_size <<
			PA_SC_FIFO_SIZE__SC_HIZ_TILE_FIFO_SIZE__SHIFT) |
		   (adev->gfx.config.sc_earlyz_tile_fifo_size <<
			PA_SC_FIFO_SIZE__SC_EARLYZ_TILE_FIFO_SIZE__SHIFT));
	mutex_unlock(&adev->grbm_idx_mutex);

}