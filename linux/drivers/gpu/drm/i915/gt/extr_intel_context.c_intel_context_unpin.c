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
struct intel_context {int /*<<< orphan*/  pin_mutex; int /*<<< orphan*/  gem_context; TYPE_3__* ops; TYPE_2__* timeline; TYPE_1__* engine; int /*<<< orphan*/  pin_count; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* unpin ) (struct intel_context*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  fence_context; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_context_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_context_active_release (struct intel_context*) ; 
 int /*<<< orphan*/  intel_context_get (struct intel_context*) ; 
 int /*<<< orphan*/  intel_context_put (struct intel_context*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct intel_context*) ; 

void intel_context_unpin(struct intel_context *ce)
{
	if (likely(atomic_add_unless(&ce->pin_count, -1, 1)))
		return;

	/* We may be called from inside intel_context_pin() to evict another */
	intel_context_get(ce);
	mutex_lock_nested(&ce->pin_mutex, SINGLE_DEPTH_NESTING);

	if (likely(atomic_dec_and_test(&ce->pin_count))) {
		GEM_TRACE("%s context:%llx retire\n",
			  ce->engine->name, ce->timeline->fence_context);

		ce->ops->unpin(ce);

		i915_gem_context_put(ce->gem_context);
		intel_context_active_release(ce);
	}

	mutex_unlock(&ce->pin_mutex);
	intel_context_put(ce);
}