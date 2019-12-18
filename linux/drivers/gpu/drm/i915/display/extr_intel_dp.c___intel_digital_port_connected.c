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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAS_GMCH (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_GM45 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int bdw_digital_port_connected (struct intel_encoder*) ; 
 int bxt_digital_port_connected (struct intel_encoder*) ; 
 int g4x_digital_port_connected (struct intel_encoder*) ; 
 int gm45_digital_port_connected (struct intel_encoder*) ; 
 int icl_digital_port_connected (struct intel_encoder*) ; 
 int ilk_digital_port_connected (struct intel_encoder*) ; 
 int ivb_digital_port_connected (struct intel_encoder*) ; 
 int snb_digital_port_connected (struct intel_encoder*) ; 
 int spt_digital_port_connected (struct intel_encoder*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __intel_digital_port_connected(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);

	if (HAS_GMCH(dev_priv)) {
		if (IS_GM45(dev_priv))
			return gm45_digital_port_connected(encoder);
		else
			return g4x_digital_port_connected(encoder);
	}

	if (INTEL_GEN(dev_priv) >= 11)
		return icl_digital_port_connected(encoder);
	else if (IS_GEN(dev_priv, 10) || IS_GEN9_BC(dev_priv))
		return spt_digital_port_connected(encoder);
	else if (IS_GEN9_LP(dev_priv))
		return bxt_digital_port_connected(encoder);
	else if (IS_GEN(dev_priv, 8))
		return bdw_digital_port_connected(encoder);
	else if (IS_GEN(dev_priv, 7))
		return ivb_digital_port_connected(encoder);
	else if (IS_GEN(dev_priv, 6))
		return snb_digital_port_connected(encoder);
	else if (IS_GEN(dev_priv, 5))
		return ilk_digital_port_connected(encoder);

	MISSING_CASE(INTEL_GEN(dev_priv));
	return false;
}