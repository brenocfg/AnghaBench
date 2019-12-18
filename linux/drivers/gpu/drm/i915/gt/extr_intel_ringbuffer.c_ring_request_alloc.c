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
struct i915_request {int /*<<< orphan*/  reserved_space; TYPE_2__* engine; TYPE_1__* timeline; int /*<<< orphan*/  hw_context; } ;
struct TYPE_4__ {int (* emit_flush ) (struct i915_request*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int has_initial_breadcrumb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT_INVALIDATE ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ LEGACY_REQUEST_SIZE ; 
 int /*<<< orphan*/  intel_context_is_pinned (int /*<<< orphan*/ ) ; 
 int stub1 (struct i915_request*,int /*<<< orphan*/ ) ; 
 int switch_context (struct i915_request*) ; 

__attribute__((used)) static int ring_request_alloc(struct i915_request *request)
{
	int ret;

	GEM_BUG_ON(!intel_context_is_pinned(request->hw_context));
	GEM_BUG_ON(request->timeline->has_initial_breadcrumb);

	/*
	 * Flush enough space to reduce the likelihood of waiting after
	 * we start building the request - in which case we will just
	 * have to repeat work.
	 */
	request->reserved_space += LEGACY_REQUEST_SIZE;

	/* Unconditionally invalidate GPU caches and TLBs. */
	ret = request->engine->emit_flush(request, EMIT_INVALIDATE);
	if (ret)
		return ret;

	ret = switch_context(request);
	if (ret)
		return ret;

	request->reserved_space -= LEGACY_REQUEST_SIZE;
	return 0;
}