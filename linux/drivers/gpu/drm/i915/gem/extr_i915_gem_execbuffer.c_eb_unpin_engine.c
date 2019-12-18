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
struct intel_timeline {int /*<<< orphan*/  mutex; } ;
struct intel_context {struct intel_timeline* timeline; } ;
struct i915_execbuffer {struct intel_context* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  __eb_unpin_context (struct i915_execbuffer*,struct intel_context*) ; 
 int /*<<< orphan*/  intel_context_exit (struct intel_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eb_unpin_engine(struct i915_execbuffer *eb)
{
	struct intel_context *ce = eb->context;
	struct intel_timeline *tl = ce->timeline;

	mutex_lock(&tl->mutex);
	intel_context_exit(ce);
	mutex_unlock(&tl->mutex);

	__eb_unpin_context(eb, ce);
}