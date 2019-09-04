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
struct intel_context {int /*<<< orphan*/  gem_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DRM_I915_GVT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ i915_gem_context_force_single_submission (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ctx_single_port_submission(const struct intel_context *ce)
{
	return (IS_ENABLED(CONFIG_DRM_I915_GVT) &&
		i915_gem_context_force_single_submission(ce->gem_context));
}