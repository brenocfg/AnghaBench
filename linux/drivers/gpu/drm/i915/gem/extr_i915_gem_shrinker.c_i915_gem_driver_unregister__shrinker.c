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
struct TYPE_2__ {int /*<<< orphan*/  shrinker; int /*<<< orphan*/  oom_notifier; int /*<<< orphan*/  vmap_notifier; } ;
struct drm_i915_private {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_oom_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_shrinker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_vmap_purge_notifier (int /*<<< orphan*/ *) ; 

void i915_gem_driver_unregister__shrinker(struct drm_i915_private *i915)
{
	WARN_ON(unregister_vmap_purge_notifier(&i915->mm.vmap_notifier));
	WARN_ON(unregister_oom_notifier(&i915->mm.oom_notifier));
	unregister_shrinker(&i915->mm.shrinker);
}