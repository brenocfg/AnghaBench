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
struct intel_overlay {int /*<<< orphan*/  last_flip; TYPE_2__* i915; } ;
struct i915_request {int dummy; } ;
typedef  int /*<<< orphan*/  i915_gem_retire_fn ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_active_peek (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_active_set (int /*<<< orphan*/ *,struct i915_request*) ; 
 int /*<<< orphan*/  i915_gem_active_set_retire_fn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_request*) ; 

__attribute__((used)) static void intel_overlay_submit_request(struct intel_overlay *overlay,
					 struct i915_request *rq,
					 i915_gem_retire_fn retire)
{
	GEM_BUG_ON(i915_gem_active_peek(&overlay->last_flip,
					&overlay->i915->drm.struct_mutex));
	i915_gem_active_set_retire_fn(&overlay->last_flip, retire,
				      &overlay->i915->drm.struct_mutex);
	i915_gem_active_set(&overlay->last_flip, rq);
	i915_request_add(rq);
}