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
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  poll_wq; } ;
struct TYPE_4__ {TYPE_1__ oa; } ;
struct drm_i915_private {TYPE_2__ perf; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i915_oa_poll_wait(struct i915_perf_stream *stream,
			      struct file *file,
			      poll_table *wait)
{
	struct drm_i915_private *dev_priv = stream->dev_priv;

	poll_wait(file, &dev_priv->perf.oa.poll_wq, wait);
}