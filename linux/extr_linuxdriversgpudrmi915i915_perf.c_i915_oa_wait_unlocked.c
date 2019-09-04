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
struct i915_perf_stream {struct drm_i915_private* dev_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  poll_wq; int /*<<< orphan*/  periodic; } ;
struct TYPE_4__ {TYPE_1__ oa; } ;
struct drm_i915_private {TYPE_2__ perf; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  oa_buffer_check_unlocked (struct drm_i915_private*) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_oa_wait_unlocked(struct i915_perf_stream *stream)
{
	struct drm_i915_private *dev_priv = stream->dev_priv;

	/* We would wait indefinitely if periodic sampling is not enabled */
	if (!dev_priv->perf.oa.periodic)
		return -EIO;

	return wait_event_interruptible(dev_priv->perf.oa.poll_wq,
					oa_buffer_check_unlocked(dev_priv));
}