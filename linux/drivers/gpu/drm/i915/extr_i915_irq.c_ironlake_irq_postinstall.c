#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_uncore {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  debug; } ;
struct drm_i915_private {int irq_mask; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  gt; TYPE_1__ psr; struct intel_uncore uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE ; 
 int DE_AUX_CHANNEL_A ; 
 int DE_AUX_CHANNEL_A_IVB ; 
 int DE_DP_A_HOTPLUG ; 
 int DE_DP_A_HOTPLUG_IVB ; 
 int DE_EDP_PSR_INT_HSW ; 
 int DE_ERR_INT_IVB ; 
 int DE_GSE ; 
 int DE_GSE_IVB ; 
 int DE_MASTER_IRQ_CONTROL ; 
 int DE_PCH_EVENT ; 
 int DE_PCH_EVENT_IVB ; 
 int DE_PCU_EVENT ; 
 int DE_PIPEA_CRC_DONE ; 
 int DE_PIPEA_FIFO_UNDERRUN ; 
 int DE_PIPEA_VBLANK ; 
 int DE_PIPEA_VBLANK_IVB ; 
 int DE_PIPEB_CRC_DONE ; 
 int DE_PIPEB_FIFO_UNDERRUN ; 
 int DE_PIPEB_VBLANK ; 
 int DE_PIPEB_VBLANK_IVB ; 
 int DE_PIPEC_VBLANK_IVB ; 
 int DE_POISON ; 
 int /*<<< orphan*/  EDP_PSR_IIR ; 
 int /*<<< orphan*/  GEN3_IRQ_INIT (struct intel_uncore*,int /*<<< orphan*/ ,int,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_IRONLAKE_M (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen3_assert_iir_is_zero (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen5_gt_irq_postinstall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibx_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ibx_irq_pre_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ilk_enable_display_irq (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  ilk_hpd_detection_setup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_psr_irq_control (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ironlake_irq_postinstall(struct drm_i915_private *dev_priv)
{
	struct intel_uncore *uncore = &dev_priv->uncore;
	u32 display_mask, extra_mask;

	if (INTEL_GEN(dev_priv) >= 7) {
		display_mask = (DE_MASTER_IRQ_CONTROL | DE_GSE_IVB |
				DE_PCH_EVENT_IVB | DE_AUX_CHANNEL_A_IVB);
		extra_mask = (DE_PIPEC_VBLANK_IVB | DE_PIPEB_VBLANK_IVB |
			      DE_PIPEA_VBLANK_IVB | DE_ERR_INT_IVB |
			      DE_DP_A_HOTPLUG_IVB);
	} else {
		display_mask = (DE_MASTER_IRQ_CONTROL | DE_GSE | DE_PCH_EVENT |
				DE_AUX_CHANNEL_A | DE_PIPEB_CRC_DONE |
				DE_PIPEA_CRC_DONE | DE_POISON);
		extra_mask = (DE_PIPEA_VBLANK | DE_PIPEB_VBLANK | DE_PCU_EVENT |
			      DE_PIPEB_FIFO_UNDERRUN | DE_PIPEA_FIFO_UNDERRUN |
			      DE_DP_A_HOTPLUG);
	}

	if (IS_HASWELL(dev_priv)) {
		gen3_assert_iir_is_zero(uncore, EDP_PSR_IIR);
		intel_psr_irq_control(dev_priv, dev_priv->psr.debug);
		display_mask |= DE_EDP_PSR_INT_HSW;
	}

	dev_priv->irq_mask = ~display_mask;

	ibx_irq_pre_postinstall(dev_priv);

	GEN3_IRQ_INIT(uncore, DE, dev_priv->irq_mask,
		      display_mask | extra_mask);

	gen5_gt_irq_postinstall(&dev_priv->gt);

	ilk_hpd_detection_setup(dev_priv);

	ibx_irq_postinstall(dev_priv);

	if (IS_IRONLAKE_M(dev_priv)) {
		/* Enable PCU event interrupts
		 *
		 * spinlocking not required here for correctness since interrupt
		 * setup is guaranteed to run in single-threaded context. But we
		 * need it to make the assert_spin_locked happy. */
		spin_lock_irq(&dev_priv->irq_lock);
		ilk_enable_display_irq(dev_priv, DE_PCU_EVENT);
		spin_unlock_irq(&dev_priv->irq_lock);
	}
}