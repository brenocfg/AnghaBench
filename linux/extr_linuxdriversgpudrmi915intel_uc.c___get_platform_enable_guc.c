#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_uc_fw {int dummy; } ;
struct TYPE_4__ {struct intel_uc_fw fw; } ;
struct TYPE_3__ {struct intel_uc_fw fw; } ;
struct drm_i915_private {TYPE_2__ huc; TYPE_1__ guc; } ;

/* Variables and functions */
 int ENABLE_GUC_LOAD_HUC ; 
 int ENABLE_GUC_SUBMISSION ; 
 scalar_t__ intel_uc_fw_is_selected (struct intel_uc_fw*) ; 

__attribute__((used)) static int __get_platform_enable_guc(struct drm_i915_private *i915)
{
	struct intel_uc_fw *guc_fw = &i915->guc.fw;
	struct intel_uc_fw *huc_fw = &i915->huc.fw;
	int enable_guc = 0;

	/* Default is to enable GuC/HuC if we know their firmwares */
	if (intel_uc_fw_is_selected(guc_fw))
		enable_guc |= ENABLE_GUC_SUBMISSION;
	if (intel_uc_fw_is_selected(huc_fw))
		enable_guc |= ENABLE_GUC_LOAD_HUC;

	/* Any platform specific fine-tuning can be done here */

	return enable_guc;
}