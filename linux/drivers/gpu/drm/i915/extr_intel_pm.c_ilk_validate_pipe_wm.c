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
struct intel_wm_config {int num_pipes_active; int /*<<< orphan*/  sprites_scaled; int /*<<< orphan*/  sprites_enabled; } ;
struct intel_pipe_wm {int /*<<< orphan*/ * wm; int /*<<< orphan*/  sprites_scaled; int /*<<< orphan*/  sprites_enabled; } ;
struct ilk_wm_maximums {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  INTEL_DDB_PART_1_2 ; 
 int /*<<< orphan*/  ilk_compute_wm_maximums (struct drm_i915_private const*,int /*<<< orphan*/ ,struct intel_wm_config const*,int /*<<< orphan*/ ,struct ilk_wm_maximums*) ; 
 int /*<<< orphan*/  ilk_validate_wm_level (int /*<<< orphan*/ ,struct ilk_wm_maximums*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ilk_validate_pipe_wm(const struct drm_i915_private *dev_priv,
				 struct intel_pipe_wm *pipe_wm)
{
	/* LP0 watermark maximums depend on this pipe alone */
	const struct intel_wm_config config = {
		.num_pipes_active = 1,
		.sprites_enabled = pipe_wm->sprites_enabled,
		.sprites_scaled = pipe_wm->sprites_scaled,
	};
	struct ilk_wm_maximums max;

	/* LP0 watermarks always use 1/2 DDB partitioning */
	ilk_compute_wm_maximums(dev_priv, 0, &config, INTEL_DDB_PART_1_2, &max);

	/* At least LP0 must be valid */
	if (!ilk_validate_wm_level(0, &max, &pipe_wm->wm[0])) {
		DRM_DEBUG_KMS("LP0 watermark invalid\n");
		return false;
	}

	return true;
}