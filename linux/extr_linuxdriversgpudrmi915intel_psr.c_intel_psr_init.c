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
struct TYPE_7__ {int link_standby; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; int /*<<< orphan*/  sink_support; } ;
struct TYPE_5__ {int enable; int full_link; } ;
struct TYPE_6__ {TYPE_1__ psr; } ;
struct drm_i915_private {TYPE_3__ psr; TYPE_2__ vbt; int /*<<< orphan*/  psr_mmio_base; } ;
struct TYPE_8__ {int enable_psr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDW_EDP_PSR_BASE ; 
 int /*<<< orphan*/  HAS_PSR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HSW_EDP_PSR_BASE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 TYPE_4__ i915_modparams ; 
 int /*<<< orphan*/  intel_psr_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void intel_psr_init(struct drm_i915_private *dev_priv)
{
	if (!HAS_PSR(dev_priv))
		return;

	dev_priv->psr_mmio_base = IS_HASWELL(dev_priv) ?
		HSW_EDP_PSR_BASE : BDW_EDP_PSR_BASE;

	if (!dev_priv->psr.sink_support)
		return;

	if (i915_modparams.enable_psr == -1) {
		i915_modparams.enable_psr = dev_priv->vbt.psr.enable;

		/* Per platform default: all disabled. */
		i915_modparams.enable_psr = 0;
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