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
struct intel_engine_cs {int /*<<< orphan*/  context_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DRM_I915_DEBUG_GEM ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int LRC_HEADER_PAGES ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  POISON_INUSE ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_redzone(void *vaddr, const struct intel_engine_cs *engine)
{
	if (!IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		return;

	vaddr += LRC_HEADER_PAGES * PAGE_SIZE;
	vaddr += engine->context_size;

	memset(vaddr, POISON_INUSE, I915_GTT_PAGE_SIZE);
}