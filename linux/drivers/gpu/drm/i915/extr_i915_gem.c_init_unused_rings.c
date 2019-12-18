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
struct intel_gt {struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_I830 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PRB1_BASE ; 
 int /*<<< orphan*/  PRB2_BASE ; 
 int /*<<< orphan*/  SRB0_BASE ; 
 int /*<<< orphan*/  SRB1_BASE ; 
 int /*<<< orphan*/  SRB2_BASE ; 
 int /*<<< orphan*/  SRB3_BASE ; 
 int /*<<< orphan*/  init_unused_ring (struct intel_gt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_unused_rings(struct intel_gt *gt)
{
	struct drm_i915_private *i915 = gt->i915;

	if (IS_I830(i915)) {
		init_unused_ring(gt, PRB1_BASE);
		init_unused_ring(gt, SRB0_BASE);
		init_unused_ring(gt, SRB1_BASE);
		init_unused_ring(gt, SRB2_BASE);
		init_unused_ring(gt, SRB3_BASE);
	} else if (IS_GEN(i915, 2)) {
		init_unused_ring(gt, SRB0_BASE);
		init_unused_ring(gt, SRB1_BASE);
	} else if (IS_GEN(i915, 3)) {
		init_unused_ring(gt, PRB1_BASE);
		init_unused_ring(gt, PRB2_BASE);
	}
}