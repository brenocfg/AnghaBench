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
typedef  int /*<<< orphan*/  u32 ;
struct whitelist {unsigned int count; int /*<<< orphan*/  nopid; int /*<<< orphan*/ * reg; } ;
struct intel_engine_cs {struct drm_i915_private* i915; int /*<<< orphan*/  mmio_base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_FORCE_TO_NONPRIV (int /*<<< orphan*/  const,unsigned int) ; 
 unsigned int RING_MAX_NONPRIV_SLOTS ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void whitelist_apply(struct intel_engine_cs *engine,
			    const struct whitelist *w)
{
	struct drm_i915_private *dev_priv = engine->i915;
	const u32 base = engine->mmio_base;
	unsigned int i;

	if (!w)
		return;

	intel_uncore_forcewake_get(engine->i915, FORCEWAKE_ALL);

	for (i = 0; i < w->count; i++)
		I915_WRITE_FW(RING_FORCE_TO_NONPRIV(base, i),
			      i915_mmio_reg_offset(w->reg[i]));

	/* And clear the rest just in case of garbage */
	for (; i < RING_MAX_NONPRIV_SLOTS; i++)
		I915_WRITE_FW(RING_FORCE_TO_NONPRIV(base, i), w->nopid);

	intel_uncore_forcewake_put(engine->i915, FORCEWAKE_ALL);
}