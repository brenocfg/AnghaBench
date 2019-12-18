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
struct TYPE_2__ {int /*<<< orphan*/  dp_wq; } ;
struct drm_i915_private {int /*<<< orphan*/  wq; TYPE_1__ hotplug; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i915_workqueues_cleanup(struct drm_i915_private *dev_priv)
{
	destroy_workqueue(dev_priv->hotplug.dp_wq);
	destroy_workqueue(dev_priv->wq);
}