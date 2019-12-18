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
struct intel_guc {int /*<<< orphan*/ * params; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,int /*<<< orphan*/ ) ; 
 size_t GUC_CTL_ADS ; 
 size_t GUC_CTL_CTXINFO ; 
 size_t GUC_CTL_DEBUG ; 
 size_t GUC_CTL_FEATURE ; 
 size_t GUC_CTL_LOG_PARAMS ; 
 int GUC_CTL_MAX_DWORDS ; 
 int /*<<< orphan*/  guc_ctl_ads_flags (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_ctl_ctxinfo_flags (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_ctl_debug_flags (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_ctl_feature_flags (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_ctl_log_params_flags (struct intel_guc*) ; 

__attribute__((used)) static void guc_init_params(struct intel_guc *guc)
{
	u32 *params = guc->params;
	int i;

	BUILD_BUG_ON(sizeof(guc->params) != GUC_CTL_MAX_DWORDS * sizeof(u32));

	params[GUC_CTL_CTXINFO] = guc_ctl_ctxinfo_flags(guc);
	params[GUC_CTL_LOG_PARAMS] = guc_ctl_log_params_flags(guc);
	params[GUC_CTL_FEATURE] = guc_ctl_feature_flags(guc);
	params[GUC_CTL_DEBUG] = guc_ctl_debug_flags(guc);
	params[GUC_CTL_ADS] = guc_ctl_ads_flags(guc);

	for (i = 0; i < GUC_CTL_MAX_DWORDS; i++)
		DRM_DEBUG_DRIVER("param[%2d] = %#x\n", i, params[i]);
}