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
struct tegra_bo {void* vaddr; } ;
struct drm_gem_object {int dummy; } ;
struct dma_buf {struct drm_gem_object* priv; } ;

/* Variables and functions */
 struct tegra_bo* to_tegra_bo (struct drm_gem_object*) ; 

__attribute__((used)) static void *tegra_gem_prime_vmap(struct dma_buf *buf)
{
	struct drm_gem_object *gem = buf->priv;
	struct tegra_bo *bo = to_tegra_bo(gem);

	return bo->vaddr;
}