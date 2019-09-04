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
struct i915_perf_stream {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
#define  I915_PERF_IOCTL_DISABLE 129 
#define  I915_PERF_IOCTL_ENABLE 128 
 int /*<<< orphan*/  i915_perf_disable_locked (struct i915_perf_stream*) ; 
 int /*<<< orphan*/  i915_perf_enable_locked (struct i915_perf_stream*) ; 

__attribute__((used)) static long i915_perf_ioctl_locked(struct i915_perf_stream *stream,
				   unsigned int cmd,
				   unsigned long arg)
{
	switch (cmd) {
	case I915_PERF_IOCTL_ENABLE:
		i915_perf_enable_locked(stream);
		return 0;
	case I915_PERF_IOCTL_DISABLE:
		i915_perf_disable_locked(stream);
		return 0;
	}

	return -EINVAL;
}