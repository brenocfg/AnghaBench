#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct panfrost_perfcnt {struct drm_gem_shmem_object* buf; TYPE_2__* bo; struct panfrost_file_priv* user; int /*<<< orphan*/  dump_comp; int /*<<< orphan*/  bosize; } ;
struct panfrost_file_priv {int dummy; } ;
struct panfrost_device {struct panfrost_perfcnt* perfcnt; int /*<<< orphan*/  ddev; int /*<<< orphan*/  dev; } ;
struct drm_gem_shmem_object {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct TYPE_5__ {TYPE_1__ base; } ;

/* Variables and functions */
 int EBUSY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GPU_CMD ; 
 int GPU_CMD_CLEAN_INV_CACHES ; 
 int GPU_CMD_PERFCNT_CLEAR ; 
 int /*<<< orphan*/  GPU_INT_CLEAR ; 
 int GPU_IRQ_CLEAN_CACHES_COMPLETED ; 
 int GPU_IRQ_PERFCNT_SAMPLE_COMPLETED ; 
 int /*<<< orphan*/  GPU_PERFCNT_CFG ; 
 int GPU_PERFCNT_CFG_AS (int /*<<< orphan*/ ) ; 
 int GPU_PERFCNT_CFG_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPU_PERFCNT_CFG_MODE_MANUAL ; 
 int GPU_PERFCNT_CFG_SETSEL (unsigned int) ; 
 int /*<<< orphan*/  GPU_PRFCNT_JM_EN ; 
 int /*<<< orphan*/  GPU_PRFCNT_MMU_L2_EN ; 
 int /*<<< orphan*/  GPU_PRFCNT_SHADER_EN ; 
 int /*<<< orphan*/  GPU_PRFCNT_TILER_EN ; 
 int /*<<< orphan*/  HW_ISSUE_8186 ; 
 scalar_t__ IS_ERR (struct drm_gem_shmem_object*) ; 
 int PTR_ERR (struct drm_gem_shmem_object*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct drm_gem_shmem_object* drm_gem_shmem_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_gem_shmem_object* drm_gem_shmem_vmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_shmem_vunmap (int /*<<< orphan*/ *,struct drm_gem_shmem_object*) ; 
 int /*<<< orphan*/  gpu_write (struct panfrost_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 scalar_t__ panfrost_has_hw_issue (struct panfrost_device*,int /*<<< orphan*/ ) ; 
 int panfrost_mmu_map (TYPE_2__*) ; 
 scalar_t__ panfrost_model_is_bifrost (struct panfrost_device*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 TYPE_2__* to_panfrost_bo (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int panfrost_perfcnt_enable_locked(struct panfrost_device *pfdev,
					  struct panfrost_file_priv *user,
					  unsigned int counterset)
{
	struct panfrost_perfcnt *perfcnt = pfdev->perfcnt;
	struct drm_gem_shmem_object *bo;
	u32 cfg;
	int ret;

	if (user == perfcnt->user)
		return 0;
	else if (perfcnt->user)
		return -EBUSY;

	ret = pm_runtime_get_sync(pfdev->dev);
	if (ret < 0)
		return ret;

	bo = drm_gem_shmem_create(pfdev->ddev, perfcnt->bosize);
	if (IS_ERR(bo))
		return PTR_ERR(bo);

	perfcnt->bo = to_panfrost_bo(&bo->base);

	/* Map the perfcnt buf in the address space attached to file_priv. */
	ret = panfrost_mmu_map(perfcnt->bo);
	if (ret)
		goto err_put_bo;

	perfcnt->buf = drm_gem_shmem_vmap(&bo->base);
	if (IS_ERR(perfcnt->buf)) {
		ret = PTR_ERR(perfcnt->buf);
		goto err_put_bo;
	}

	/*
	 * Invalidate the cache and clear the counters to start from a fresh
	 * state.
	 */
	reinit_completion(&pfdev->perfcnt->dump_comp);
	gpu_write(pfdev, GPU_INT_CLEAR,
		  GPU_IRQ_CLEAN_CACHES_COMPLETED |
		  GPU_IRQ_PERFCNT_SAMPLE_COMPLETED);
	gpu_write(pfdev, GPU_CMD, GPU_CMD_PERFCNT_CLEAR);
	gpu_write(pfdev, GPU_CMD, GPU_CMD_CLEAN_INV_CACHES);
	ret = wait_for_completion_timeout(&pfdev->perfcnt->dump_comp,
					  msecs_to_jiffies(1000));
	if (!ret) {
		ret = -ETIMEDOUT;
		goto err_vunmap;
	}

	perfcnt->user = user;

	/*
	 * Always use address space 0 for now.
	 * FIXME: this needs to be updated when we start using different
	 * address space.
	 */
	cfg = GPU_PERFCNT_CFG_AS(0) |
	      GPU_PERFCNT_CFG_MODE(GPU_PERFCNT_CFG_MODE_MANUAL);

	/*
	 * Bifrost GPUs have 2 set of counters, but we're only interested by
	 * the first one for now.
	 */
	if (panfrost_model_is_bifrost(pfdev))
		cfg |= GPU_PERFCNT_CFG_SETSEL(counterset);

	gpu_write(pfdev, GPU_PRFCNT_JM_EN, 0xffffffff);
	gpu_write(pfdev, GPU_PRFCNT_SHADER_EN, 0xffffffff);
	gpu_write(pfdev, GPU_PRFCNT_MMU_L2_EN, 0xffffffff);

	/*
	 * Due to PRLAM-8186 we need to disable the Tiler before we enable HW
	 * counters.
	 */
	if (panfrost_has_hw_issue(pfdev, HW_ISSUE_8186))
		gpu_write(pfdev, GPU_PRFCNT_TILER_EN, 0);
	else
		gpu_write(pfdev, GPU_PRFCNT_TILER_EN, 0xffffffff);

	gpu_write(pfdev, GPU_PERFCNT_CFG, cfg);

	if (panfrost_has_hw_issue(pfdev, HW_ISSUE_8186))
		gpu_write(pfdev, GPU_PRFCNT_TILER_EN, 0xffffffff);

	return 0;

err_vunmap:
	drm_gem_shmem_vunmap(&perfcnt->bo->base.base, perfcnt->buf);
err_put_bo:
	drm_gem_object_put_unlocked(&bo->base);
	return ret;
}