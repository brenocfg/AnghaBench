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
struct TYPE_4__ {TYPE_1__* ddi_port_info; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct child_device_config {scalar_t__ lspcon; } ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_3__ {struct child_device_config* child; } ;

/* Variables and functions */
 scalar_t__ HAS_LSPCON (struct drm_i915_private const*) ; 

bool
intel_bios_is_lspcon_present(const struct drm_i915_private *i915,
			     enum port port)
{
	const struct child_device_config *child =
		i915->vbt.ddi_port_info[port].child;

	return HAS_LSPCON(i915) && child && child->lspcon;
}