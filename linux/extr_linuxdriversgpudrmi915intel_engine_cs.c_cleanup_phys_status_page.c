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
struct TYPE_2__ {int /*<<< orphan*/ * page_addr; } ;
struct intel_engine_cs {TYPE_1__ status_page; struct drm_i915_private* i915; } ;
struct drm_i915_private {int /*<<< orphan*/  status_page_dmah; int /*<<< orphan*/  drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_pci_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_phys_status_page(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	if (!dev_priv->status_page_dmah)
		return;

	drm_pci_free(&dev_priv->drm, dev_priv->status_page_dmah);
	engine->status_page.page_addr = NULL;
}