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
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crtc {int /*<<< orphan*/  config; } ;
struct i915_audio_component {int* aud_sample_rate; } ;
struct drm_i915_private {int /*<<< orphan*/  av_mutex; struct i915_audio_component* audio_component; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  HAS_DDI (struct drm_i915_private*) ; 
 struct intel_encoder* get_saved_enc (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  hsw_audio_config_update (struct intel_encoder*,int /*<<< orphan*/ ) ; 
 unsigned long i915_audio_component_get_power (struct device*) ; 
 int /*<<< orphan*/  i915_audio_component_put_power (struct device*,unsigned long) ; 
 struct drm_i915_private* kdev_to_i915 (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_name (int) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_audio_component_sync_audio_rate(struct device *kdev, int port,
						int pipe, int rate)
{
	struct drm_i915_private *dev_priv = kdev_to_i915(kdev);
	struct i915_audio_component *acomp = dev_priv->audio_component;
	struct intel_encoder *encoder;
	struct intel_crtc *crtc;
	unsigned long cookie;
	int err = 0;

	if (!HAS_DDI(dev_priv))
		return 0;

	cookie = i915_audio_component_get_power(kdev);
	mutex_lock(&dev_priv->av_mutex);

	/* 1. get the pipe */
	encoder = get_saved_enc(dev_priv, port, pipe);
	if (!encoder || !encoder->base.crtc) {
		DRM_DEBUG_KMS("Not valid for port %c\n", port_name(port));
		err = -ENODEV;
		goto unlock;
	}

	crtc = to_intel_crtc(encoder->base.crtc);

	/* port must be valid now, otherwise the pipe will be invalid */
	acomp->aud_sample_rate[port] = rate;

	hsw_audio_config_update(encoder, crtc->config);

 unlock:
	mutex_unlock(&dev_priv->av_mutex);
	i915_audio_component_put_power(kdev, cookie);
	return err;
}