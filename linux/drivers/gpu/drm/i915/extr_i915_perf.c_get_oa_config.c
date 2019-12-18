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
struct i915_oa_config {int /*<<< orphan*/  ref_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  metrics_lock; int /*<<< orphan*/  metrics_idr; struct i915_oa_config test_config; } ;
struct drm_i915_private {TYPE_1__ perf; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct i915_oa_config* idr_find (int /*<<< orphan*/ *,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_oa_config(struct drm_i915_private *dev_priv,
			 int metrics_set,
			 struct i915_oa_config **out_config)
{
	int ret;

	if (metrics_set == 1) {
		*out_config = &dev_priv->perf.test_config;
		atomic_inc(&dev_priv->perf.test_config.ref_count);
		return 0;
	}

	ret = mutex_lock_interruptible(&dev_priv->perf.metrics_lock);
	if (ret)
		return ret;

	*out_config = idr_find(&dev_priv->perf.metrics_idr, metrics_set);
	if (!*out_config)
		ret = -EINVAL;
	else
		atomic_inc(&(*out_config)->ref_count);

	mutex_unlock(&dev_priv->perf.metrics_lock);

	return ret;
}