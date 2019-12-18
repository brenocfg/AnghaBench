#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  attr; } ;
struct TYPE_11__ {scalar_t__ id; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  sysfs_metric; TYPE_4__ sysfs_metric_id; } ;
struct TYPE_12__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * metrics_kobj; TYPE_5__ test_config; int /*<<< orphan*/  initialized; } ;
struct TYPE_9__ {TYPE_2__* primary; } ;
struct drm_i915_private {TYPE_6__ perf; TYPE_3__ drm; } ;
struct TYPE_8__ {TYPE_1__* kdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_CFL_GT2 (struct drm_i915_private*) ; 
 scalar_t__ IS_CFL_GT3 (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_COFFEELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_KBL_GT2 (struct drm_i915_private*) ; 
 scalar_t__ IS_KBL_GT3 (struct drm_i915_private*) ; 
 scalar_t__ IS_SKL_GT2 (struct drm_i915_private*) ; 
 scalar_t__ IS_SKL_GT3 (struct drm_i915_private*) ; 
 scalar_t__ IS_SKL_GT4 (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i915_perf_load_test_config_bdw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_load_test_config_bxt (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_load_test_config_cflgt2 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_load_test_config_cflgt3 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_load_test_config_chv (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_load_test_config_cnl (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_load_test_config_glk (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_load_test_config_hsw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_load_test_config_icl (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_load_test_config_kblgt2 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_load_test_config_kblgt3 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_load_test_config_sklgt2 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_load_test_config_sklgt3 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_load_test_config_sklgt4 (struct drm_i915_private*) ; 
 int /*<<< orphan*/ * kobject_create_and_add (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_attr_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void i915_perf_register(struct drm_i915_private *dev_priv)
{
	int ret;

	if (!dev_priv->perf.initialized)
		return;

	/* To be sure we're synchronized with an attempted
	 * i915_perf_open_ioctl(); considering that we register after
	 * being exposed to userspace.
	 */
	mutex_lock(&dev_priv->perf.lock);

	dev_priv->perf.metrics_kobj =
		kobject_create_and_add("metrics",
				       &dev_priv->drm.primary->kdev->kobj);
	if (!dev_priv->perf.metrics_kobj)
		goto exit;

	sysfs_attr_init(&dev_priv->perf.test_config.sysfs_metric_id.attr);

	if (INTEL_GEN(dev_priv) >= 11) {
		i915_perf_load_test_config_icl(dev_priv);
	} else if (IS_CANNONLAKE(dev_priv)) {
		i915_perf_load_test_config_cnl(dev_priv);
	} else if (IS_COFFEELAKE(dev_priv)) {
		if (IS_CFL_GT2(dev_priv))
			i915_perf_load_test_config_cflgt2(dev_priv);
		if (IS_CFL_GT3(dev_priv))
			i915_perf_load_test_config_cflgt3(dev_priv);
	} else if (IS_GEMINILAKE(dev_priv)) {
		i915_perf_load_test_config_glk(dev_priv);
	} else if (IS_KABYLAKE(dev_priv)) {
		if (IS_KBL_GT2(dev_priv))
			i915_perf_load_test_config_kblgt2(dev_priv);
		else if (IS_KBL_GT3(dev_priv))
			i915_perf_load_test_config_kblgt3(dev_priv);
	} else if (IS_BROXTON(dev_priv)) {
		i915_perf_load_test_config_bxt(dev_priv);
	} else if (IS_SKYLAKE(dev_priv)) {
		if (IS_SKL_GT2(dev_priv))
			i915_perf_load_test_config_sklgt2(dev_priv);
		else if (IS_SKL_GT3(dev_priv))
			i915_perf_load_test_config_sklgt3(dev_priv);
		else if (IS_SKL_GT4(dev_priv))
			i915_perf_load_test_config_sklgt4(dev_priv);
	} else if (IS_CHERRYVIEW(dev_priv)) {
		i915_perf_load_test_config_chv(dev_priv);
	} else if (IS_BROADWELL(dev_priv)) {
		i915_perf_load_test_config_bdw(dev_priv);
	} else if (IS_HASWELL(dev_priv)) {
		i915_perf_load_test_config_hsw(dev_priv);
}

	if (dev_priv->perf.test_config.id == 0)
		goto sysfs_error;

	ret = sysfs_create_group(dev_priv->perf.metrics_kobj,
				 &dev_priv->perf.test_config.sysfs_metric);
	if (ret)
		goto sysfs_error;

	atomic_set(&dev_priv->perf.test_config.ref_count, 1);

	goto exit;

sysfs_error:
	kobject_put(dev_priv->perf.metrics_kobj);
	dev_priv->perf.metrics_kobj = NULL;

exit:
	mutex_unlock(&dev_priv->perf.lock);
}