#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct i915_perf_stream {int /*<<< orphan*/  poll_wq; int /*<<< orphan*/  periodic; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  oa_buffer_check_unlocked (struct i915_perf_stream*) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_oa_wait_unlocked(struct i915_perf_stream *stream)
{
	/* We would wait indefinitely if periodic sampling is not enabled */
	if (!stream->periodic)
		return -EIO;

	return wait_event_interruptible(stream->poll_wq,
					oa_buffer_check_unlocked(stream));
}