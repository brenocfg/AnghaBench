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
struct intel_rps {int /*<<< orphan*/  pm_intrmsk_mbz; int /*<<< orphan*/  work; } ;
struct TYPE_9__ {void* hpd_irq_setup; } ;
struct TYPE_8__ {int /*<<< orphan*/  hpd_storm_threshold; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** remap_info; int /*<<< orphan*/  error_work; } ;
struct TYPE_6__ {struct intel_rps rps; } ;
struct drm_device {int max_vblank_count; int vblank_disable_immediate; TYPE_5__* driver; } ;
struct drm_i915_private {int display_irqs_enabled; TYPE_4__ display; TYPE_3__ hotplug; int /*<<< orphan*/  pm_rps_events; int /*<<< orphan*/  pm_guc_events; TYPE_2__ l3_parity; TYPE_1__ gt_pm; struct drm_device drm; } ;
struct TYPE_10__ {void* disable_vblank; void* enable_vblank; int /*<<< orphan*/  irq_handler; void* irq_uninstall; int /*<<< orphan*/  irq_postinstall; void* irq_preinstall; int /*<<< orphan*/  get_scanout_position; int /*<<< orphan*/  get_vblank_timestamp; int /*<<< orphan*/  get_vblank_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_PM_RPS_EVENTS ; 
 int /*<<< orphan*/  GEN6_PM_RP_UP_EI_EXPIRED ; 
 int /*<<< orphan*/  GEN8_PMINTR_DISABLE_REDIRECT_TO_GUC ; 
 int /*<<< orphan*/  GEN9_GUC_TO_HOST_INT_EVENT ; 
 scalar_t__ HAS_GUC_SCHED (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_CNP (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_KBP (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_SPT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HPD_STORM_DEFAULT_THRESHOLD ; 
 scalar_t__ I915_HAS_HOTPLUG (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN2 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN3 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int MAX_L3_SLICES ; 
 void* bxt_hpd_irq_setup ; 
 int /*<<< orphan*/  cherryview_irq_handler ; 
 int /*<<< orphan*/  cherryview_irq_postinstall ; 
 void* cherryview_irq_reset ; 
 int /*<<< orphan*/  drm_calc_vbltimestamp_from_scanoutpos ; 
 int /*<<< orphan*/  g4x_get_vblank_counter ; 
 void* gen11_hpd_irq_setup ; 
 int /*<<< orphan*/  gen11_irq_handler ; 
 int /*<<< orphan*/  gen11_irq_postinstall ; 
 void* gen11_irq_reset ; 
 int /*<<< orphan*/  gen6_pm_rps_work ; 
 void* gen8_disable_vblank ; 
 void* gen8_enable_vblank ; 
 int /*<<< orphan*/  gen8_irq_handler ; 
 int /*<<< orphan*/  gen8_irq_postinstall ; 
 void* gen8_irq_reset ; 
 void* i8xx_disable_vblank ; 
 void* i8xx_enable_vblank ; 
 int /*<<< orphan*/  i8xx_irq_handler ; 
 int /*<<< orphan*/  i8xx_irq_postinstall ; 
 void* i8xx_irq_reset ; 
 int /*<<< orphan*/  i915_get_crtc_scanoutpos ; 
 int /*<<< orphan*/  i915_get_vblank_counter ; 
 void* i915_hpd_irq_setup ; 
 int /*<<< orphan*/  i915_irq_handler ; 
 int /*<<< orphan*/  i915_irq_postinstall ; 
 void* i915_irq_reset ; 
 void* i965_disable_vblank ; 
 void* i965_enable_vblank ; 
 int /*<<< orphan*/  i965_irq_handler ; 
 int /*<<< orphan*/  i965_irq_postinstall ; 
 void* i965_irq_reset ; 
 void* ilk_hpd_irq_setup ; 
 int /*<<< orphan*/  intel_hpd_init_work (struct drm_i915_private*) ; 
 void* ironlake_disable_vblank ; 
 void* ironlake_enable_vblank ; 
 int /*<<< orphan*/  ironlake_irq_handler ; 
 int /*<<< orphan*/  ironlake_irq_postinstall ; 
 void* ironlake_irq_reset ; 
 int /*<<< orphan*/  ivybridge_parity_work ; 
 void* spt_hpd_irq_setup ; 
 int /*<<< orphan*/  valleyview_irq_handler ; 
 int /*<<< orphan*/  valleyview_irq_postinstall ; 
 void* valleyview_irq_reset ; 

void intel_irq_init(struct drm_i915_private *dev_priv)
{
	struct drm_device *dev = &dev_priv->drm;
	struct intel_rps *rps = &dev_priv->gt_pm.rps;
	int i;

	intel_hpd_init_work(dev_priv);

	INIT_WORK(&rps->work, gen6_pm_rps_work);

	INIT_WORK(&dev_priv->l3_parity.error_work, ivybridge_parity_work);
	for (i = 0; i < MAX_L3_SLICES; ++i)
		dev_priv->l3_parity.remap_info[i] = NULL;

	if (HAS_GUC_SCHED(dev_priv))
		dev_priv->pm_guc_events = GEN9_GUC_TO_HOST_INT_EVENT;

	/* Let's track the enabled rps events */
	if (IS_VALLEYVIEW(dev_priv))
		/* WaGsvRC0ResidencyMethod:vlv */
		dev_priv->pm_rps_events = GEN6_PM_RP_UP_EI_EXPIRED;
	else
		dev_priv->pm_rps_events = GEN6_PM_RPS_EVENTS;

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

	if (IS_GEN2(dev_priv)) {
		/* Gen2 doesn't have a hardware frame counter */
		dev->max_vblank_count = 0;
	} else if (IS_G4X(dev_priv) || INTEL_GEN(dev_priv) >= 5) {
		dev->max_vblank_count = 0xffffffff; /* full 32 bit counter */
		dev->driver->get_vblank_counter = g4x_get_vblank_counter;
	} else {
		dev->driver->get_vblank_counter = i915_get_vblank_counter;
		dev->max_vblank_count = 0xffffff; /* only 24 bits of frame count */
	}

	/*
	 * Opt out of the vblank disable timer on everything except gen2.
	 * Gen2 doesn't have a hardware frame counter and so depends on
	 * vblank interrupts to produce sane vblank seuquence numbers.
	 */
	if (!IS_GEN2(dev_priv))
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

	dev->driver->get_vblank_timestamp = drm_calc_vbltimestamp_from_scanoutpos;
	dev->driver->get_scanout_position = i915_get_crtc_scanoutpos;

	if (IS_CHERRYVIEW(dev_priv)) {
		dev->driver->irq_handler = cherryview_irq_handler;
		dev->driver->irq_preinstall = cherryview_irq_reset;
		dev->driver->irq_postinstall = cherryview_irq_postinstall;
		dev->driver->irq_uninstall = cherryview_irq_reset;
		dev->driver->enable_vblank = i965_enable_vblank;
		dev->driver->disable_vblank = i965_disable_vblank;
		dev_priv->display.hpd_irq_setup = i915_hpd_irq_setup;
	} else if (IS_VALLEYVIEW(dev_priv)) {
		dev->driver->irq_handler = valleyview_irq_handler;
		dev->driver->irq_preinstall = valleyview_irq_reset;
		dev->driver->irq_postinstall = valleyview_irq_postinstall;
		dev->driver->irq_uninstall = valleyview_irq_reset;
		dev->driver->enable_vblank = i965_enable_vblank;
		dev->driver->disable_vblank = i965_disable_vblank;
		dev_priv->display.hpd_irq_setup = i915_hpd_irq_setup;
	} else if (INTEL_GEN(dev_priv) >= 11) {
		dev->driver->irq_handler = gen11_irq_handler;
		dev->driver->irq_preinstall = gen11_irq_reset;
		dev->driver->irq_postinstall = gen11_irq_postinstall;
		dev->driver->irq_uninstall = gen11_irq_reset;
		dev->driver->enable_vblank = gen8_enable_vblank;
		dev->driver->disable_vblank = gen8_disable_vblank;
		dev_priv->display.hpd_irq_setup = gen11_hpd_irq_setup;
	} else if (INTEL_GEN(dev_priv) >= 8) {
		dev->driver->irq_handler = gen8_irq_handler;
		dev->driver->irq_preinstall = gen8_irq_reset;
		dev->driver->irq_postinstall = gen8_irq_postinstall;
		dev->driver->irq_uninstall = gen8_irq_reset;
		dev->driver->enable_vblank = gen8_enable_vblank;
		dev->driver->disable_vblank = gen8_disable_vblank;
		if (IS_GEN9_LP(dev_priv))
			dev_priv->display.hpd_irq_setup = bxt_hpd_irq_setup;
		else if (HAS_PCH_SPT(dev_priv) || HAS_PCH_KBP(dev_priv) ||
			 HAS_PCH_CNP(dev_priv))
			dev_priv->display.hpd_irq_setup = spt_hpd_irq_setup;
		else
			dev_priv->display.hpd_irq_setup = ilk_hpd_irq_setup;
	} else if (HAS_PCH_SPLIT(dev_priv)) {
		dev->driver->irq_handler = ironlake_irq_handler;
		dev->driver->irq_preinstall = ironlake_irq_reset;
		dev->driver->irq_postinstall = ironlake_irq_postinstall;
		dev->driver->irq_uninstall = ironlake_irq_reset;
		dev->driver->enable_vblank = ironlake_enable_vblank;
		dev->driver->disable_vblank = ironlake_disable_vblank;
		dev_priv->display.hpd_irq_setup = ilk_hpd_irq_setup;
	} else {
		if (IS_GEN2(dev_priv)) {
			dev->driver->irq_preinstall = i8xx_irq_reset;
			dev->driver->irq_postinstall = i8xx_irq_postinstall;
			dev->driver->irq_handler = i8xx_irq_handler;
			dev->driver->irq_uninstall = i8xx_irq_reset;
			dev->driver->enable_vblank = i8xx_enable_vblank;
			dev->driver->disable_vblank = i8xx_disable_vblank;
		} else if (IS_GEN3(dev_priv)) {
			dev->driver->irq_preinstall = i915_irq_reset;
			dev->driver->irq_postinstall = i915_irq_postinstall;
			dev->driver->irq_uninstall = i915_irq_reset;
			dev->driver->irq_handler = i915_irq_handler;
			dev->driver->enable_vblank = i8xx_enable_vblank;
			dev->driver->disable_vblank = i8xx_disable_vblank;
		} else {
			dev->driver->irq_preinstall = i965_irq_reset;
			dev->driver->irq_postinstall = i965_irq_postinstall;
			dev->driver->irq_uninstall = i965_irq_reset;
			dev->driver->irq_handler = i965_irq_handler;
			dev->driver->enable_vblank = i965_enable_vblank;
			dev->driver->disable_vblank = i965_disable_vblank;
		}
		if (I915_HAS_HOTPLUG(dev_priv))
			dev_priv->display.hpd_irq_setup = i915_hpd_irq_setup;
	}
}