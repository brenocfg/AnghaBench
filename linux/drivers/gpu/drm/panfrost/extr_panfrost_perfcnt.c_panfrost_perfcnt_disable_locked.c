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
struct panfrost_perfcnt {TYPE_2__* bo; int /*<<< orphan*/ * buf; struct panfrost_file_priv* user; } ;
struct panfrost_file_priv {int dummy; } ;
struct panfrost_device {int /*<<< orphan*/  dev; struct panfrost_perfcnt* perfcnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPU_PERFCNT_CFG ; 
 int GPU_PERFCNT_CFG_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPU_PERFCNT_CFG_MODE_OFF ; 
 int /*<<< orphan*/  GPU_PRFCNT_JM_EN ; 
 int /*<<< orphan*/  GPU_PRFCNT_MMU_L2_EN ; 
 int /*<<< orphan*/  GPU_PRFCNT_SHADER_EN ; 
 int /*<<< orphan*/  GPU_PRFCNT_TILER_EN ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_shmem_vunmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpu_write (struct panfrost_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int panfrost_perfcnt_disable_locked(struct panfrost_device *pfdev,
					   struct panfrost_file_priv *user)
{
	struct panfrost_perfcnt *perfcnt = pfdev->perfcnt;

	if (user != perfcnt->user)
		return -EINVAL;

	gpu_write(pfdev, GPU_PRFCNT_JM_EN, 0x0);
	gpu_write(pfdev, GPU_PRFCNT_SHADER_EN, 0x0);
	gpu_write(pfdev, GPU_PRFCNT_MMU_L2_EN, 0x0);
	gpu_write(pfdev, GPU_PRFCNT_TILER_EN, 0);
	gpu_write(pfdev, GPU_PERFCNT_CFG,
		  GPU_PERFCNT_CFG_MODE(GPU_PERFCNT_CFG_MODE_OFF));

	perfcnt->user = NULL;
	drm_gem_shmem_vunmap(&perfcnt->bo->base.base, perfcnt->buf);
	perfcnt->buf = NULL;
	drm_gem_object_put_unlocked(&perfcnt->bo->base.base);
	perfcnt->bo = NULL;
	pm_runtime_mark_last_busy(pfdev->dev);
	pm_runtime_put_autosuspend(pfdev->dev);

	return 0;
}