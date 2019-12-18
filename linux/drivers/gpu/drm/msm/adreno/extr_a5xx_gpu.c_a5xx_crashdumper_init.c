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
struct msm_gpu {int /*<<< orphan*/  aspace; int /*<<< orphan*/  dev; } ;
struct a5xx_crashdumper {int /*<<< orphan*/  ptr; int /*<<< orphan*/  bo; int /*<<< orphan*/  iova; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSM_BO_UNCACHED ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_1M ; 
 int /*<<< orphan*/  msm_gem_kernel_new_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_object_set_name (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int a5xx_crashdumper_init(struct msm_gpu *gpu,
		struct a5xx_crashdumper *dumper)
{
	dumper->ptr = msm_gem_kernel_new_locked(gpu->dev,
		SZ_1M, MSM_BO_UNCACHED, gpu->aspace,
		&dumper->bo, &dumper->iova);

	if (!IS_ERR(dumper->ptr))
		msm_gem_object_set_name(dumper->bo, "crashdump");

	return PTR_ERR_OR_ZERO(dumper->ptr);
}