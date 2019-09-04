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
struct i915_request {TYPE_1__* engine; } ;
struct TYPE_2__ {int /*<<< orphan*/  context_status_notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DRM_I915_GVT ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,struct i915_request*) ; 

__attribute__((used)) static inline void
execlists_context_status_change(struct i915_request *rq, unsigned long status)
{
	/*
	 * Only used when GVT-g is enabled now. When GVT-g is disabled,
	 * The compiler should eliminate this function as dead-code.
	 */
	if (!IS_ENABLED(CONFIG_DRM_I915_GVT))
		return;

	atomic_notifier_call_chain(&rq->engine->context_status_notifier,
				   status, rq);
}