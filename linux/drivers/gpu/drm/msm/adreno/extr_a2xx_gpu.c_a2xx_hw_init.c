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
typedef  int uint32_t ;
struct msm_gpu {int name; TYPE_1__* aspace; } ;
struct adreno_gpu {int gmem; TYPE_2__** fw; } ;
typedef  int dma_addr_t ;
struct TYPE_4__ {int size; scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmu; } ;

/* Variables and functions */
 int A2XX_MH_ARBITER_CONFIG_CP_CLNT_ENABLE ; 
 int A2XX_MH_ARBITER_CONFIG_IN_FLIGHT_LIMIT (int) ; 
 int A2XX_MH_ARBITER_CONFIG_IN_FLIGHT_LIMIT_ENABLE ; 
 int A2XX_MH_ARBITER_CONFIG_L1_ARB_ENABLE ; 
 int A2XX_MH_ARBITER_CONFIG_L1_ARB_HOLD_ENABLE ; 
 int A2XX_MH_ARBITER_CONFIG_PAGE_SIZE (int) ; 
 int A2XX_MH_ARBITER_CONFIG_PA_CLNT_ENABLE ; 
 int A2XX_MH_ARBITER_CONFIG_RB_CLNT_ENABLE ; 
 int A2XX_MH_ARBITER_CONFIG_SAME_PAGE_LIMIT (int) ; 
 int A2XX_MH_ARBITER_CONFIG_TC_ARB_HOLD_ENABLE ; 
 int A2XX_MH_ARBITER_CONFIG_TC_CLNT_ENABLE ; 
 int A2XX_MH_ARBITER_CONFIG_TC_REORDER_ENABLE ; 
 int A2XX_MH_ARBITER_CONFIG_VGT_CLNT_ENABLE ; 
 int A2XX_MH_INTERRUPT_MASK_AXI_READ_ERROR ; 
 int A2XX_MH_INTERRUPT_MASK_AXI_WRITE_ERROR ; 
 int A2XX_MH_INTERRUPT_MASK_MMU_PAGE_FAULT ; 
 int A2XX_MH_MMU_CONFIG_CP_R0_CLNT_BEHAVIOR (int /*<<< orphan*/ ) ; 
 int A2XX_MH_MMU_CONFIG_CP_R1_CLNT_BEHAVIOR (int /*<<< orphan*/ ) ; 
 int A2XX_MH_MMU_CONFIG_CP_R2_CLNT_BEHAVIOR (int /*<<< orphan*/ ) ; 
 int A2XX_MH_MMU_CONFIG_CP_R3_CLNT_BEHAVIOR (int /*<<< orphan*/ ) ; 
 int A2XX_MH_MMU_CONFIG_CP_R4_CLNT_BEHAVIOR (int /*<<< orphan*/ ) ; 
 int A2XX_MH_MMU_CONFIG_CP_W_CLNT_BEHAVIOR (int /*<<< orphan*/ ) ; 
 int A2XX_MH_MMU_CONFIG_MMU_ENABLE ; 
 int A2XX_MH_MMU_CONFIG_PA_W_CLNT_BEHAVIOR (int /*<<< orphan*/ ) ; 
 int A2XX_MH_MMU_CONFIG_RB_W_CLNT_BEHAVIOR (int /*<<< orphan*/ ) ; 
 int A2XX_MH_MMU_CONFIG_TC_R_CLNT_BEHAVIOR (int /*<<< orphan*/ ) ; 
 int A2XX_MH_MMU_CONFIG_VGT_R0_CLNT_BEHAVIOR (int /*<<< orphan*/ ) ; 
 int A2XX_MH_MMU_CONFIG_VGT_R1_CLNT_BEHAVIOR (int /*<<< orphan*/ ) ; 
 int A2XX_MH_MMU_INVALIDATE_INVALIDATE_ALL ; 
 int A2XX_MH_MMU_INVALIDATE_INVALIDATE_TC ; 
 int A2XX_MH_MMU_VA_RANGE_NUM_64KB_REGIONS (int) ; 
 int A2XX_RBBM_INT_CNTL_RDERR_INT_MASK ; 
 size_t ADRENO_FW_PFP ; 
 size_t ADRENO_FW_PM4 ; 
 int AXXX_CP_DEBUG_MIU_128BIT_WRITE_ENABLE ; 
 int AXXX_CP_INT_CNTL_IB1_INT_MASK ; 
 int AXXX_CP_INT_CNTL_IB_ERROR_MASK ; 
 int AXXX_CP_INT_CNTL_OPCODE_ERROR_MASK ; 
 int AXXX_CP_INT_CNTL_PROTECTED_MODE_ERROR_MASK ; 
 int AXXX_CP_INT_CNTL_RB_INT_MASK ; 
 int AXXX_CP_INT_CNTL_RESERVED_BIT_ERROR_MASK ; 
 int AXXX_CP_INT_CNTL_T0_PACKET_IN_IB_MASK ; 
 int AXXX_CP_ME_CNTL_HALT ; 
 int /*<<< orphan*/  BEH_TRAN_RNG ; 
 int /*<<< orphan*/  DBG (char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  REG_A2XX_CP_PFP_UCODE_ADDR ; 
 int /*<<< orphan*/  REG_A2XX_CP_PFP_UCODE_DATA ; 
 int /*<<< orphan*/  REG_A2XX_MH_ARBITER_CONFIG ; 
 int /*<<< orphan*/  REG_A2XX_MH_CLNT_INTF_CTRL_CONFIG1 ; 
 int /*<<< orphan*/  REG_A2XX_MH_INTERRUPT_MASK ; 
 int /*<<< orphan*/  REG_A2XX_MH_MMU_CONFIG ; 
 int /*<<< orphan*/  REG_A2XX_MH_MMU_INVALIDATE ; 
 int /*<<< orphan*/  REG_A2XX_MH_MMU_MPU_BASE ; 
 int /*<<< orphan*/  REG_A2XX_MH_MMU_MPU_END ; 
 int /*<<< orphan*/  REG_A2XX_MH_MMU_PT_BASE ; 
 int /*<<< orphan*/  REG_A2XX_MH_MMU_TRAN_ERROR ; 
 int /*<<< orphan*/  REG_A2XX_MH_MMU_VA_RANGE ; 
 int /*<<< orphan*/  REG_A2XX_RBBM_CNTL ; 
 int /*<<< orphan*/  REG_A2XX_RBBM_DEBUG ; 
 int /*<<< orphan*/  REG_A2XX_RBBM_INT_CNTL ; 
 int /*<<< orphan*/  REG_A2XX_RBBM_PM_OVERRIDE1 ; 
 int /*<<< orphan*/  REG_A2XX_RBBM_PM_OVERRIDE2 ; 
 int /*<<< orphan*/  REG_A2XX_RBBM_SOFT_RESET ; 
 int /*<<< orphan*/  REG_A2XX_RB_EDRAM_INFO ; 
 int /*<<< orphan*/  REG_A2XX_SQ_FLOW_CONTROL ; 
 int /*<<< orphan*/  REG_A2XX_SQ_INT_CNTL ; 
 int /*<<< orphan*/  REG_A2XX_SQ_PS_PROGRAM ; 
 int /*<<< orphan*/  REG_A2XX_SQ_VS_PROGRAM ; 
 int /*<<< orphan*/  REG_AXXX_CP_DEBUG ; 
 int /*<<< orphan*/  REG_AXXX_CP_INT_CNTL ; 
 int /*<<< orphan*/  REG_AXXX_CP_ME_CNTL ; 
 int /*<<< orphan*/  REG_AXXX_CP_ME_RAM_DATA ; 
 int /*<<< orphan*/  REG_AXXX_CP_ME_RAM_WADDR ; 
 int /*<<< orphan*/  REG_AXXX_CP_QUEUE_THRESHOLDS ; 
 int SZ_16K ; 
 int SZ_16M ; 
 scalar_t__ a2xx_me_init (struct msm_gpu*) ; 
 int adreno_hw_init (struct msm_gpu*) ; 
 int /*<<< orphan*/  adreno_is_a20x (struct adreno_gpu*) ; 
 scalar_t__ adreno_is_a225 (struct adreno_gpu*) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  msm_gpummu_params (int /*<<< orphan*/ ,int*,int*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static int a2xx_hw_init(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	dma_addr_t pt_base, tran_error;
	uint32_t *ptr, len;
	int i, ret;

	msm_gpummu_params(gpu->aspace->mmu, &pt_base, &tran_error);

	DBG("%s", gpu->name);

	/* halt ME to avoid ucode upload issues on a20x */
	gpu_write(gpu, REG_AXXX_CP_ME_CNTL, AXXX_CP_ME_CNTL_HALT);

	gpu_write(gpu, REG_A2XX_RBBM_PM_OVERRIDE1, 0xfffffffe);
	gpu_write(gpu, REG_A2XX_RBBM_PM_OVERRIDE2, 0xffffffff);

	/* note: kgsl uses 0x00000001 after first reset on a22x */
	gpu_write(gpu, REG_A2XX_RBBM_SOFT_RESET, 0xffffffff);
	msleep(30);
	gpu_write(gpu, REG_A2XX_RBBM_SOFT_RESET, 0x00000000);

	if (adreno_is_a225(adreno_gpu))
		gpu_write(gpu, REG_A2XX_SQ_FLOW_CONTROL, 0x18000000);

	/* note: kgsl uses 0x0000ffff for a20x */
	gpu_write(gpu, REG_A2XX_RBBM_CNTL, 0x00004442);

	/* MPU: physical range */
	gpu_write(gpu, REG_A2XX_MH_MMU_MPU_BASE, 0x00000000);
	gpu_write(gpu, REG_A2XX_MH_MMU_MPU_END, 0xfffff000);

	gpu_write(gpu, REG_A2XX_MH_MMU_CONFIG, A2XX_MH_MMU_CONFIG_MMU_ENABLE |
		A2XX_MH_MMU_CONFIG_RB_W_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_CP_W_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_CP_R0_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_CP_R1_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_CP_R2_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_CP_R3_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_CP_R4_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_VGT_R0_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_VGT_R1_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_TC_R_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_PA_W_CLNT_BEHAVIOR(BEH_TRAN_RNG));

	/* same as parameters in adreno_gpu */
	gpu_write(gpu, REG_A2XX_MH_MMU_VA_RANGE, SZ_16M |
		A2XX_MH_MMU_VA_RANGE_NUM_64KB_REGIONS(0xfff));

	gpu_write(gpu, REG_A2XX_MH_MMU_PT_BASE, pt_base);
	gpu_write(gpu, REG_A2XX_MH_MMU_TRAN_ERROR, tran_error);

	gpu_write(gpu, REG_A2XX_MH_MMU_INVALIDATE,
		A2XX_MH_MMU_INVALIDATE_INVALIDATE_ALL |
		A2XX_MH_MMU_INVALIDATE_INVALIDATE_TC);

	gpu_write(gpu, REG_A2XX_MH_ARBITER_CONFIG,
		A2XX_MH_ARBITER_CONFIG_SAME_PAGE_LIMIT(16) |
		A2XX_MH_ARBITER_CONFIG_L1_ARB_ENABLE |
		A2XX_MH_ARBITER_CONFIG_L1_ARB_HOLD_ENABLE |
		A2XX_MH_ARBITER_CONFIG_PAGE_SIZE(1) |
		A2XX_MH_ARBITER_CONFIG_TC_REORDER_ENABLE |
		A2XX_MH_ARBITER_CONFIG_TC_ARB_HOLD_ENABLE |
		A2XX_MH_ARBITER_CONFIG_IN_FLIGHT_LIMIT_ENABLE |
		A2XX_MH_ARBITER_CONFIG_IN_FLIGHT_LIMIT(8) |
		A2XX_MH_ARBITER_CONFIG_CP_CLNT_ENABLE |
		A2XX_MH_ARBITER_CONFIG_VGT_CLNT_ENABLE |
		A2XX_MH_ARBITER_CONFIG_TC_CLNT_ENABLE |
		A2XX_MH_ARBITER_CONFIG_RB_CLNT_ENABLE |
		A2XX_MH_ARBITER_CONFIG_PA_CLNT_ENABLE);
	if (!adreno_is_a20x(adreno_gpu))
		gpu_write(gpu, REG_A2XX_MH_CLNT_INTF_CTRL_CONFIG1, 0x00032f07);

	gpu_write(gpu, REG_A2XX_SQ_VS_PROGRAM, 0x00000000);
	gpu_write(gpu, REG_A2XX_SQ_PS_PROGRAM, 0x00000000);

	gpu_write(gpu, REG_A2XX_RBBM_PM_OVERRIDE1, 0); /* 0x200 for msm8960? */
	gpu_write(gpu, REG_A2XX_RBBM_PM_OVERRIDE2, 0); /* 0x80/0x1a0 for a22x? */

	/* note: gsl doesn't set this */
	gpu_write(gpu, REG_A2XX_RBBM_DEBUG, 0x00080000);

	gpu_write(gpu, REG_A2XX_RBBM_INT_CNTL,
		A2XX_RBBM_INT_CNTL_RDERR_INT_MASK);
	gpu_write(gpu, REG_AXXX_CP_INT_CNTL,
		AXXX_CP_INT_CNTL_T0_PACKET_IN_IB_MASK |
		AXXX_CP_INT_CNTL_OPCODE_ERROR_MASK |
		AXXX_CP_INT_CNTL_PROTECTED_MODE_ERROR_MASK |
		AXXX_CP_INT_CNTL_RESERVED_BIT_ERROR_MASK |
		AXXX_CP_INT_CNTL_IB_ERROR_MASK |
		AXXX_CP_INT_CNTL_IB1_INT_MASK |
		AXXX_CP_INT_CNTL_RB_INT_MASK);
	gpu_write(gpu, REG_A2XX_SQ_INT_CNTL, 0);
	gpu_write(gpu, REG_A2XX_MH_INTERRUPT_MASK,
		A2XX_MH_INTERRUPT_MASK_AXI_READ_ERROR |
		A2XX_MH_INTERRUPT_MASK_AXI_WRITE_ERROR |
		A2XX_MH_INTERRUPT_MASK_MMU_PAGE_FAULT);

	for (i = 3; i <= 5; i++)
		if ((SZ_16K << i) == adreno_gpu->gmem)
			break;
	gpu_write(gpu, REG_A2XX_RB_EDRAM_INFO, i);

	ret = adreno_hw_init(gpu);
	if (ret)
		return ret;

	/* NOTE: PM4/micro-engine firmware registers look to be the same
	 * for a2xx and a3xx.. we could possibly push that part down to
	 * adreno_gpu base class.  Or push both PM4 and PFP but
	 * parameterize the pfp ucode addr/data registers..
	 */

	/* Load PM4: */
	ptr = (uint32_t *)(adreno_gpu->fw[ADRENO_FW_PM4]->data);
	len = adreno_gpu->fw[ADRENO_FW_PM4]->size / 4;
	DBG("loading PM4 ucode version: %x", ptr[1]);

	gpu_write(gpu, REG_AXXX_CP_DEBUG,
			AXXX_CP_DEBUG_MIU_128BIT_WRITE_ENABLE);
	gpu_write(gpu, REG_AXXX_CP_ME_RAM_WADDR, 0);
	for (i = 1; i < len; i++)
		gpu_write(gpu, REG_AXXX_CP_ME_RAM_DATA, ptr[i]);

	/* Load PFP: */
	ptr = (uint32_t *)(adreno_gpu->fw[ADRENO_FW_PFP]->data);
	len = adreno_gpu->fw[ADRENO_FW_PFP]->size / 4;
	DBG("loading PFP ucode version: %x", ptr[5]);

	gpu_write(gpu, REG_A2XX_CP_PFP_UCODE_ADDR, 0);
	for (i = 1; i < len; i++)
		gpu_write(gpu, REG_A2XX_CP_PFP_UCODE_DATA, ptr[i]);

	gpu_write(gpu, REG_AXXX_CP_QUEUE_THRESHOLDS, 0x000C0804);

	/* clear ME_HALT to start micro engine */
	gpu_write(gpu, REG_AXXX_CP_ME_CNTL, 0);

	return a2xx_me_init(gpu) ? 0 : -EINVAL;
}