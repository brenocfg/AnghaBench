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
struct drm_printer {struct drm_i915_error_state_buf* arg; int /*<<< orphan*/  printfn; } ;
struct drm_i915_error_state_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i915_printfn_error ; 

__attribute__((used)) static inline struct drm_printer
i915_error_printer(struct drm_i915_error_state_buf *e)
{
	struct drm_printer p = {
		.printfn = __i915_printfn_error,
		.arg = e,
	};
	return p;
}