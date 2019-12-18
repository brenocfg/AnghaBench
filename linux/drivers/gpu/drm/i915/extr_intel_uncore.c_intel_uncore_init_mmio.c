#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  write_fw_domains; int /*<<< orphan*/  read_fw_domains; int /*<<< orphan*/  force_wake_put; int /*<<< orphan*/  force_wake_get; } ;
struct intel_uncore {int /*<<< orphan*/  flags; TYPE_1__ funcs; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ HAS_FPGA_DBG_UNCLAIMED (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN_RANGE (struct drm_i915_private*,int,int) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  UNCORE_HAS_DBG_UNCLAIMED ; 
 int /*<<< orphan*/  UNCORE_HAS_FIFO ; 
 int /*<<< orphan*/  UNCORE_HAS_FORCEWAKE ; 
 int /*<<< orphan*/  UNCORE_HAS_FPGA_DBG_UNCLAIMED ; 
 int intel_uncore_has_forcewake (struct intel_uncore*) ; 
 scalar_t__ intel_uncore_unclaimed_mmio (struct intel_uncore*) ; 
 int /*<<< orphan*/  intel_vgpu_active (struct drm_i915_private*) ; 
 int uncore_forcewake_init (struct intel_uncore*) ; 
 int /*<<< orphan*/  uncore_mmio_cleanup (struct intel_uncore*) ; 
 int uncore_mmio_setup (struct intel_uncore*) ; 
 int /*<<< orphan*/  uncore_raw_init (struct intel_uncore*) ; 

int intel_uncore_init_mmio(struct intel_uncore *uncore)
{
	struct drm_i915_private *i915 = uncore->i915;
	int ret;

	ret = uncore_mmio_setup(uncore);
	if (ret)
		return ret;

	if (INTEL_GEN(i915) > 5 && !intel_vgpu_active(i915))
		uncore->flags |= UNCORE_HAS_FORCEWAKE;

	if (!intel_uncore_has_forcewake(uncore)) {
		uncore_raw_init(uncore);
	} else {
		ret = uncore_forcewake_init(uncore);
		if (ret)
			goto out_mmio_cleanup;
	}

	/* make sure fw funcs are set if and only if we have fw*/
	GEM_BUG_ON(intel_uncore_has_forcewake(uncore) != !!uncore->funcs.force_wake_get);
	GEM_BUG_ON(intel_uncore_has_forcewake(uncore) != !!uncore->funcs.force_wake_put);
	GEM_BUG_ON(intel_uncore_has_forcewake(uncore) != !!uncore->funcs.read_fw_domains);
	GEM_BUG_ON(intel_uncore_has_forcewake(uncore) != !!uncore->funcs.write_fw_domains);

	if (HAS_FPGA_DBG_UNCLAIMED(i915))
		uncore->flags |= UNCORE_HAS_FPGA_DBG_UNCLAIMED;

	if (IS_VALLEYVIEW(i915) || IS_CHERRYVIEW(i915))
		uncore->flags |= UNCORE_HAS_DBG_UNCLAIMED;

	if (IS_GEN_RANGE(i915, 6, 7))
		uncore->flags |= UNCORE_HAS_FIFO;

	/* clear out unclaimed reg detection bit */
	if (intel_uncore_unclaimed_mmio(uncore))
		DRM_DEBUG("unclaimed mmio detected on uncore init, clearing\n");

	return 0;

out_mmio_cleanup:
	uncore_mmio_cleanup(uncore);

	return ret;
}