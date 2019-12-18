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
struct intel_engine_cs {int /*<<< orphan*/  name; TYPE_2__* i915; int /*<<< orphan*/  context_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DRM_I915_DEBUG_GEM ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int LRC_HEADER_PAGES ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  POISON_INUSE ; 
 int /*<<< orphan*/  dev_err_once (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ memchr_inv (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_redzone(const void *vaddr, const struct intel_engine_cs *engine)
{
	if (!IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		return;

	vaddr += LRC_HEADER_PAGES * PAGE_SIZE;
	vaddr += engine->context_size;

	if (memchr_inv(vaddr, POISON_INUSE, I915_GTT_PAGE_SIZE))
		dev_err_once(engine->i915->drm.dev,
			     "%s context redzone overwritten!\n",
			     engine->name);
}