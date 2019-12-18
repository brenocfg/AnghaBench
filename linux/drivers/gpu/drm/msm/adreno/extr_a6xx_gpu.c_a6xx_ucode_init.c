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
struct msm_gpu {TYPE_1__* pdev; } ;
struct adreno_gpu {int /*<<< orphan*/ * fw; } ;
struct a6xx_gpu {int /*<<< orphan*/  sqe_iova; int /*<<< orphan*/ * sqe_bo; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t ADRENO_FW_SQE ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_A6XX_CP_SQE_INSTR_BASE_HI ; 
 int /*<<< orphan*/  REG_A6XX_CP_SQE_INSTR_BASE_LO ; 
 int /*<<< orphan*/ * adreno_fw_create_bo (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpu_write64 (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_gem_object_set_name (int /*<<< orphan*/ *,char*) ; 
 struct a6xx_gpu* to_a6xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static int a6xx_ucode_init(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);

	if (!a6xx_gpu->sqe_bo) {
		a6xx_gpu->sqe_bo = adreno_fw_create_bo(gpu,
			adreno_gpu->fw[ADRENO_FW_SQE], &a6xx_gpu->sqe_iova);

		if (IS_ERR(a6xx_gpu->sqe_bo)) {
			int ret = PTR_ERR(a6xx_gpu->sqe_bo);

			a6xx_gpu->sqe_bo = NULL;
			DRM_DEV_ERROR(&gpu->pdev->dev,
				"Could not allocate SQE ucode: %d\n", ret);

			return ret;
		}

		msm_gem_object_set_name(a6xx_gpu->sqe_bo, "sqefw");
	}

	gpu_write64(gpu, REG_A6XX_CP_SQE_INSTR_BASE_LO,
		REG_A6XX_CP_SQE_INSTR_BASE_HI, a6xx_gpu->sqe_iova);

	return 0;
}