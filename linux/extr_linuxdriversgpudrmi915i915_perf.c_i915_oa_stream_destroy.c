#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct i915_perf_stream {int /*<<< orphan*/  oa_config; scalar_t__ ctx; struct drm_i915_private* dev_priv; } ;
struct TYPE_8__ {scalar_t__ missed; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* disable_metric_set ) (struct drm_i915_private*) ;} ;
struct TYPE_9__ {TYPE_3__ spurious_report_rs; TYPE_1__ ops; struct i915_perf_stream* exclusive_stream; } ;
struct TYPE_10__ {TYPE_4__ oa; } ;
struct TYPE_7__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_5__ perf; TYPE_2__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_NOTE (char*,scalar_t__) ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  free_oa_buffer (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oa_put_render_ctx_id (struct i915_perf_stream*) ; 
 int /*<<< orphan*/  put_oa_config (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*) ; 

__attribute__((used)) static void i915_oa_stream_destroy(struct i915_perf_stream *stream)
{
	struct drm_i915_private *dev_priv = stream->dev_priv;

	BUG_ON(stream != dev_priv->perf.oa.exclusive_stream);

	/*
	 * Unset exclusive_stream first, it will be checked while disabling
	 * the metric set on gen8+.
	 */
	mutex_lock(&dev_priv->drm.struct_mutex);
	dev_priv->perf.oa.exclusive_stream = NULL;
	dev_priv->perf.oa.ops.disable_metric_set(dev_priv);
	mutex_unlock(&dev_priv->drm.struct_mutex);

	free_oa_buffer(dev_priv);

	intel_uncore_forcewake_put(dev_priv, FORCEWAKE_ALL);
	intel_runtime_pm_put(dev_priv);

	if (stream->ctx)
		oa_put_render_ctx_id(stream);

	put_oa_config(dev_priv, stream->oa_config);

	if (dev_priv->perf.oa.spurious_report_rs.missed) {
		DRM_NOTE("%d spurious OA report notices suppressed due to ratelimiting\n",
			 dev_priv->perf.oa.spurious_report_rs.missed);
	}
}