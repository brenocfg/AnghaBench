#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_15__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_14__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_13__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_12__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_11__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_10__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_9__ {scalar_t__ min; scalar_t__ max; } ;
struct intel_limit {TYPE_8__ dot; TYPE_7__ vco; TYPE_6__ m; TYPE_5__ p; TYPE_4__ m1; TYPE_3__ m2; TYPE_2__ p1; TYPE_1__ n; } ;
struct drm_i915_private {int dummy; } ;
struct dpll {scalar_t__ n; scalar_t__ p1; scalar_t__ m2; scalar_t__ m1; scalar_t__ p; scalar_t__ m; scalar_t__ vco; scalar_t__ dot; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTELPllInvalid (char*) ; 
 int /*<<< orphan*/  IS_CHERRYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_GEN9_LP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_PINEVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_VALLEYVIEW (struct drm_i915_private*) ; 

__attribute__((used)) static bool intel_PLL_is_valid(struct drm_i915_private *dev_priv,
			       const struct intel_limit *limit,
			       const struct dpll *clock)
{
	if (clock->n   < limit->n.min   || limit->n.max   < clock->n)
		INTELPllInvalid("n out of range\n");
	if (clock->p1  < limit->p1.min  || limit->p1.max  < clock->p1)
		INTELPllInvalid("p1 out of range\n");
	if (clock->m2  < limit->m2.min  || limit->m2.max  < clock->m2)
		INTELPllInvalid("m2 out of range\n");
	if (clock->m1  < limit->m1.min  || limit->m1.max  < clock->m1)
		INTELPllInvalid("m1 out of range\n");

	if (!IS_PINEVIEW(dev_priv) && !IS_VALLEYVIEW(dev_priv) &&
	    !IS_CHERRYVIEW(dev_priv) && !IS_GEN9_LP(dev_priv))
		if (clock->m1 <= clock->m2)
			INTELPllInvalid("m1 <= m2\n");

	if (!IS_VALLEYVIEW(dev_priv) && !IS_CHERRYVIEW(dev_priv) &&
	    !IS_GEN9_LP(dev_priv)) {
		if (clock->p < limit->p.min || limit->p.max < clock->p)
			INTELPllInvalid("p out of range\n");
		if (clock->m < limit->m.min || limit->m.max < clock->m)
			INTELPllInvalid("m out of range\n");
	}

	if (clock->vco < limit->vco.min || limit->vco.max < clock->vco)
		INTELPllInvalid("vco out of range\n");
	/* XXX: We may need to be checking "Dot clock" depending on the multiplier,
	 * connector, etc., rather than just a single range.
	 */
	if (clock->dot < limit->dot.min || limit->dot.max < clock->dot)
		INTELPllInvalid("dot out of range\n");

	return true;
}