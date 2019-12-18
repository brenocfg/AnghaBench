#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct i915_ggtt {int /*<<< orphan*/  do_idle_maps; } ;
struct TYPE_6__ {TYPE_2__* pdev; } ;
struct drm_i915_private {struct i915_ggtt ggtt; TYPE_3__ drm; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i915_gem_wait_for_idle (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void i915_gem_gtt_finish_pages(struct drm_i915_gem_object *obj,
			       struct sg_table *pages)
{
	struct drm_i915_private *dev_priv = to_i915(obj->base.dev);
	struct device *kdev = &dev_priv->drm.pdev->dev;
	struct i915_ggtt *ggtt = &dev_priv->ggtt;

	if (unlikely(ggtt->do_idle_maps)) {
		if (i915_gem_wait_for_idle(dev_priv, 0, MAX_SCHEDULE_TIMEOUT)) {
			DRM_ERROR("Failed to wait for idle; VT'd may hang.\n");
			/* Wait a bit, in hopes it avoids the hang */
			udelay(10);
		}
	}

	dma_unmap_sg(kdev, pages->sgl, pages->nents, PCI_DMA_BIDIRECTIONAL);
}