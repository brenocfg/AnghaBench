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
typedef  scalar_t__ u64 ;
struct intel_gt {struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_GT_GFX_RC6 ; 
 int /*<<< orphan*/  GEN6_GT_GFX_RC6p ; 
 int /*<<< orphan*/  GEN6_GT_GFX_RC6pp ; 
 scalar_t__ HAS_RC6p (struct drm_i915_private*) ; 
 scalar_t__ HAS_RC6pp (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  VLV_GT_RENDER_RC6 ; 
 scalar_t__ intel_rc6_residency_ns (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 __get_rc6(struct intel_gt *gt)
{
	struct drm_i915_private *i915 = gt->i915;
	u64 val;

	val = intel_rc6_residency_ns(i915,
				     IS_VALLEYVIEW(i915) ?
				     VLV_GT_RENDER_RC6 :
				     GEN6_GT_GFX_RC6);

	if (HAS_RC6p(i915))
		val += intel_rc6_residency_ns(i915, GEN6_GT_GFX_RC6p);

	if (HAS_RC6pp(i915))
		val += intel_rc6_residency_ns(i915, GEN6_GT_GFX_RC6pp);

	return val;
}