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
struct whitelist {int /*<<< orphan*/  nopid; scalar_t__ count; } ;
struct intel_engine_cs {scalar_t__ id; int /*<<< orphan*/  mmio_base; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_COFFEELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_ICELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 scalar_t__ RCS ; 
 int /*<<< orphan*/  RING_NOPID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdw_whitelist_build (struct whitelist*) ; 
 int /*<<< orphan*/  bxt_whitelist_build (struct whitelist*) ; 
 int /*<<< orphan*/  cfl_whitelist_build (struct whitelist*) ; 
 int /*<<< orphan*/  chv_whitelist_build (struct whitelist*) ; 
 int /*<<< orphan*/  cnl_whitelist_build (struct whitelist*) ; 
 int /*<<< orphan*/  glk_whitelist_build (struct whitelist*) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_whitelist_build (struct whitelist*) ; 
 int /*<<< orphan*/  kbl_whitelist_build (struct whitelist*) ; 
 int /*<<< orphan*/  skl_whitelist_build (struct whitelist*) ; 

__attribute__((used)) static struct whitelist *whitelist_build(struct intel_engine_cs *engine,
					 struct whitelist *w)
{
	struct drm_i915_private *i915 = engine->i915;

	GEM_BUG_ON(engine->id != RCS);

	w->count = 0;
	w->nopid = i915_mmio_reg_offset(RING_NOPID(engine->mmio_base));

	if (INTEL_GEN(i915) < 8)
		return NULL;
	else if (IS_BROADWELL(i915))
		bdw_whitelist_build(w);
	else if (IS_CHERRYVIEW(i915))
		chv_whitelist_build(w);
	else if (IS_SKYLAKE(i915))
		skl_whitelist_build(w);
	else if (IS_BROXTON(i915))
		bxt_whitelist_build(w);
	else if (IS_KABYLAKE(i915))
		kbl_whitelist_build(w);
	else if (IS_GEMINILAKE(i915))
		glk_whitelist_build(w);
	else if (IS_COFFEELAKE(i915))
		cfl_whitelist_build(w);
	else if (IS_CANNONLAKE(i915))
		cnl_whitelist_build(w);
	else if (IS_ICELAKE(i915))
		icl_whitelist_build(w);
	else
		MISSING_CASE(INTEL_GEN(i915));

	return w;
}