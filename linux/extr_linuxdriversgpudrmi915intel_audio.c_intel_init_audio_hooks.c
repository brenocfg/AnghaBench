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
struct TYPE_2__ {void* audio_codec_disable; void* audio_codec_enable; } ;
struct drm_i915_private {TYPE_1__ display; } ;

/* Variables and functions */
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 void* g4x_audio_codec_disable ; 
 void* g4x_audio_codec_enable ; 
 void* hsw_audio_codec_disable ; 
 void* hsw_audio_codec_enable ; 
 void* ilk_audio_codec_disable ; 
 void* ilk_audio_codec_enable ; 

void intel_init_audio_hooks(struct drm_i915_private *dev_priv)
{
	if (IS_G4X(dev_priv)) {
		dev_priv->display.audio_codec_enable = g4x_audio_codec_enable;
		dev_priv->display.audio_codec_disable = g4x_audio_codec_disable;
	} else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		dev_priv->display.audio_codec_enable = ilk_audio_codec_enable;
		dev_priv->display.audio_codec_disable = ilk_audio_codec_disable;
	} else if (IS_HASWELL(dev_priv) || INTEL_GEN(dev_priv) >= 8) {
		dev_priv->display.audio_codec_enable = hsw_audio_codec_enable;
		dev_priv->display.audio_codec_disable = hsw_audio_codec_disable;
	} else if (HAS_PCH_SPLIT(dev_priv)) {
		dev_priv->display.audio_codec_enable = ilk_audio_codec_enable;
		dev_priv->display.audio_codec_disable = ilk_audio_codec_disable;
	}
}