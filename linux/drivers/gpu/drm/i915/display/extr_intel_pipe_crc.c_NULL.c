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
typedef  int /*<<< orphan*/  intel_wakeref_t ;
typedef  enum intel_pipe_crc_source { ____Placeholder_intel_pipe_crc_source } intel_pipe_crc_source ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char const*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_PIPE_CRC_SOURCE_NONE ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPE_CRC_CTL (size_t) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int POWER_DOMAIN_PIPE (size_t) ; 
 scalar_t__ display_crc_ctl_parse_source (char const*,int*) ; 
 int get_new_crc_ctl_reg (struct drm_i915_private*,size_t,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_crtc_crc_setup_workarounds (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_display_power_get_if_enabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_intel_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  vlv_undo_pipe_scramble_reset (struct drm_i915_private*,size_t) ; 

int intel_crtc_set_crc_source(struct drm_crtc *crtc, const char *source_name)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->dev);
	struct intel_pipe_crc *pipe_crc = &dev_priv->pipe_crc[crtc->index];
	enum intel_display_power_domain power_domain;
	enum intel_pipe_crc_source source;
	intel_wakeref_t wakeref;
	u32 val = 0; /* shut up gcc */
	int ret = 0;
	bool enable;

	if (display_crc_ctl_parse_source(source_name, &source) < 0) {
		DRM_DEBUG_DRIVER("unknown source %s\n", source_name);
		return -EINVAL;
	}

	power_domain = POWER_DOMAIN_PIPE(crtc->index);
	wakeref = intel_display_power_get_if_enabled(dev_priv, power_domain);
	if (!wakeref) {
		DRM_DEBUG_KMS("Trying to capture CRC while pipe is off\n");
		return -EIO;
	}

	enable = source != INTEL_PIPE_CRC_SOURCE_NONE;
	if (enable)
		intel_crtc_crc_setup_workarounds(to_intel_crtc(crtc), true);

	ret = get_new_crc_ctl_reg(dev_priv, crtc->index, &source, &val);
	if (ret != 0)
		goto out;

	pipe_crc->source = source;
	I915_WRITE(PIPE_CRC_CTL(crtc->index), val);
	POSTING_READ(PIPE_CRC_CTL(crtc->index));

	if (!source) {
		if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
			vlv_undo_pipe_scramble_reset(dev_priv, crtc->index);
	}

	pipe_crc->skipped = 0;

out:
	if (!enable)
		intel_crtc_crc_setup_workarounds(to_intel_crtc(crtc), false);

	intel_display_power_put(dev_priv, power_domain, wakeref);

	return ret;
}