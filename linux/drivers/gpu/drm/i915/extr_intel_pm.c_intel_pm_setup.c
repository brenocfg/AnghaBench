#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int suspended; int /*<<< orphan*/  wakeref_count; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_waiters; TYPE_2__ power; int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {TYPE_3__ rps; } ;
struct drm_i915_private {TYPE_1__ runtime_pm; TYPE_4__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void intel_pm_setup(struct drm_i915_private *dev_priv)
{
	mutex_init(&dev_priv->gt_pm.rps.lock);
	mutex_init(&dev_priv->gt_pm.rps.power.mutex);

	atomic_set(&dev_priv->gt_pm.rps.num_waiters, 0);

	dev_priv->runtime_pm.suspended = false;
	atomic_set(&dev_priv->runtime_pm.wakeref_count, 0);
}