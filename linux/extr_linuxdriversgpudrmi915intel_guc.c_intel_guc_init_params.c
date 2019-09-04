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
typedef  int u32 ;
struct intel_guc {int dummy; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,int) ; 
 int /*<<< orphan*/  FORCEWAKE_BLITTER ; 
 size_t GUC_CTL_ARAT_HIGH ; 
 size_t GUC_CTL_ARAT_LOW ; 
 size_t GUC_CTL_CTXINFO ; 
 size_t GUC_CTL_DEBUG ; 
 size_t GUC_CTL_FEATURE ; 
 size_t GUC_CTL_LOG_PARAMS ; 
 int GUC_CTL_MAX_DWORDS ; 
 size_t GUC_CTL_WA ; 
 int GUC_CTL_WA_UK_BY_DRIVER ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SOFT_SCRATCH (int) ; 
 int guc_ctl_ctxinfo_flags (struct intel_guc*) ; 
 int guc_ctl_debug_flags (struct intel_guc*) ; 
 int guc_ctl_feature_flags (struct intel_guc*) ; 
 int guc_ctl_log_params_flags (struct intel_guc*) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void intel_guc_init_params(struct intel_guc *guc)
{
	struct drm_i915_private *dev_priv = guc_to_i915(guc);
	u32 params[GUC_CTL_MAX_DWORDS];
	int i;

	memset(params, 0, sizeof(params));

	/*
	 * GuC ARAT increment is 10 ns. GuC default scheduler quantum is one
	 * second. This ARAR is calculated by:
	 * Scheduler-Quantum-in-ns / ARAT-increment-in-ns = 1000000000 / 10
	 */
	params[GUC_CTL_ARAT_HIGH] = 0;
	params[GUC_CTL_ARAT_LOW] = 100000000;

	params[GUC_CTL_WA] |= GUC_CTL_WA_UK_BY_DRIVER;

	params[GUC_CTL_FEATURE] = guc_ctl_feature_flags(guc);
	params[GUC_CTL_LOG_PARAMS]  = guc_ctl_log_params_flags(guc);
	params[GUC_CTL_DEBUG] = guc_ctl_debug_flags(guc);
	params[GUC_CTL_CTXINFO] = guc_ctl_ctxinfo_flags(guc);

	for (i = 0; i < GUC_CTL_MAX_DWORDS; i++)
		DRM_DEBUG_DRIVER("param[%2d] = %#x\n", i, params[i]);

	/*
	 * All SOFT_SCRATCH registers are in FORCEWAKE_BLITTER domain and
	 * they are power context saved so it's ok to release forcewake
	 * when we are done here and take it again at xfer time.
	 */
	intel_uncore_forcewake_get(dev_priv, FORCEWAKE_BLITTER);

	I915_WRITE(SOFT_SCRATCH(0), 0);

	for (i = 0; i < GUC_CTL_MAX_DWORDS; i++)
		I915_WRITE(SOFT_SCRATCH(1 + i), params[i]);

	intel_uncore_forcewake_put(dev_priv, FORCEWAKE_BLITTER);
}