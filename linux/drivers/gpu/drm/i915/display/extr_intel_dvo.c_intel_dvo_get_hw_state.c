#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dvo_reg; } ;
struct intel_dvo {TYPE_2__ dev; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int DVO_ENABLE ; 
 int DVO_PIPE_SEL_MASK ; 
 int DVO_PIPE_SEL_SHIFT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 struct intel_dvo* enc_to_dvo (struct intel_encoder*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_dvo_get_hw_state(struct intel_encoder *encoder,
				   enum pipe *pipe)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_dvo *intel_dvo = enc_to_dvo(encoder);
	u32 tmp;

	tmp = I915_READ(intel_dvo->dev.dvo_reg);

	*pipe = (tmp & DVO_PIPE_SEL_MASK) >> DVO_PIPE_SEL_SHIFT;

	return tmp & DVO_ENABLE;
}