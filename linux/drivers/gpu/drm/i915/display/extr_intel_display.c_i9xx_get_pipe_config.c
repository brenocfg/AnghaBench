#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int crtc_clock; } ;
struct TYPE_8__ {TYPE_3__ adjusted_mode; } ;
struct TYPE_6__ {int dpll_md; int dpll; void* fp1; void* fp0; } ;
struct intel_crtc_state {int cpu_transcoder; int pipe_bpp; int limited_color_range; int gamma_mode; int double_wide; int pixel_multiplier; int port_clock; TYPE_4__ base; TYPE_2__ dpll_hw_state; void* cgm_mode; int /*<<< orphan*/ * shared_dpll; int /*<<< orphan*/  output_format; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {size_t pipe; TYPE_1__ base; } ;
struct drm_i915_private {int* chv_dpll_md; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;

/* Variables and functions */
 int /*<<< orphan*/  CGM_PIPE_MODE (size_t) ; 
 int /*<<< orphan*/  DPLL (size_t) ; 
 int DPLL_LOCK_VLV ; 
 int /*<<< orphan*/  DPLL_MD (size_t) ; 
 int DPLL_MD_UDI_MULTIPLIER_MASK ; 
 int DPLL_MD_UDI_MULTIPLIER_SHIFT ; 
 int DPLL_PORTB_READY_MASK ; 
 int DPLL_PORTC_READY_MASK ; 
 int /*<<< orphan*/  FP0 (size_t) ; 
 int /*<<< orphan*/  FP1 (size_t) ; 
 void* I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_FORMAT_RGB ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G33 (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_I945G (struct drm_i915_private*) ; 
 scalar_t__ IS_I945GM (struct drm_i915_private*) ; 
 scalar_t__ IS_PINEVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPECONF (size_t) ; 
#define  PIPECONF_10BPC 130 
#define  PIPECONF_6BPC 129 
#define  PIPECONF_8BPC 128 
 int PIPECONF_BPC_MASK ; 
 int PIPECONF_COLOR_RANGE_SELECT ; 
 int PIPECONF_DOUBLE_WIDE ; 
 int PIPECONF_ENABLE ; 
 int PIPECONF_GAMMA_MODE_MASK_I9XX ; 
 int PIPECONF_GAMMA_MODE_SHIFT ; 
 size_t PIPE_A ; 
 int POWER_DOMAIN_PIPE (size_t) ; 
 int SDVO_MULTIPLIER_MASK ; 
 int SDVO_MULTIPLIER_SHIFT_HIRES ; 
 int /*<<< orphan*/  chv_crtc_clock_get (struct intel_crtc*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  i9xx_crtc_clock_get (struct intel_crtc*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  i9xx_get_pfit_config (struct intel_crtc*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  i9xx_get_pipe_color_config (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_color_get_config (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_display_power_get_if_enabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_get_pipe_src_size (struct intel_crtc*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_get_pipe_timings (struct intel_crtc*,struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_crtc_clock_get (struct intel_crtc*,struct intel_crtc_state*) ; 

__attribute__((used)) static bool i9xx_get_pipe_config(struct intel_crtc *crtc,
				 struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum intel_display_power_domain power_domain;
	intel_wakeref_t wakeref;
	u32 tmp;
	bool ret;

	power_domain = POWER_DOMAIN_PIPE(crtc->pipe);
	wakeref = intel_display_power_get_if_enabled(dev_priv, power_domain);
	if (!wakeref)
		return false;

	pipe_config->output_format = INTEL_OUTPUT_FORMAT_RGB;
	pipe_config->cpu_transcoder = (enum transcoder) crtc->pipe;
	pipe_config->shared_dpll = NULL;

	ret = false;

	tmp = I915_READ(PIPECONF(crtc->pipe));
	if (!(tmp & PIPECONF_ENABLE))
		goto out;

	if (IS_G4X(dev_priv) || IS_VALLEYVIEW(dev_priv) ||
	    IS_CHERRYVIEW(dev_priv)) {
		switch (tmp & PIPECONF_BPC_MASK) {
		case PIPECONF_6BPC:
			pipe_config->pipe_bpp = 18;
			break;
		case PIPECONF_8BPC:
			pipe_config->pipe_bpp = 24;
			break;
		case PIPECONF_10BPC:
			pipe_config->pipe_bpp = 30;
			break;
		default:
			break;
		}
	}

	if ((IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) &&
	    (tmp & PIPECONF_COLOR_RANGE_SELECT))
		pipe_config->limited_color_range = true;

	pipe_config->gamma_mode = (tmp & PIPECONF_GAMMA_MODE_MASK_I9XX) >>
		PIPECONF_GAMMA_MODE_SHIFT;

	if (IS_CHERRYVIEW(dev_priv))
		pipe_config->cgm_mode = I915_READ(CGM_PIPE_MODE(crtc->pipe));

	i9xx_get_pipe_color_config(pipe_config);
	intel_color_get_config(pipe_config);

	if (INTEL_GEN(dev_priv) < 4)
		pipe_config->double_wide = tmp & PIPECONF_DOUBLE_WIDE;

	intel_get_pipe_timings(crtc, pipe_config);
	intel_get_pipe_src_size(crtc, pipe_config);

	i9xx_get_pfit_config(crtc, pipe_config);

	if (INTEL_GEN(dev_priv) >= 4) {
		/* No way to read it out on pipes B and C */
		if (IS_CHERRYVIEW(dev_priv) && crtc->pipe != PIPE_A)
			tmp = dev_priv->chv_dpll_md[crtc->pipe];
		else
			tmp = I915_READ(DPLL_MD(crtc->pipe));
		pipe_config->pixel_multiplier =
			((tmp & DPLL_MD_UDI_MULTIPLIER_MASK)
			 >> DPLL_MD_UDI_MULTIPLIER_SHIFT) + 1;
		pipe_config->dpll_hw_state.dpll_md = tmp;
	} else if (IS_I945G(dev_priv) || IS_I945GM(dev_priv) ||
		   IS_G33(dev_priv) || IS_PINEVIEW(dev_priv)) {
		tmp = I915_READ(DPLL(crtc->pipe));
		pipe_config->pixel_multiplier =
			((tmp & SDVO_MULTIPLIER_MASK)
			 >> SDVO_MULTIPLIER_SHIFT_HIRES) + 1;
	} else {
		/* Note that on i915G/GM the pixel multiplier is in the sdvo
		 * port and will be fixed up in the encoder->get_config
		 * function. */
		pipe_config->pixel_multiplier = 1;
	}
	pipe_config->dpll_hw_state.dpll = I915_READ(DPLL(crtc->pipe));
	if (!IS_VALLEYVIEW(dev_priv) && !IS_CHERRYVIEW(dev_priv)) {
		pipe_config->dpll_hw_state.fp0 = I915_READ(FP0(crtc->pipe));
		pipe_config->dpll_hw_state.fp1 = I915_READ(FP1(crtc->pipe));
	} else {
		/* Mask out read-only status bits. */
		pipe_config->dpll_hw_state.dpll &= ~(DPLL_LOCK_VLV |
						     DPLL_PORTC_READY_MASK |
						     DPLL_PORTB_READY_MASK);
	}

	if (IS_CHERRYVIEW(dev_priv))
		chv_crtc_clock_get(crtc, pipe_config);
	else if (IS_VALLEYVIEW(dev_priv))
		vlv_crtc_clock_get(crtc, pipe_config);
	else
		i9xx_crtc_clock_get(crtc, pipe_config);

	/*
	 * Normally the dotclock is filled in by the encoder .get_config()
	 * but in case the pipe is enabled w/o any ports we need a sane
	 * default.
	 */
	pipe_config->base.adjusted_mode.crtc_clock =
		pipe_config->port_clock / pipe_config->pixel_multiplier;

	ret = true;

out:
	intel_display_power_put(dev_priv, power_domain, wakeref);

	return ret;
}