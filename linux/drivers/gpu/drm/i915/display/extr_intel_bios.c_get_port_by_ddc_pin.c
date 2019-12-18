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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {struct ddi_vbt_port_info* ddi_port_info; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;
struct ddi_vbt_port_info {scalar_t__ alternate_ddc_pin; scalar_t__ child; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int I915_MAX_PORTS ; 
 int PORT_A ; 
 int PORT_NONE ; 

__attribute__((used)) static enum port get_port_by_ddc_pin(struct drm_i915_private *i915, u8 ddc_pin)
{
	const struct ddi_vbt_port_info *info;
	enum port port;

	for (port = PORT_A; port < I915_MAX_PORTS; port++) {
		info = &i915->vbt.ddi_port_info[port];

		if (info->child && ddc_pin == info->alternate_ddc_pin)
			return port;
	}

	return PORT_NONE;
}