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
struct TYPE_2__ {int initialized; int /*<<< orphan*/  ops; int /*<<< orphan*/  sysctl_header; int /*<<< orphan*/  metrics_idr; } ;
struct drm_i915_private {TYPE_1__ perf; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_config ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct drm_i915_private*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_sysctl_table (int /*<<< orphan*/ ) ; 

void i915_perf_fini(struct drm_i915_private *dev_priv)
{
	if (!dev_priv->perf.initialized)
		return;

	idr_for_each(&dev_priv->perf.metrics_idr, destroy_config, dev_priv);
	idr_destroy(&dev_priv->perf.metrics_idr);

	unregister_sysctl_table(dev_priv->perf.sysctl_header);

	memset(&dev_priv->perf.ops, 0, sizeof(dev_priv->perf.ops));

	dev_priv->perf.initialized = false;
}