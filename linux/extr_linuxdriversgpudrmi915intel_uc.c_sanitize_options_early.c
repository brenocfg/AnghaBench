#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_uc_fw {int dummy; } ;
struct TYPE_5__ {struct intel_uc_fw fw; } ;
struct TYPE_4__ {struct intel_uc_fw fw; } ;
struct drm_i915_private {TYPE_2__ huc; TYPE_1__ guc; } ;
struct TYPE_6__ {scalar_t__ enable_guc; scalar_t__ guc_log_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DRM_WARN (char*,char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ GUC_LOG_LEVEL_IS_VERBOSE (scalar_t__) ; 
 scalar_t__ GUC_LOG_LEVEL_MAX ; 
 int /*<<< orphan*/  GUC_LOG_LEVEL_TO_VERBOSITY (scalar_t__) ; 
 int /*<<< orphan*/  HAS_GUC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HAS_HUC (struct drm_i915_private*) ; 
 scalar_t__ __get_default_guc_log_level (struct drm_i915_private*) ; 
 scalar_t__ __get_platform_enable_guc (struct drm_i915_private*) ; 
 TYPE_3__ i915_modparams ; 
 int /*<<< orphan*/  intel_uc_fw_is_selected (struct intel_uc_fw*) ; 
 scalar_t__ intel_uc_is_using_guc () ; 
 scalar_t__ intel_uc_is_using_guc_submission () ; 
 scalar_t__ intel_uc_is_using_huc () ; 
 int /*<<< orphan*/  yesno (scalar_t__) ; 

__attribute__((used)) static void sanitize_options_early(struct drm_i915_private *i915)
{
	struct intel_uc_fw *guc_fw = &i915->guc.fw;
	struct intel_uc_fw *huc_fw = &i915->huc.fw;

	/* A negative value means "use platform default" */
	if (i915_modparams.enable_guc < 0)
		i915_modparams.enable_guc = __get_platform_enable_guc(i915);

	DRM_DEBUG_DRIVER("enable_guc=%d (submission:%s huc:%s)\n",
			 i915_modparams.enable_guc,
			 yesno(intel_uc_is_using_guc_submission()),
			 yesno(intel_uc_is_using_huc()));

	/* Verify GuC firmware availability */
	if (intel_uc_is_using_guc() && !intel_uc_fw_is_selected(guc_fw)) {
		DRM_WARN("Incompatible option detected: %s=%d, %s!\n",
			 "enable_guc", i915_modparams.enable_guc,
			 !HAS_GUC(i915) ? "no GuC hardware" :
					  "no GuC firmware");
	}

	/* Verify HuC firmware availability */
	if (intel_uc_is_using_huc() && !intel_uc_fw_is_selected(huc_fw)) {
		DRM_WARN("Incompatible option detected: %s=%d, %s!\n",
			 "enable_guc", i915_modparams.enable_guc,
			 !HAS_HUC(i915) ? "no HuC hardware" :
					  "no HuC firmware");
	}

	/* A negative value means "use platform/config default" */
	if (i915_modparams.guc_log_level < 0)
		i915_modparams.guc_log_level =
			__get_default_guc_log_level(i915);

	if (i915_modparams.guc_log_level > 0 && !intel_uc_is_using_guc()) {
		DRM_WARN("Incompatible option detected: %s=%d, %s!\n",
			 "guc_log_level", i915_modparams.guc_log_level,
			 !HAS_GUC(i915) ? "no GuC hardware" :
					  "GuC not enabled");
		i915_modparams.guc_log_level = 0;
	}

	if (i915_modparams.guc_log_level > GUC_LOG_LEVEL_MAX) {
		DRM_WARN("Incompatible option detected: %s=%d, %s!\n",
			 "guc_log_level", i915_modparams.guc_log_level,
			 "verbosity too high");
		i915_modparams.guc_log_level = GUC_LOG_LEVEL_MAX;
	}

	DRM_DEBUG_DRIVER("guc_log_level=%d (enabled:%s, verbose:%s, verbosity:%d)\n",
			 i915_modparams.guc_log_level,
			 yesno(i915_modparams.guc_log_level),
			 yesno(GUC_LOG_LEVEL_IS_VERBOSE(i915_modparams.guc_log_level)),
			 GUC_LOG_LEVEL_TO_VERBOSITY(i915_modparams.guc_log_level));

	/* Make sure that sanitization was done */
	GEM_BUG_ON(i915_modparams.enable_guc < 0);
	GEM_BUG_ON(i915_modparams.guc_log_level < 0);
}