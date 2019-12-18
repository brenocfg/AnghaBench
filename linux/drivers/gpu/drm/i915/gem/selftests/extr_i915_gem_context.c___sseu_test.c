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
struct intel_sseu {int /*<<< orphan*/  slice_mask; } ;
struct intel_context {int dummy; } ;
struct igt_spinner {int dummy; } ;
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 int __intel_context_reconfigure_sseu (struct intel_context*,struct intel_sseu) ; 
 int __sseu_finish (char const*,unsigned int,struct intel_context*,struct drm_i915_gem_object*,int /*<<< orphan*/ ,struct igt_spinner*) ; 
 int __sseu_prepare (char const*,unsigned int,struct intel_context*,struct igt_spinner**) ; 
 int /*<<< orphan*/  hweight32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igt_spinner_end (struct igt_spinner*) ; 
 int /*<<< orphan*/  igt_spinner_fini (struct igt_spinner*) ; 
 int /*<<< orphan*/  kfree (struct igt_spinner*) ; 

__attribute__((used)) static int
__sseu_test(const char *name,
	    unsigned int flags,
	    struct intel_context *ce,
	    struct drm_i915_gem_object *obj,
	    struct intel_sseu sseu)
{
	struct igt_spinner *spin = NULL;
	int ret;

	ret = __sseu_prepare(name, flags, ce, &spin);
	if (ret)
		return ret;

	ret = __intel_context_reconfigure_sseu(ce, sseu);
	if (ret)
		goto out_spin;

	ret = __sseu_finish(name, flags, ce, obj,
			    hweight32(sseu.slice_mask), spin);

out_spin:
	if (spin) {
		igt_spinner_end(spin);
		igt_spinner_fini(spin);
		kfree(spin);
	}
	return ret;
}