#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msm_gpu {TYPE_1__* dev; int /*<<< orphan*/ * rb; } ;
struct adreno_gpu {int gmem; } ;
struct a6xx_gpu {int /*<<< orphan*/  gmu; int /*<<< orphan*/  cur_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int A6XX_INT_MASK ; 
 int A6XX_PROTECT_RDONLY (int,int) ; 
 int A6XX_PROTECT_RW (int,int) ; 
 int /*<<< orphan*/  CP_SET_SECURE_MODE ; 
 int EINVAL ; 
 int /*<<< orphan*/  GMU_OOB_BOOT_SLUMBER ; 
 int /*<<< orphan*/  GMU_OOB_GPU_SET ; 
 int /*<<< orphan*/  OUT_PKT7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING (int /*<<< orphan*/ ,int) ; 
 int PERF_CP_ALWAYS_COUNT ; 
 int /*<<< orphan*/  REG_A6XX_CP_ADDR_MODE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_CP_AHB_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_CP_MEM_POOL_SIZE ; 
 int /*<<< orphan*/  REG_A6XX_CP_PERFCTR_CP_SEL_0 ; 
 int /*<<< orphan*/  REG_A6XX_CP_PROTECT (int) ; 
 int /*<<< orphan*/  REG_A6XX_CP_PROTECT_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_CP_ROQ_THRESHOLDS_1 ; 
 int /*<<< orphan*/  REG_A6XX_CP_ROQ_THRESHOLDS_2 ; 
 int /*<<< orphan*/  REG_A6XX_CP_SQE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_GRAS_ADDR_MODE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_HLSQ_ADDR_MODE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_PC_ADDR_MODE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_PC_DBG_ECO_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_INTERFACE_HANG_INT_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_INT_0_MASK ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_PERFCTR_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_PERFCTR_GPU_BUSY_MASKED ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_SECVID_TRUST_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_SECVID_TSB_ADDR_MODE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_SECVID_TSB_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_SECVID_TSB_TRUSTED_BASE_HI ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_SECVID_TSB_TRUSTED_BASE_LO ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_SECVID_TSB_TRUSTED_SIZE ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_VBIF_CLIENT_QOS_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_RB_ADDR_MODE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_RB_NC_MODE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_SP_ADDR_MODE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_SP_NC_MODE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_TPL1_ADDR_MODE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_TPL1_NC_MODE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_UCHE_ADDR_MODE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_UCHE_CACHE_WAYS ; 
 int /*<<< orphan*/  REG_A6XX_UCHE_CLIENT_PF ; 
 int /*<<< orphan*/  REG_A6XX_UCHE_FILTER_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_UCHE_GMEM_RANGE_MAX_HI ; 
 int /*<<< orphan*/  REG_A6XX_UCHE_GMEM_RANGE_MAX_LO ; 
 int /*<<< orphan*/  REG_A6XX_UCHE_GMEM_RANGE_MIN_HI ; 
 int /*<<< orphan*/  REG_A6XX_UCHE_GMEM_RANGE_MIN_LO ; 
 int /*<<< orphan*/  REG_A6XX_UCHE_MODE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_UCHE_TRAP_BASE_HI ; 
 int /*<<< orphan*/  REG_A6XX_UCHE_TRAP_BASE_LO ; 
 int /*<<< orphan*/  REG_A6XX_UCHE_WRITE_RANGE_MAX_HI ; 
 int /*<<< orphan*/  REG_A6XX_UCHE_WRITE_RANGE_MAX_LO ; 
 int /*<<< orphan*/  REG_A6XX_UCHE_WRITE_THRU_BASE_HI ; 
 int /*<<< orphan*/  REG_A6XX_UCHE_WRITE_THRU_BASE_LO ; 
 int /*<<< orphan*/  REG_A6XX_VBIF_GATE_OFF_WRREQ_EN ; 
 int /*<<< orphan*/  REG_A6XX_VFD_ADDR_MODE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_VPC_ADDR_MODE_CNTL ; 
 int /*<<< orphan*/  REG_A6XX_VSC_ADDR_MODE_CNTL ; 
 int a6xx_cp_init (struct msm_gpu*) ; 
 int /*<<< orphan*/  a6xx_flush (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a6xx_gmu_clear_oob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a6xx_gmu_set_oob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a6xx_idle (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a6xx_set_hwcg (struct msm_gpu*,int) ; 
 int a6xx_ucode_init (struct msm_gpu*) ; 
 int a6xx_zap_shader_init (struct msm_gpu*) ; 
 int adreno_hw_init (struct msm_gpu*) ; 
 int /*<<< orphan*/  dev_warn_once (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpu_write64 (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct a6xx_gpu* to_a6xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static int a6xx_hw_init(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	int ret;

	/* Make sure the GMU keeps the GPU on while we set it up */
	a6xx_gmu_set_oob(&a6xx_gpu->gmu, GMU_OOB_GPU_SET);

	gpu_write(gpu, REG_A6XX_RBBM_SECVID_TSB_CNTL, 0);

	/*
	 * Disable the trusted memory range - we don't actually supported secure
	 * memory rendering at this point in time and we don't want to block off
	 * part of the virtual memory space.
	 */
	gpu_write64(gpu, REG_A6XX_RBBM_SECVID_TSB_TRUSTED_BASE_LO,
		REG_A6XX_RBBM_SECVID_TSB_TRUSTED_BASE_HI, 0x00000000);
	gpu_write(gpu, REG_A6XX_RBBM_SECVID_TSB_TRUSTED_SIZE, 0x00000000);

	/* Turn on 64 bit addressing for all blocks */
	gpu_write(gpu, REG_A6XX_CP_ADDR_MODE_CNTL, 0x1);
	gpu_write(gpu, REG_A6XX_VSC_ADDR_MODE_CNTL, 0x1);
	gpu_write(gpu, REG_A6XX_GRAS_ADDR_MODE_CNTL, 0x1);
	gpu_write(gpu, REG_A6XX_RB_ADDR_MODE_CNTL, 0x1);
	gpu_write(gpu, REG_A6XX_PC_ADDR_MODE_CNTL, 0x1);
	gpu_write(gpu, REG_A6XX_HLSQ_ADDR_MODE_CNTL, 0x1);
	gpu_write(gpu, REG_A6XX_VFD_ADDR_MODE_CNTL, 0x1);
	gpu_write(gpu, REG_A6XX_VPC_ADDR_MODE_CNTL, 0x1);
	gpu_write(gpu, REG_A6XX_UCHE_ADDR_MODE_CNTL, 0x1);
	gpu_write(gpu, REG_A6XX_SP_ADDR_MODE_CNTL, 0x1);
	gpu_write(gpu, REG_A6XX_TPL1_ADDR_MODE_CNTL, 0x1);
	gpu_write(gpu, REG_A6XX_RBBM_SECVID_TSB_ADDR_MODE_CNTL, 0x1);

	/* enable hardware clockgating */
	a6xx_set_hwcg(gpu, true);

	/* VBIF start */
	gpu_write(gpu, REG_A6XX_VBIF_GATE_OFF_WRREQ_EN, 0x00000009);
	gpu_write(gpu, REG_A6XX_RBBM_VBIF_CLIENT_QOS_CNTL, 0x3);

	/* Make all blocks contribute to the GPU BUSY perf counter */
	gpu_write(gpu, REG_A6XX_RBBM_PERFCTR_GPU_BUSY_MASKED, 0xffffffff);

	/* Disable L2 bypass in the UCHE */
	gpu_write(gpu, REG_A6XX_UCHE_WRITE_RANGE_MAX_LO, 0xffffffc0);
	gpu_write(gpu, REG_A6XX_UCHE_WRITE_RANGE_MAX_HI, 0x0001ffff);
	gpu_write(gpu, REG_A6XX_UCHE_TRAP_BASE_LO, 0xfffff000);
	gpu_write(gpu, REG_A6XX_UCHE_TRAP_BASE_HI, 0x0001ffff);
	gpu_write(gpu, REG_A6XX_UCHE_WRITE_THRU_BASE_LO, 0xfffff000);
	gpu_write(gpu, REG_A6XX_UCHE_WRITE_THRU_BASE_HI, 0x0001ffff);

	/* Set the GMEM VA range [0x100000:0x100000 + gpu->gmem - 1] */
	gpu_write64(gpu, REG_A6XX_UCHE_GMEM_RANGE_MIN_LO,
		REG_A6XX_UCHE_GMEM_RANGE_MIN_HI, 0x00100000);

	gpu_write64(gpu, REG_A6XX_UCHE_GMEM_RANGE_MAX_LO,
		REG_A6XX_UCHE_GMEM_RANGE_MAX_HI,
		0x00100000 + adreno_gpu->gmem - 1);

	gpu_write(gpu, REG_A6XX_UCHE_FILTER_CNTL, 0x804);
	gpu_write(gpu, REG_A6XX_UCHE_CACHE_WAYS, 0x4);

	gpu_write(gpu, REG_A6XX_CP_ROQ_THRESHOLDS_2, 0x010000c0);
	gpu_write(gpu, REG_A6XX_CP_ROQ_THRESHOLDS_1, 0x8040362c);

	/* Setting the mem pool size */
	gpu_write(gpu, REG_A6XX_CP_MEM_POOL_SIZE, 128);

	/* Setting the primFifo thresholds default values */
	gpu_write(gpu, REG_A6XX_PC_DBG_ECO_CNTL, (0x300 << 11));

	/* Set the AHB default slave response to "ERROR" */
	gpu_write(gpu, REG_A6XX_CP_AHB_CNTL, 0x1);

	/* Turn on performance counters */
	gpu_write(gpu, REG_A6XX_RBBM_PERFCTR_CNTL, 0x1);

	/* Select CP0 to always count cycles */
	gpu_write(gpu, REG_A6XX_CP_PERFCTR_CP_SEL_0, PERF_CP_ALWAYS_COUNT);

	gpu_write(gpu, REG_A6XX_RB_NC_MODE_CNTL, 2 << 1);
	gpu_write(gpu, REG_A6XX_TPL1_NC_MODE_CNTL, 2 << 1);
	gpu_write(gpu, REG_A6XX_SP_NC_MODE_CNTL, 2 << 1);
	gpu_write(gpu, REG_A6XX_UCHE_MODE_CNTL, 2 << 21);

	/* Enable fault detection */
	gpu_write(gpu, REG_A6XX_RBBM_INTERFACE_HANG_INT_CNTL,
		(1 << 30) | 0x1fffff);

	gpu_write(gpu, REG_A6XX_UCHE_CLIENT_PF, 1);

	/* Protect registers from the CP */
	gpu_write(gpu, REG_A6XX_CP_PROTECT_CNTL, 0x00000003);

	gpu_write(gpu, REG_A6XX_CP_PROTECT(0),
		A6XX_PROTECT_RDONLY(0x600, 0x51));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(1), A6XX_PROTECT_RW(0xae50, 0x2));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(2), A6XX_PROTECT_RW(0x9624, 0x13));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(3), A6XX_PROTECT_RW(0x8630, 0x8));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(4), A6XX_PROTECT_RW(0x9e70, 0x1));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(5), A6XX_PROTECT_RW(0x9e78, 0x187));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(6), A6XX_PROTECT_RW(0xf000, 0x810));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(7),
		A6XX_PROTECT_RDONLY(0xfc00, 0x3));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(8), A6XX_PROTECT_RW(0x50e, 0x0));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(9), A6XX_PROTECT_RDONLY(0x50f, 0x0));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(10), A6XX_PROTECT_RW(0x510, 0x0));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(11),
		A6XX_PROTECT_RDONLY(0x0, 0x4f9));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(12),
		A6XX_PROTECT_RDONLY(0x501, 0xa));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(13),
		A6XX_PROTECT_RDONLY(0x511, 0x44));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(14), A6XX_PROTECT_RW(0xe00, 0xe));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(15), A6XX_PROTECT_RW(0x8e00, 0x0));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(16), A6XX_PROTECT_RW(0x8e50, 0xf));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(17), A6XX_PROTECT_RW(0xbe02, 0x0));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(18),
		A6XX_PROTECT_RW(0xbe20, 0x11f3));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(19), A6XX_PROTECT_RW(0x800, 0x82));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(20), A6XX_PROTECT_RW(0x8a0, 0x8));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(21), A6XX_PROTECT_RW(0x8ab, 0x19));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(22), A6XX_PROTECT_RW(0x900, 0x4d));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(23), A6XX_PROTECT_RW(0x98d, 0x76));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(24),
			A6XX_PROTECT_RDONLY(0x980, 0x4));
	gpu_write(gpu, REG_A6XX_CP_PROTECT(25), A6XX_PROTECT_RW(0xa630, 0x0));

	/* Enable interrupts */
	gpu_write(gpu, REG_A6XX_RBBM_INT_0_MASK, A6XX_INT_MASK);

	ret = adreno_hw_init(gpu);
	if (ret)
		goto out;

	ret = a6xx_ucode_init(gpu);
	if (ret)
		goto out;

	/* Always come up on rb 0 */
	a6xx_gpu->cur_ring = gpu->rb[0];

	/* Enable the SQE_to start the CP engine */
	gpu_write(gpu, REG_A6XX_CP_SQE_CNTL, 1);

	ret = a6xx_cp_init(gpu);
	if (ret)
		goto out;

	/*
	 * Try to load a zap shader into the secure world. If successful
	 * we can use the CP to switch out of secure mode. If not then we
	 * have no resource but to try to switch ourselves out manually. If we
	 * guessed wrong then access to the RBBM_SECVID_TRUST_CNTL register will
	 * be blocked and a permissions violation will soon follow.
	 */
	ret = a6xx_zap_shader_init(gpu);
	if (!ret) {
		OUT_PKT7(gpu->rb[0], CP_SET_SECURE_MODE, 1);
		OUT_RING(gpu->rb[0], 0x00000000);

		a6xx_flush(gpu, gpu->rb[0]);
		if (!a6xx_idle(gpu, gpu->rb[0]))
			return -EINVAL;
	} else {
		/* Print a warning so if we die, we know why */
		dev_warn_once(gpu->dev->dev,
			"Zap shader not enabled - using SECVID_TRUST_CNTL instead\n");
		gpu_write(gpu, REG_A6XX_RBBM_SECVID_TRUST_CNTL, 0x0);
		ret = 0;
	}

out:
	/*
	 * Tell the GMU that we are done touching the GPU and it can start power
	 * management
	 */
	a6xx_gmu_clear_oob(&a6xx_gpu->gmu, GMU_OOB_GPU_SET);

	/* Take the GMU out of its special boot mode */
	a6xx_gmu_clear_oob(&a6xx_gpu->gmu, GMU_OOB_BOOT_SLUMBER);

	return ret;
}