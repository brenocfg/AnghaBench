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
struct i915_perf_stream {scalar_t__ pollin; TYPE_1__* ops; } ;
struct file {int dummy; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* poll_wait ) (struct i915_perf_stream*,struct file*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  stub1 (struct i915_perf_stream*,struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t i915_perf_poll_locked(struct drm_i915_private *dev_priv,
					  struct i915_perf_stream *stream,
					  struct file *file,
					  poll_table *wait)
{
	__poll_t events = 0;

	stream->ops->poll_wait(stream, file, wait);

	/* Note: we don't explicitly check whether there's something to read
	 * here since this path may be very hot depending on what else
	 * userspace is polling, or on the timeout in use. We rely solely on
	 * the hrtimer/oa_poll_check_timer_cb to notify us when there are
	 * samples to read.
	 */
	if (stream->pollin)
		events |= EPOLLIN;

	return events;
}