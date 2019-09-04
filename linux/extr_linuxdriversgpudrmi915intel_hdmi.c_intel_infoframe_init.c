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
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct intel_digital_port {int /*<<< orphan*/  infoframe_enabled; int /*<<< orphan*/  set_infoframes; int /*<<< orphan*/  write_infoframe; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAS_DDI (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cpt_infoframe_enabled ; 
 int /*<<< orphan*/  cpt_set_infoframes ; 
 int /*<<< orphan*/  cpt_write_infoframe ; 
 int /*<<< orphan*/  g4x_infoframe_enabled ; 
 int /*<<< orphan*/  g4x_set_infoframes ; 
 int /*<<< orphan*/  g4x_write_infoframe ; 
 int /*<<< orphan*/  hsw_infoframe_enabled ; 
 int /*<<< orphan*/  hsw_set_infoframes ; 
 int /*<<< orphan*/  hsw_write_infoframe ; 
 int /*<<< orphan*/  ibx_infoframe_enabled ; 
 int /*<<< orphan*/  ibx_set_infoframes ; 
 int /*<<< orphan*/  ibx_write_infoframe ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_infoframe_enabled ; 
 int /*<<< orphan*/  vlv_set_infoframes ; 
 int /*<<< orphan*/  vlv_write_infoframe ; 

void intel_infoframe_init(struct intel_digital_port *intel_dig_port)
{
	struct drm_i915_private *dev_priv =
		to_i915(intel_dig_port->base.base.dev);

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		intel_dig_port->write_infoframe = vlv_write_infoframe;
		intel_dig_port->set_infoframes = vlv_set_infoframes;
		intel_dig_port->infoframe_enabled = vlv_infoframe_enabled;
	} else if (IS_G4X(dev_priv)) {
		intel_dig_port->write_infoframe = g4x_write_infoframe;
		intel_dig_port->set_infoframes = g4x_set_infoframes;
		intel_dig_port->infoframe_enabled = g4x_infoframe_enabled;
	} else if (HAS_DDI(dev_priv)) {
		intel_dig_port->write_infoframe = hsw_write_infoframe;
		intel_dig_port->set_infoframes = hsw_set_infoframes;
		intel_dig_port->infoframe_enabled = hsw_infoframe_enabled;
	} else if (HAS_PCH_IBX(dev_priv)) {
		intel_dig_port->write_infoframe = ibx_write_infoframe;
		intel_dig_port->set_infoframes = ibx_set_infoframes;
		intel_dig_port->infoframe_enabled = ibx_infoframe_enabled;
	} else {
		intel_dig_port->write_infoframe = cpt_write_infoframe;
		intel_dig_port->set_infoframes = cpt_set_infoframes;
		intel_dig_port->infoframe_enabled = cpt_infoframe_enabled;
	}
}