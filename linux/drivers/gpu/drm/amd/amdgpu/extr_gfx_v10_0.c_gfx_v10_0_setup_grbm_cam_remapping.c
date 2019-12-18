#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int GRBM_CAM_DATA__CAM_ADDR__SHIFT ; 
 int GRBM_CAM_DATA__CAM_REMAPADDR__SHIFT ; 
 int SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmGRBM_CAM_DATA ; 
 int /*<<< orphan*/  mmGRBM_CAM_DATA_UPPER ; 
 int /*<<< orphan*/  mmGRBM_CAM_INDEX ; 
 int /*<<< orphan*/  mmSPI_CONFIG_CNTL ; 
 int /*<<< orphan*/  mmSPI_CONFIG_CNTL_REMAP ; 
 int /*<<< orphan*/  mmVGT_ESGS_RING_SIZE ; 
 int /*<<< orphan*/  mmVGT_ESGS_RING_SIZE_UMD ; 
 int /*<<< orphan*/  mmVGT_GSVS_RING_SIZE ; 
 int /*<<< orphan*/  mmVGT_GSVS_RING_SIZE_UMD ; 
 int /*<<< orphan*/  mmVGT_HS_OFFCHIP_PARAM ; 
 int /*<<< orphan*/  mmVGT_HS_OFFCHIP_PARAM_UMD ; 
 int /*<<< orphan*/  mmVGT_TF_MEMORY_BASE ; 
 int /*<<< orphan*/  mmVGT_TF_MEMORY_BASE_HI ; 
 int /*<<< orphan*/  mmVGT_TF_MEMORY_BASE_HI_UMD ; 
 int /*<<< orphan*/  mmVGT_TF_MEMORY_BASE_UMD ; 
 int /*<<< orphan*/  mmVGT_TF_RING_SIZE ; 
 int /*<<< orphan*/  mmVGT_TF_RING_SIZE_UMD ; 

__attribute__((used)) static void gfx_v10_0_setup_grbm_cam_remapping(struct amdgpu_device *adev)
{
	uint32_t data;

	/* initialize cam_index to 0
	 * index will auto-inc after each data writting */
	WREG32_SOC15(GC, 0, mmGRBM_CAM_INDEX, 0);

	/* mmVGT_TF_RING_SIZE_UMD -> mmVGT_TF_RING_SIZE */
	data = (SOC15_REG_OFFSET(GC, 0, mmVGT_TF_RING_SIZE_UMD) <<
		GRBM_CAM_DATA__CAM_ADDR__SHIFT) |
	       (SOC15_REG_OFFSET(GC, 0, mmVGT_TF_RING_SIZE) <<
		GRBM_CAM_DATA__CAM_REMAPADDR__SHIFT);
	WREG32_SOC15(GC, 0, mmGRBM_CAM_DATA_UPPER, 0);
	WREG32_SOC15(GC, 0, mmGRBM_CAM_DATA, data);

	/* mmVGT_TF_MEMORY_BASE_UMD -> mmVGT_TF_MEMORY_BASE */
	data = (SOC15_REG_OFFSET(GC, 0, mmVGT_TF_MEMORY_BASE_UMD) <<
		GRBM_CAM_DATA__CAM_ADDR__SHIFT) |
	       (SOC15_REG_OFFSET(GC, 0, mmVGT_TF_MEMORY_BASE) <<
		GRBM_CAM_DATA__CAM_REMAPADDR__SHIFT);
	WREG32_SOC15(GC, 0, mmGRBM_CAM_DATA_UPPER, 0);
	WREG32_SOC15(GC, 0, mmGRBM_CAM_DATA, data);

	/* mmVGT_TF_MEMORY_BASE_HI_UMD -> mmVGT_TF_MEMORY_BASE_HI */
	data = (SOC15_REG_OFFSET(GC, 0, mmVGT_TF_MEMORY_BASE_HI_UMD) <<
		GRBM_CAM_DATA__CAM_ADDR__SHIFT) |
	       (SOC15_REG_OFFSET(GC, 0, mmVGT_TF_MEMORY_BASE_HI) <<
		GRBM_CAM_DATA__CAM_REMAPADDR__SHIFT);
	WREG32_SOC15(GC, 0, mmGRBM_CAM_DATA_UPPER, 0);
	WREG32_SOC15(GC, 0, mmGRBM_CAM_DATA, data);

	/* mmVGT_HS_OFFCHIP_PARAM_UMD -> mmVGT_HS_OFFCHIP_PARAM */
	data = (SOC15_REG_OFFSET(GC, 0, mmVGT_HS_OFFCHIP_PARAM_UMD) <<
		GRBM_CAM_DATA__CAM_ADDR__SHIFT) |
	       (SOC15_REG_OFFSET(GC, 0, mmVGT_HS_OFFCHIP_PARAM) <<
		GRBM_CAM_DATA__CAM_REMAPADDR__SHIFT);
	WREG32_SOC15(GC, 0, mmGRBM_CAM_DATA_UPPER, 0);
	WREG32_SOC15(GC, 0, mmGRBM_CAM_DATA, data);

	/* mmVGT_ESGS_RING_SIZE_UMD -> mmVGT_ESGS_RING_SIZE */
	data = (SOC15_REG_OFFSET(GC, 0, mmVGT_ESGS_RING_SIZE_UMD) <<
		GRBM_CAM_DATA__CAM_ADDR__SHIFT) |
	       (SOC15_REG_OFFSET(GC, 0, mmVGT_ESGS_RING_SIZE) <<
		GRBM_CAM_DATA__CAM_REMAPADDR__SHIFT);
	WREG32_SOC15(GC, 0, mmGRBM_CAM_DATA_UPPER, 0);
	WREG32_SOC15(GC, 0, mmGRBM_CAM_DATA, data);

	/* mmVGT_GSVS_RING_SIZE_UMD -> mmVGT_GSVS_RING_SIZE */
	data = (SOC15_REG_OFFSET(GC, 0, mmVGT_GSVS_RING_SIZE_UMD) <<
		GRBM_CAM_DATA__CAM_ADDR__SHIFT) |
	       (SOC15_REG_OFFSET(GC, 0, mmVGT_GSVS_RING_SIZE) <<
		GRBM_CAM_DATA__CAM_REMAPADDR__SHIFT);
	WREG32_SOC15(GC, 0, mmGRBM_CAM_DATA_UPPER, 0);
	WREG32_SOC15(GC, 0, mmGRBM_CAM_DATA, data);

	/* mmSPI_CONFIG_CNTL_REMAP -> mmSPI_CONFIG_CNTL */
	data = (SOC15_REG_OFFSET(GC, 0, mmSPI_CONFIG_CNTL_REMAP) <<
		GRBM_CAM_DATA__CAM_ADDR__SHIFT) |
	       (SOC15_REG_OFFSET(GC, 0, mmSPI_CONFIG_CNTL) <<
		GRBM_CAM_DATA__CAM_REMAPADDR__SHIFT);
	WREG32_SOC15(GC, 0, mmGRBM_CAM_DATA_UPPER, 0);
	WREG32_SOC15(GC, 0, mmGRBM_CAM_DATA, data);
}