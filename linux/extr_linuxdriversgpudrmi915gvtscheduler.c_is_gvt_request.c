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
struct i915_request {int /*<<< orphan*/  gem_context; } ;

/* Variables and functions */
 int i915_gem_context_force_single_submission (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_gvt_request(struct i915_request *req)
{
	return i915_gem_context_force_single_submission(req->gem_context);
}