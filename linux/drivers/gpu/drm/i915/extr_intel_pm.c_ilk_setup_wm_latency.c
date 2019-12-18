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
struct TYPE_2__ {int /*<<< orphan*/  cur_latency; int /*<<< orphan*/  spr_latency; int /*<<< orphan*/  pri_latency; } ;
struct drm_i915_private {TYPE_1__ wm; } ;

/* Variables and functions */
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_fixup_cur_wm_latency (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_fixup_spr_wm_latency (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_print_wm_latency (struct drm_i915_private*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_read_wm_latency (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snb_wm_latency_quirk (struct drm_i915_private*) ; 
 int /*<<< orphan*/  snb_wm_lp3_irq_quirk (struct drm_i915_private*) ; 

__attribute__((used)) static void ilk_setup_wm_latency(struct drm_i915_private *dev_priv)
{
	intel_read_wm_latency(dev_priv, dev_priv->wm.pri_latency);

	memcpy(dev_priv->wm.spr_latency, dev_priv->wm.pri_latency,
	       sizeof(dev_priv->wm.pri_latency));
	memcpy(dev_priv->wm.cur_latency, dev_priv->wm.pri_latency,
	       sizeof(dev_priv->wm.pri_latency));

	intel_fixup_spr_wm_latency(dev_priv, dev_priv->wm.spr_latency);
	intel_fixup_cur_wm_latency(dev_priv, dev_priv->wm.cur_latency);

	intel_print_wm_latency(dev_priv, "Primary", dev_priv->wm.pri_latency);
	intel_print_wm_latency(dev_priv, "Sprite", dev_priv->wm.spr_latency);
	intel_print_wm_latency(dev_priv, "Cursor", dev_priv->wm.cur_latency);

	if (IS_GEN(dev_priv, 6)) {
		snb_wm_latency_quirk(dev_priv);
		snb_wm_lp3_irq_quirk(dev_priv);
	}
}