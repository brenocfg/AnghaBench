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
struct drm_gem_object {int /*<<< orphan*/  resv; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 struct dma_fence* dma_resv_get_excl_rcu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void panfrost_acquire_object_fences(struct drm_gem_object **bos,
					   int bo_count,
					   struct dma_fence **implicit_fences)
{
	int i;

	for (i = 0; i < bo_count; i++)
		implicit_fences[i] = dma_resv_get_excl_rcu(bos[i]->resv);
}