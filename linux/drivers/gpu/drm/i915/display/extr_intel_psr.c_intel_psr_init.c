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
struct TYPE_7__ {int sink_not_reliable; int link_standby; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; int /*<<< orphan*/  sink_support; } ;
struct TYPE_5__ {int full_link; int /*<<< orphan*/  enable; } ;
struct TYPE_6__ {TYPE_1__ psr; } ;
struct drm_i915_private {TYPE_3__ psr; TYPE_2__ vbt; int /*<<< orphan*/  psr_mmio_base; } ;
struct TYPE_8__ {int enable_psr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDW_EDP_PSR_BASE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int EDP_PSR_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDP_PSR_IIR ; 
 int /*<<< orphan*/  HAS_PSR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HSW_EDP_PSR_BASE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  TRANSCODER_EDP ; 
 int /*<<< orphan*/  edp_psr_shift (int /*<<< orphan*/ ) ; 
 TYPE_4__ i915_modparams ; 
 int /*<<< orphan*/  intel_psr_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void intel_psr_init(struct drm_i915_private *dev_priv)
{
	u32 val;

	if (!HAS_PSR(dev_priv))
		return;

	dev_priv->psr_mmio_base = IS_HASWELL(dev_priv) ?
		HSW_EDP_PSR_BASE : BDW_EDP_PSR_BASE;

	if (!dev_priv->psr.sink_support)
		return;

	if (i915_modparams.enable_psr == -1)
		if (INTEL_GEN(dev_priv) < 9 || !dev_priv->vbt.psr.enable)
			i915_modparams.enable_psr = 0;

	/*
	 * If a PSR error happened and the driver is reloaded, the EDP_PSR_IIR
	 * will still keep the error set even after the reset done in the
	 * irq_preinstall and irq_uninstall hooks.
	 * And enabling in this situation cause the screen to freeze in the
	 * first time that PSR HW tries to activate so lets keep PSR disabled
	 * to avoid any rendering problems.
	 */
	val = I915_READ(EDP_PSR_IIR);
	val &= EDP_PSR_ERROR(edp_psr_shift(TRANSCODER_EDP));
	if (val) {
		DRM_DEBUG_KMS("PSR interruption error set\n");
		dev_priv->psr.sink_not_reliable = true;
	}

	/* Set link_standby x link_off defaults */
	if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		/* HSW and BDW require workarounds that we don't implement. */
		dev_priv->psr.link_standby = false;
	else
		/* For new platforms let's respect VBT back again */
		dev_priv->psr.link_standby = dev_priv->vbt.psr.full_link;

	INIT_WORK(&dev_priv->psr.work, intel_psr_work);
	mutex_init(&dev_priv->psr.lock);
}