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
struct i915_gpu_error {int dummy; } ;

/* Variables and functions */
 int i915_reset_backoff (struct i915_gpu_error*) ; 
 int i915_terminally_wedged (struct i915_gpu_error*) ; 

__attribute__((used)) static inline bool i915_reset_backoff_or_wedged(struct i915_gpu_error *error)
{
	return i915_reset_backoff(error) | i915_terminally_wedged(error);
}