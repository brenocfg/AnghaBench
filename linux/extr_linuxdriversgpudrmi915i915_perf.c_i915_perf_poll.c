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
struct i915_perf_stream {struct drm_i915_private* dev_priv; } ;
struct file {struct i915_perf_stream* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_1__ perf; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  i915_perf_poll_locked (struct drm_i915_private*,struct i915_perf_stream*,struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t i915_perf_poll(struct file *file, poll_table *wait)
{
	struct i915_perf_stream *stream = file->private_data;
	struct drm_i915_private *dev_priv = stream->dev_priv;
	__poll_t ret;

	mutex_lock(&dev_priv->perf.lock);
	ret = i915_perf_poll_locked(dev_priv, stream, file, wait);
	mutex_unlock(&dev_priv->perf.lock);

	return ret;
}