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
struct TYPE_4__ {scalar_t__ port; TYPE_1__ base; } ;
struct intel_digital_port {int saved_port_bits; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int DDI_A_4_LANES ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ PORT_A ; 
 int /*<<< orphan*/  PORT_E ; 
 int /*<<< orphan*/  intel_bios_is_port_present (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_ddi_a_force_4_lanes(struct intel_digital_port *dport)
{
	struct drm_i915_private *dev_priv = to_i915(dport->base.base.dev);

	if (dport->base.port != PORT_A)
		return false;

	if (dport->saved_port_bits & DDI_A_4_LANES)
		return false;

	/* Broxton/Geminilake: Bspec says that DDI_A_4_LANES is the only
	 *                     supported configuration
	 */
	if (IS_GEN9_LP(dev_priv))
		return true;

	/* Cannonlake: Most of SKUs don't support DDI_E, and the only
	 *             one who does also have a full A/E split called
	 *             DDI_F what makes DDI_E useless. However for this
	 *             case let's trust VBT info.
	 */
	if (IS_CANNONLAKE(dev_priv) &&
	    !intel_bios_is_port_present(dev_priv, PORT_E))
		return true;

	return false;
}