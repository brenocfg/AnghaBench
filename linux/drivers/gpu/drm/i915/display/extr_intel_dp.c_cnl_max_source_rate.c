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
typedef  scalar_t__ u32 ;
struct intel_dp {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int port; TYPE_1__ base; } ;
struct intel_digital_port {TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_PORT_COMP_DW3 ; 
 scalar_t__ I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CNL_WITH_PORT_F (struct drm_i915_private*) ; 
 int PORT_A ; 
 int PORT_D ; 
 scalar_t__ VOLTAGE_INFO_0_85V ; 
 scalar_t__ VOLTAGE_INFO_MASK ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cnl_max_source_rate(struct intel_dp *intel_dp)
{
	struct intel_digital_port *dig_port = dp_to_dig_port(intel_dp);
	struct drm_i915_private *dev_priv = to_i915(dig_port->base.base.dev);
	enum port port = dig_port->base.port;

	u32 voltage = I915_READ(CNL_PORT_COMP_DW3) & VOLTAGE_INFO_MASK;

	/* Low voltage SKUs are limited to max of 5.4G */
	if (voltage == VOLTAGE_INFO_0_85V)
		return 540000;

	/* For this SKU 8.1G is supported in all ports */
	if (IS_CNL_WITH_PORT_F(dev_priv))
		return 810000;

	/* For other SKUs, max rate on ports A and D is 5.4G */
	if (port == PORT_A || port == PORT_D)
		return 540000;

	return 810000;
}