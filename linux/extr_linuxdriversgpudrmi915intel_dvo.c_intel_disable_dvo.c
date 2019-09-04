#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct TYPE_6__ {TYPE_2__* dev_ops; int /*<<< orphan*/  dvo_reg; } ;
struct intel_dvo {TYPE_3__ dev; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* dpms ) (TYPE_3__*,int) ;} ;

/* Variables and functions */
 int DVO_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 struct intel_dvo* enc_to_dvo (struct intel_encoder*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_disable_dvo(struct intel_encoder *encoder,
			      const struct intel_crtc_state *old_crtc_state,
			      const struct drm_connector_state *old_conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_dvo *intel_dvo = enc_to_dvo(encoder);
	i915_reg_t dvo_reg = intel_dvo->dev.dvo_reg;
	u32 temp = I915_READ(dvo_reg);

	intel_dvo->dev.dev_ops->dpms(&intel_dvo->dev, false);
	I915_WRITE(dvo_reg, temp & ~DVO_ENABLE);
	I915_READ(dvo_reg);
}