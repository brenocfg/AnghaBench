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
struct TYPE_2__ {struct drm_device* dev; } ;
struct exynos_drm_gem {int /*<<< orphan*/  pages; int /*<<< orphan*/  dma_attrs; scalar_t__ dma_addr; int /*<<< orphan*/  cookie; int /*<<< orphan*/  size; TYPE_1__ base; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_dma_dev (struct drm_device*) ; 

__attribute__((used)) static void exynos_drm_free_buf(struct exynos_drm_gem *exynos_gem)
{
	struct drm_device *dev = exynos_gem->base.dev;

	if (!exynos_gem->dma_addr) {
		DRM_DEV_DEBUG_KMS(dev->dev, "dma_addr is invalid.\n");
		return;
	}

	DRM_DEV_DEBUG_KMS(dev->dev, "dma_addr(0x%lx), size(0x%lx)\n",
			(unsigned long)exynos_gem->dma_addr, exynos_gem->size);

	dma_free_attrs(to_dma_dev(dev), exynos_gem->size, exynos_gem->cookie,
			(dma_addr_t)exynos_gem->dma_addr,
			exynos_gem->dma_attrs);

	kvfree(exynos_gem->pages);
}