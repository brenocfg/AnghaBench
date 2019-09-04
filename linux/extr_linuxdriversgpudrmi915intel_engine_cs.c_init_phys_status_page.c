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
struct TYPE_3__ {int /*<<< orphan*/  page_addr; } ;
struct intel_engine_cs {scalar_t__ id; TYPE_1__ status_page; struct drm_i915_private* i915; } ;
struct drm_i915_private {TYPE_2__* status_page_dmah; int /*<<< orphan*/  drm; } ;
struct TYPE_4__ {int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ RCS ; 
 TYPE_2__* drm_pci_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_phys_status_page(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	GEM_BUG_ON(engine->id != RCS);

	dev_priv->status_page_dmah =
		drm_pci_alloc(&dev_priv->drm, PAGE_SIZE, PAGE_SIZE);
	if (!dev_priv->status_page_dmah)
		return -ENOMEM;

	engine->status_page.page_addr = dev_priv->status_page_dmah->vaddr;
	memset(engine->status_page.page_addr, 0, PAGE_SIZE);

	return 0;
}