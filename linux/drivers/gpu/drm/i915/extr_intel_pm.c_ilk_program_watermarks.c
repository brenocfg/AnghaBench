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
struct intel_wm_config {int num_pipes_active; scalar_t__ sprites_enabled; } ;
struct intel_pipe_wm {int dummy; } ;
struct ilk_wm_values {int dummy; } ;
struct ilk_wm_maximums {int dummy; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum intel_ddb_partitioning { ____Placeholder_intel_ddb_partitioning } intel_ddb_partitioning ;

/* Variables and functions */
 int INTEL_DDB_PART_1_2 ; 
 int INTEL_DDB_PART_5_6 ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ilk_compute_wm_config (struct drm_i915_private*,struct intel_wm_config*) ; 
 int /*<<< orphan*/  ilk_compute_wm_maximums (struct drm_i915_private*,int,struct intel_wm_config*,int,struct ilk_wm_maximums*) ; 
 int /*<<< orphan*/  ilk_compute_wm_results (struct drm_i915_private*,struct intel_pipe_wm*,int,struct ilk_wm_values*) ; 
 struct intel_pipe_wm* ilk_find_best_result (struct drm_i915_private*,struct intel_pipe_wm*,struct intel_pipe_wm*) ; 
 int /*<<< orphan*/  ilk_wm_merge (struct drm_i915_private*,struct intel_wm_config*,struct ilk_wm_maximums*,struct intel_pipe_wm*) ; 
 int /*<<< orphan*/  ilk_write_wm_values (struct drm_i915_private*,struct ilk_wm_values*) ; 

__attribute__((used)) static void ilk_program_watermarks(struct drm_i915_private *dev_priv)
{
	struct intel_pipe_wm lp_wm_1_2 = {}, lp_wm_5_6 = {}, *best_lp_wm;
	struct ilk_wm_maximums max;
	struct intel_wm_config config = {};
	struct ilk_wm_values results = {};
	enum intel_ddb_partitioning partitioning;

	ilk_compute_wm_config(dev_priv, &config);

	ilk_compute_wm_maximums(dev_priv, 1, &config, INTEL_DDB_PART_1_2, &max);
	ilk_wm_merge(dev_priv, &config, &max, &lp_wm_1_2);

	/* 5/6 split only in single pipe config on IVB+ */
	if (INTEL_GEN(dev_priv) >= 7 &&
	    config.num_pipes_active == 1 && config.sprites_enabled) {
		ilk_compute_wm_maximums(dev_priv, 1, &config, INTEL_DDB_PART_5_6, &max);
		ilk_wm_merge(dev_priv, &config, &max, &lp_wm_5_6);

		best_lp_wm = ilk_find_best_result(dev_priv, &lp_wm_1_2, &lp_wm_5_6);
	} else {
		best_lp_wm = &lp_wm_1_2;
	}

	partitioning = (best_lp_wm == &lp_wm_1_2) ?
		       INTEL_DDB_PART_1_2 : INTEL_DDB_PART_5_6;

	ilk_compute_wm_results(dev_priv, best_lp_wm, partitioning, &results);

	ilk_write_wm_values(dev_priv, &results);
}