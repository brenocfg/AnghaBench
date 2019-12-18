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
struct TYPE_2__ {scalar_t__* pri_latency; scalar_t__* spr_latency; scalar_t__* cur_latency; } ;
struct drm_i915_private {TYPE_1__ wm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  intel_print_wm_latency (struct drm_i915_private*,char*,scalar_t__*) ; 

__attribute__((used)) static void snb_wm_lp3_irq_quirk(struct drm_i915_private *dev_priv)
{
	/*
	 * On some SNB machines (Thinkpad X220 Tablet at least)
	 * LP3 usage can cause vblank interrupts to be lost.
	 * The DEIIR bit will go high but it looks like the CPU
	 * never gets interrupted.
	 *
	 * It's not clear whether other interrupt source could
	 * be affected or if this is somehow limited to vblank
	 * interrupts only. To play it safe we disable LP3
	 * watermarks entirely.
	 */
	if (dev_priv->wm.pri_latency[3] == 0 &&
	    dev_priv->wm.spr_latency[3] == 0 &&
	    dev_priv->wm.cur_latency[3] == 0)
		return;

	dev_priv->wm.pri_latency[3] = 0;
	dev_priv->wm.spr_latency[3] = 0;
	dev_priv->wm.cur_latency[3] = 0;

	DRM_DEBUG_KMS("LP3 watermarks disabled due to potential for lost interrupts\n");
	intel_print_wm_latency(dev_priv, "Primary", dev_priv->wm.pri_latency);
	intel_print_wm_latency(dev_priv, "Sprite", dev_priv->wm.spr_latency);
	intel_print_wm_latency(dev_priv, "Cursor", dev_priv->wm.cur_latency);
}