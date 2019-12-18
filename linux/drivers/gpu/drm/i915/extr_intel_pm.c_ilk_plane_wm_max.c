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
struct intel_wm_config {int num_pipes_active; scalar_t__ sprites_enabled; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum intel_ddb_partitioning { ____Placeholder_intel_ddb_partitioning } intel_ddb_partitioning ;
struct TYPE_2__ {unsigned int num_pipes; } ;

/* Variables and functions */
 int INTEL_DDB_PART_5_6 ; 
 int INTEL_GEN (struct drm_i915_private const*) ; 
 TYPE_1__* INTEL_INFO (struct drm_i915_private const*) ; 
 unsigned int ilk_display_fifo_size (struct drm_i915_private const*) ; 
 int /*<<< orphan*/  ilk_plane_wm_reg_max (struct drm_i915_private const*,int,int) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ilk_plane_wm_max(const struct drm_i915_private *dev_priv,
				     int level,
				     const struct intel_wm_config *config,
				     enum intel_ddb_partitioning ddb_partitioning,
				     bool is_sprite)
{
	unsigned int fifo_size = ilk_display_fifo_size(dev_priv);

	/* if sprites aren't enabled, sprites get nothing */
	if (is_sprite && !config->sprites_enabled)
		return 0;

	/* HSW allows LP1+ watermarks even with multiple pipes */
	if (level == 0 || config->num_pipes_active > 1) {
		fifo_size /= INTEL_INFO(dev_priv)->num_pipes;

		/*
		 * For some reason the non self refresh
		 * FIFO size is only half of the self
		 * refresh FIFO size on ILK/SNB.
		 */
		if (INTEL_GEN(dev_priv) <= 6)
			fifo_size /= 2;
	}

	if (config->sprites_enabled) {
		/* level 0 is always calculated with 1:1 split */
		if (level > 0 && ddb_partitioning == INTEL_DDB_PART_5_6) {
			if (is_sprite)
				fifo_size *= 5;
			fifo_size /= 6;
		} else {
			fifo_size /= 2;
		}
	}

	/* clamp to max that the registers can hold */
	return min(fifo_size, ilk_plane_wm_reg_max(dev_priv, level, is_sprite));
}