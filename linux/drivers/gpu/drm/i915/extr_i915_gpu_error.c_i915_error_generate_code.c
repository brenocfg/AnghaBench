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
typedef  int u32 ;
struct i915_gpu_state {struct drm_i915_error_engine* engine; } ;
struct TYPE_2__ {int instdone; } ;
struct drm_i915_error_engine {int ipehr; TYPE_1__ instdone; } ;

/* Variables and functions */

__attribute__((used)) static u32 i915_error_generate_code(struct i915_gpu_state *error)
{
	const struct drm_i915_error_engine *ee = error->engine;

	/*
	 * IPEHR would be an ideal way to detect errors, as it's the gross
	 * measure of "the command that hung." However, has some very common
	 * synchronization commands which almost always appear in the case
	 * strictly a client bug. Use instdone to differentiate those some.
	 */
	return ee ? ee->ipehr ^ ee->instdone.instdone : 0;
}