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
struct intel_context {int /*<<< orphan*/  pin_count; } ;
struct i915_execbuffer {TYPE_2__* i915; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  intel_context_unpin (struct intel_context*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__eb_unpin_context(struct i915_execbuffer *eb, struct intel_context *ce)
{
	if (likely(atomic_add_unless(&ce->pin_count, -1, 1)))
		return;

	mutex_lock(&eb->i915->drm.struct_mutex);
	intel_context_unpin(ce);
	mutex_unlock(&eb->i915->drm.struct_mutex);
}