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
struct intel_pipe_crc {int source; scalar_t__ skipped; } ;
struct drm_i915_private {struct intel_pipe_crc* pipe_crc; } ;
struct drm_crtc {size_t index; int /*<<< orphan*/  dev; } ;
typedef  enum intel_pipe_crc_source { ____Placeholder_intel_pipe_crc_source } intel_pipe_crc_source ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char const*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 size_t PIPE_A ; 
 int /*<<< orphan*/  PIPE_CRC_CTL (size_t) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int POWER_DOMAIN_PIPE (size_t) ; 
 scalar_t__ display_crc_ctl_parse_source (char const*,int*) ; 
 int /*<<< orphan*/  g4x_undo_pipe_scramble_reset (struct drm_i915_private*,size_t) ; 
 int get_new_crc_ctl_reg (struct drm_i915_private*,size_t,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hsw_pipe_A_crc_wa (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_display_power_get_if_enabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_undo_pipe_scramble_reset (struct drm_i915_private*,size_t) ; 

int intel_crtc_set_crc_source(struct drm_crtc *crtc, const char *source_name,
			      size_t *values_cnt)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->dev);
	struct intel_pipe_crc *pipe_crc = &dev_priv->pipe_crc[crtc->index];
	enum intel_display_power_domain power_domain;
	enum intel_pipe_crc_source source;
	u32 val = 0; /* shut up gcc */
	int ret = 0;

	if (display_crc_ctl_parse_source(source_name, &source) < 0) {
		DRM_DEBUG_DRIVER("unknown source %s\n", source_name);
		return -EINVAL;
	}

	power_domain = POWER_DOMAIN_PIPE(crtc->index);
	if (!intel_display_power_get_if_enabled(dev_priv, power_domain)) {
		DRM_DEBUG_KMS("Trying to capture CRC while pipe is off\n");
		return -EIO;
	}

	ret = get_new_crc_ctl_reg(dev_priv, crtc->index, &source, &val, true);
	if (ret != 0)
		goto out;

	pipe_crc->source = source;
	I915_WRITE(PIPE_CRC_CTL(crtc->index), val);
	POSTING_READ(PIPE_CRC_CTL(crtc->index));

	if (!source) {
		if (IS_G4X(dev_priv))
			g4x_undo_pipe_scramble_reset(dev_priv, crtc->index);
		else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
			vlv_undo_pipe_scramble_reset(dev_priv, crtc->index);
		else if ((IS_HASWELL(dev_priv) ||
			  IS_BROADWELL(dev_priv)) && crtc->index == PIPE_A)
			hsw_pipe_A_crc_wa(dev_priv, false);
	}

	pipe_crc->skipped = 0;
	*values_cnt = 5;

out:
	intel_display_power_put(dev_priv, power_domain);

	return ret;
}