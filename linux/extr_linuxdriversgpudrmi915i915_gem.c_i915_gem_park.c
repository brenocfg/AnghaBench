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
struct TYPE_4__ {int /*<<< orphan*/  idle_work; int /*<<< orphan*/  awake; int /*<<< orphan*/  active_requests; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ gt; int /*<<< orphan*/  wq; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_TRACE (char*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 

void i915_gem_park(struct drm_i915_private *i915)
{
	GEM_TRACE("\n");

	lockdep_assert_held(&i915->drm.struct_mutex);
	GEM_BUG_ON(i915->gt.active_requests);

	if (!i915->gt.awake)
		return;

	/* Defer the actual call to __i915_gem_park() to prevent ping-pongs */
	mod_delayed_work(i915->wq, &i915->gt.idle_work, msecs_to_jiffies(100));
}