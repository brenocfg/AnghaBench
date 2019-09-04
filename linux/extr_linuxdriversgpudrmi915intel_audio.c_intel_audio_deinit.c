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
struct TYPE_2__ {int /*<<< orphan*/ * platdev; } ;
struct drm_i915_private {TYPE_1__ lpe_audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_audio_component_cleanup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_lpe_audio_teardown (struct drm_i915_private*) ; 

void intel_audio_deinit(struct drm_i915_private *dev_priv)
{
	if ((dev_priv)->lpe_audio.platdev != NULL)
		intel_lpe_audio_teardown(dev_priv);
	else
		i915_audio_component_cleanup(dev_priv);
}