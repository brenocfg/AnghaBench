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
struct i915_perf_stream {struct drm_i915_private* dev_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* oa_enable ) (struct drm_i915_private*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  poll_check_timer; scalar_t__ periodic; TYPE_1__ ops; } ;
struct TYPE_6__ {TYPE_2__ oa; } ;
struct drm_i915_private {TYPE_3__ perf; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED ; 
 int /*<<< orphan*/  POLL_PERIOD ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*) ; 

__attribute__((used)) static void i915_oa_stream_enable(struct i915_perf_stream *stream)
{
	struct drm_i915_private *dev_priv = stream->dev_priv;

	dev_priv->perf.oa.ops.oa_enable(dev_priv);

	if (dev_priv->perf.oa.periodic)
		hrtimer_start(&dev_priv->perf.oa.poll_check_timer,
			      ns_to_ktime(POLL_PERIOD),
			      HRTIMER_MODE_REL_PINNED);
}