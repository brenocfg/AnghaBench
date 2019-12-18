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
typedef  void* u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crtc_state {int cpu_transcoder; } ;
struct drm_i915_private {int dummy; } ;
typedef  int ssize_t ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int /*<<< orphan*/  HSW_TVIDEO_DIP_CTL (int) ; 
 void* I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsw_dip_data_reg (struct drm_i915_private*,int,unsigned int,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hsw_read_infoframe(struct intel_encoder *encoder,
			       const struct intel_crtc_state *crtc_state,
			       unsigned int type,
			       void *frame, ssize_t len)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	u32 val, *data = frame;
	int i;

	val = I915_READ(HSW_TVIDEO_DIP_CTL(cpu_transcoder));

	for (i = 0; i < len; i += 4)
		*data++ = I915_READ(hsw_dip_data_reg(dev_priv, cpu_transcoder,
						     type, i >> 2));
}