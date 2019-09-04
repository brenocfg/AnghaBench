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
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct drm_i915_private {TYPE_1__ lpe_audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR_RATELIMITED (char*,int) ; 
 int /*<<< orphan*/  HAS_LPE_AUDIO (struct drm_i915_private*) ; 
 int generic_handle_irq (int /*<<< orphan*/ ) ; 

void intel_lpe_audio_irq_handler(struct drm_i915_private *dev_priv)
{
	int ret;

	if (!HAS_LPE_AUDIO(dev_priv))
		return;

	ret = generic_handle_irq(dev_priv->lpe_audio.irq);
	if (ret)
		DRM_ERROR_RATELIMITED("error handling LPE audio irq: %d\n",
				ret);
}