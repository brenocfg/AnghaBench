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
struct i915_request {int /*<<< orphan*/  reserved_space; TYPE_1__* engine; TYPE_2__* hw_context; } ;
struct TYPE_4__ {int /*<<< orphan*/  vm; } ;
struct TYPE_3__ {int (* emit_flush ) (struct i915_request*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT_INVALIDATE ; 
 scalar_t__ EXECLISTS_REQUEST_SIZE ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int emit_pdps (struct i915_request*) ; 
 scalar_t__ i915_vm_is_4lvl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_context_is_pinned (TYPE_2__*) ; 
 int stub1 (struct i915_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int execlists_request_alloc(struct i915_request *request)
{
	int ret;

	GEM_BUG_ON(!intel_context_is_pinned(request->hw_context));

	/*
	 * Flush enough space to reduce the likelihood of waiting after
	 * we start building the request - in which case we will just
	 * have to repeat work.
	 */
	request->reserved_space += EXECLISTS_REQUEST_SIZE;

	/*
	 * Note that after this point, we have committed to using
	 * this request as it is being used to both track the
	 * state of engine initialisation and liveness of the
	 * golden renderstate above. Think twice before you try
	 * to cancel/unwind this request now.
	 */

	/* Unconditionally invalidate GPU caches and TLBs. */
	if (i915_vm_is_4lvl(request->hw_context->vm))
		ret = request->engine->emit_flush(request, EMIT_INVALIDATE);
	else
		ret = emit_pdps(request);
	if (ret)
		return ret;

	request->reserved_space -= EXECLISTS_REQUEST_SIZE;
	return 0;
}