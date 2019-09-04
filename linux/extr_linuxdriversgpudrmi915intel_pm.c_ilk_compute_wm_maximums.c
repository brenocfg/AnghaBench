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
struct intel_wm_config {int dummy; } ;
struct ilk_wm_maximums {int /*<<< orphan*/  fbc; int /*<<< orphan*/  cur; void* spr; void* pri; } ;
struct drm_device {int dummy; } ;
typedef  enum intel_ddb_partitioning { ____Placeholder_intel_ddb_partitioning } intel_ddb_partitioning ;

/* Variables and functions */
 int /*<<< orphan*/  ilk_cursor_wm_max (struct drm_device const*,int,struct intel_wm_config const*) ; 
 int /*<<< orphan*/  ilk_fbc_wm_reg_max (int /*<<< orphan*/ ) ; 
 void* ilk_plane_wm_max (struct drm_device const*,int,struct intel_wm_config const*,int,int) ; 
 int /*<<< orphan*/  to_i915 (struct drm_device const*) ; 

__attribute__((used)) static void ilk_compute_wm_maximums(const struct drm_device *dev,
				    int level,
				    const struct intel_wm_config *config,
				    enum intel_ddb_partitioning ddb_partitioning,
				    struct ilk_wm_maximums *max)
{
	max->pri = ilk_plane_wm_max(dev, level, config, ddb_partitioning, false);
	max->spr = ilk_plane_wm_max(dev, level, config, ddb_partitioning, true);
	max->cur = ilk_cursor_wm_max(dev, level, config);
	max->fbc = ilk_fbc_wm_reg_max(to_i915(dev));
}