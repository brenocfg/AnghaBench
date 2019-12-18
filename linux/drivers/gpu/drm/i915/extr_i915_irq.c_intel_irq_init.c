#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct intel_rps {int pm_intrmsk_mbz; int /*<<< orphan*/  work; } ;
struct TYPE_10__ {int /*<<< orphan*/  hpd_irq_setup; } ;
struct TYPE_9__ {int hpd_short_storm_enabled; int /*<<< orphan*/  hpd_storm_threshold; } ;
struct TYPE_8__ {int pm_guc_events; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** remap_info; int /*<<< orphan*/  error_work; } ;
struct TYPE_6__ {struct intel_rps rps; } ;
struct drm_device {int vblank_disable_immediate; } ;
struct drm_i915_private {int pm_rps_events; int display_irqs_enabled; TYPE_5__ display; TYPE_4__ hotplug; TYPE_3__ gt; TYPE_2__ l3_parity; TYPE_1__ gt_pm; struct drm_device drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_WARN_ON (int) ; 
 int GEN6_PM_RP_DOWN_THRESHOLD ; 
 int GEN6_PM_RP_DOWN_TIMEOUT ; 
 int GEN6_PM_RP_UP_EI_EXPIRED ; 
 int GEN6_PM_RP_UP_THRESHOLD ; 
 int GEN8_PMINTR_DISABLE_REDIRECT_TO_GUC ; 
 int GUC_INTR_GUC2HOST ; 
 int /*<<< orphan*/  HAS_DP_MST (struct drm_i915_private*) ; 
 scalar_t__ HAS_GMCH (struct drm_i915_private*) ; 
 scalar_t__ HAS_GT_UC (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_MCC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HPD_STORM_DEFAULT_THRESHOLD ; 
 scalar_t__ I915_HAS_HOTPLUG (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ INTEL_PCH_TYPE (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_I945GM (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int MAX_L3_SLICES ; 
 scalar_t__ PCH_SPT ; 
 int /*<<< orphan*/  bxt_hpd_irq_setup ; 
 int /*<<< orphan*/  gen11_hpd_irq_setup ; 
 int /*<<< orphan*/  gen6_pm_rps_work ; 
 int /*<<< orphan*/  i915_hpd_irq_setup ; 
 int /*<<< orphan*/  i945gm_vblank_work_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ilk_hpd_irq_setup ; 
 int /*<<< orphan*/  intel_hpd_init_work (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ivybridge_parity_work ; 
 int /*<<< orphan*/  mcc_hpd_irq_setup ; 
 int /*<<< orphan*/  spt_hpd_irq_setup ; 

void intel_irq_init(struct drm_i915_private *dev_priv)
{
	struct drm_device *dev = &dev_priv->drm;
	struct intel_rps *rps = &dev_priv->gt_pm.rps;
	int i;

	if (IS_I945GM(dev_priv))
		i945gm_vblank_work_init(dev_priv);

	intel_hpd_init_work(dev_priv);

	INIT_WORK(&rps->work, gen6_pm_rps_work);

	INIT_WORK(&dev_priv->l3_parity.error_work, ivybridge_parity_work);
	for (i = 0; i < MAX_L3_SLICES; ++i)
		dev_priv->l3_parity.remap_info[i] = NULL;

	/* pre-gen11 the guc irqs bits are in the upper 16 bits of the pm reg */
	if (HAS_GT_UC(dev_priv) && INTEL_GEN(dev_priv) < 11)
		dev_priv->gt.pm_guc_events = GUC_INTR_GUC2HOST << 16;

	/* Let's track the enabled rps events */
	if (IS_VALLEYVIEW(dev_priv))
		/* WaGsvRC0ResidencyMethod:vlv */
		dev_priv->pm_rps_events = GEN6_PM_RP_UP_EI_EXPIRED;
	else
		dev_priv->pm_rps_events = (GEN6_PM_RP_UP_THRESHOLD |
					   GEN6_PM_RP_DOWN_THRESHOLD |
					   GEN6_PM_RP_DOWN_TIMEOUT);

	/* We share the register with other engine */
	if (INTEL_GEN(dev_priv) > 9)
		GEM_WARN_ON(dev_priv->pm_rps_events & 0xffff0000);

	rps->pm_intrmsk_mbz = 0;

	/*
	 * SNB,IVB,HSW can while VLV,CHV may hard hang on looping batchbuffer
	 * if GEN6_PM_UP_EI_EXPIRED is masked.
	 *
	 * TODO: verify if this can be reproduced on VLV,CHV.
	 */
	if (INTEL_GEN(dev_priv) <= 7)
		rps->pm_intrmsk_mbz |= GEN6_PM_RP_UP_EI_EXPIRED;

	if (INTEL_GEN(dev_priv) >= 8)
		rps->pm_intrmsk_mbz |= GEN8_PMINTR_DISABLE_REDIRECT_TO_GUC;

	dev->vblank_disable_immediate = true;

	/* Most platforms treat the display irq block as an always-on
	 * power domain. vlv/chv can disable it at runtime and need
	 * special care to avoid writing any of the display block registers
	 * outside of the power domain. We defer setting up the display irqs
	 * in this case to the runtime pm.
	 */
	dev_priv->display_irqs_enabled = true;
	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		dev_priv->display_irqs_enabled = false;

	dev_priv->hotplug.hpd_storm_threshold = HPD_STORM_DEFAULT_THRESHOLD;
	/* If we have MST support, we want to avoid doing short HPD IRQ storm
	 * detection, as short HPD storms will occur as a natural part of
	 * sideband messaging with MST.
	 * On older platforms however, IRQ storms can occur with both long and
	 * short pulses, as seen on some G4x systems.
	 */
	dev_priv->hotplug.hpd_short_storm_enabled = !HAS_DP_MST(dev_priv);

	if (HAS_GMCH(dev_priv)) {
		if (I915_HAS_HOTPLUG(dev_priv))
			dev_priv->display.hpd_irq_setup = i915_hpd_irq_setup;
	} else {
		if (HAS_PCH_MCC(dev_priv))
			/* EHL doesn't need most of gen11_hpd_irq_setup */
			dev_priv->display.hpd_irq_setup = mcc_hpd_irq_setup;
		else if (INTEL_GEN(dev_priv) >= 11)
			dev_priv->display.hpd_irq_setup = gen11_hpd_irq_setup;
		else if (IS_GEN9_LP(dev_priv))
			dev_priv->display.hpd_irq_setup = bxt_hpd_irq_setup;
		else if (INTEL_PCH_TYPE(dev_priv) >= PCH_SPT)
			dev_priv->display.hpd_irq_setup = spt_hpd_irq_setup;
		else
			dev_priv->display.hpd_irq_setup = ilk_hpd_irq_setup;
	}
}