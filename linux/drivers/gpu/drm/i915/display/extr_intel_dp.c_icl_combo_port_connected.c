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
struct TYPE_2__ {int port; } ;
struct intel_digital_port {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDEISR ; 
 int SDE_DDI_HOTPLUG_ICP (int) ; 

__attribute__((used)) static bool icl_combo_port_connected(struct drm_i915_private *dev_priv,
				     struct intel_digital_port *intel_dig_port)
{
	enum port port = intel_dig_port->base.port;

	return I915_READ(SDEISR) & SDE_DDI_HOTPLUG_ICP(port);
}