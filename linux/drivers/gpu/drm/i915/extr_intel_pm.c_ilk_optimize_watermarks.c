#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  optimal; } ;
struct TYPE_13__ {TYPE_3__ ilk; int /*<<< orphan*/  need_postvbl_update; } ;
struct TYPE_12__ {TYPE_7__* crtc; } ;
struct intel_crtc_state {TYPE_6__ wm; TYPE_5__ base; } ;
struct TYPE_8__ {int /*<<< orphan*/  ilk; } ;
struct TYPE_9__ {TYPE_1__ active; } ;
struct intel_crtc {TYPE_2__ wm; } ;
struct intel_atomic_state {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  wm_mutex; } ;
struct drm_i915_private {TYPE_4__ wm; } ;
struct TYPE_14__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ilk_program_watermarks (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (TYPE_7__*) ; 

__attribute__((used)) static void ilk_optimize_watermarks(struct intel_atomic_state *state,
				    struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(crtc_state->base.crtc->dev);
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);

	if (!crtc_state->wm.need_postvbl_update)
		return;

	mutex_lock(&dev_priv->wm.wm_mutex);
	crtc->wm.active.ilk = crtc_state->wm.ilk.optimal;
	ilk_program_watermarks(dev_priv);
	mutex_unlock(&dev_priv->wm.wm_mutex);
}