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
struct msm_gpu {int /*<<< orphan*/  aspace; } ;
struct a5xx_crashdumper {int /*<<< orphan*/  bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_unreference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_gem_put_iova (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_gem_put_vaddr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a5xx_crashdumper_free(struct msm_gpu *gpu,
		struct a5xx_crashdumper *dumper)
{
	msm_gem_put_iova(dumper->bo, gpu->aspace);
	msm_gem_put_vaddr(dumper->bo);

	drm_gem_object_unreference(dumper->bo);
}