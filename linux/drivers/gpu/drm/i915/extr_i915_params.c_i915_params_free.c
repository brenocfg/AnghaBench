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
struct i915_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE ; 
 int /*<<< orphan*/  I915_PARAMS_FOR_EACH (int /*<<< orphan*/ ) ; 

void i915_params_free(struct i915_params *params)
{
#define FREE(T, x, ...) free_param(#T, &params->x);
	I915_PARAMS_FOR_EACH(FREE);
#undef FREE
}