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
struct TYPE_3__ {int /*<<< orphan*/  sysfs_metric; } ;
struct TYPE_4__ {int /*<<< orphan*/ * metrics_kobj; TYPE_1__ test_config; } ;
struct drm_i915_private {TYPE_2__ perf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void i915_perf_unregister(struct drm_i915_private *dev_priv)
{
	if (!dev_priv->perf.metrics_kobj)
		return;

	sysfs_remove_group(dev_priv->perf.metrics_kobj,
			   &dev_priv->perf.test_config.sysfs_metric);

	kobject_put(dev_priv->perf.metrics_kobj);
	dev_priv->perf.metrics_kobj = NULL;
}