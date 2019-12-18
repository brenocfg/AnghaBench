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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct msm_gpu {int nr_rings; int global_faults; int /*<<< orphan*/  name; TYPE_5__* pdev; } ;
struct TYPE_8__ {int fast_rate; } ;
struct TYPE_7__ {int patchid; int minor; int major; int core; } ;
struct adreno_gpu {int gmem; TYPE_4__* funcs; TYPE_3__ base; TYPE_2__ rev; TYPE_1__* info; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int (* get_timestamp ) (struct msm_gpu*,int*) ;} ;
struct TYPE_6__ {int revn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
#define  MSM_PARAM_CHIP_ID 136 
#define  MSM_PARAM_FAULTS 135 
#define  MSM_PARAM_GMEM_BASE 134 
#define  MSM_PARAM_GMEM_SIZE 133 
#define  MSM_PARAM_GPU_ID 132 
#define  MSM_PARAM_MAX_FREQ 131 
#define  MSM_PARAM_NR_RINGS 130 
#define  MSM_PARAM_PP_PGTABLE 129 
#define  MSM_PARAM_TIMESTAMP 128 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int stub1 (struct msm_gpu*,int*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

int adreno_get_param(struct msm_gpu *gpu, uint32_t param, uint64_t *value)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);

	switch (param) {
	case MSM_PARAM_GPU_ID:
		*value = adreno_gpu->info->revn;
		return 0;
	case MSM_PARAM_GMEM_SIZE:
		*value = adreno_gpu->gmem;
		return 0;
	case MSM_PARAM_GMEM_BASE:
		*value = 0x100000;
		return 0;
	case MSM_PARAM_CHIP_ID:
		*value = adreno_gpu->rev.patchid |
				(adreno_gpu->rev.minor << 8) |
				(adreno_gpu->rev.major << 16) |
				(adreno_gpu->rev.core << 24);
		return 0;
	case MSM_PARAM_MAX_FREQ:
		*value = adreno_gpu->base.fast_rate;
		return 0;
	case MSM_PARAM_TIMESTAMP:
		if (adreno_gpu->funcs->get_timestamp) {
			int ret;

			pm_runtime_get_sync(&gpu->pdev->dev);
			ret = adreno_gpu->funcs->get_timestamp(gpu, value);
			pm_runtime_put_autosuspend(&gpu->pdev->dev);

			return ret;
		}
		return -EINVAL;
	case MSM_PARAM_NR_RINGS:
		*value = gpu->nr_rings;
		return 0;
	case MSM_PARAM_PP_PGTABLE:
		*value = 0;
		return 0;
	case MSM_PARAM_FAULTS:
		*value = gpu->global_faults;
		return 0;
	default:
		DBG("%s: invalid param: %u", gpu->name, param);
		return -EINVAL;
	}
}