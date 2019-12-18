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
struct TYPE_6__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_5__ {TYPE_3__ pm_notifier; int /*<<< orphan*/  retire_work; int /*<<< orphan*/  idle_work; } ;
struct TYPE_4__ {int /*<<< orphan*/  pm_notifications; } ;
struct drm_i915_private {TYPE_2__ gem; TYPE_1__ gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blocking_notifier_chain_register (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  idle_work_handler ; 
 int /*<<< orphan*/  pm_notifier ; 
 int /*<<< orphan*/  retire_work_handler ; 

void i915_gem_init__pm(struct drm_i915_private *i915)
{
	INIT_WORK(&i915->gem.idle_work, idle_work_handler);
	INIT_DELAYED_WORK(&i915->gem.retire_work, retire_work_handler);

	i915->gem.pm_notifier.notifier_call = pm_notifier;
	blocking_notifier_chain_register(&i915->gt.pm_notifications,
					 &i915->gem.pm_notifier);
}