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
struct drm_printer {int dummy; } ;
struct drm_i915_error_state_buf {int dummy; } ;

/* Variables and functions */
 struct drm_printer i915_error_printer (struct drm_i915_error_state_buf*) ; 
 int /*<<< orphan*/  i915_params_dump (struct i915_params const*,struct drm_printer*) ; 

__attribute__((used)) static void err_print_params(struct drm_i915_error_state_buf *m,
			     const struct i915_params *params)
{
	struct drm_printer p = i915_error_printer(m);

	i915_params_dump(params, &p);
}