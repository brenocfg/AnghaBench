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
struct sdvo_device_mapping {int ddc_pin; scalar_t__ initialized; } ;
struct intel_sdvo {scalar_t__ port; int ddc_bus; } ;
struct TYPE_2__ {struct sdvo_device_mapping* sdvo_mappings; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;

/* Variables and functions */
 scalar_t__ PORT_B ; 
 int /*<<< orphan*/  intel_sdvo_guess_ddc_bus (struct intel_sdvo*) ; 

__attribute__((used)) static void
intel_sdvo_select_ddc_bus(struct drm_i915_private *dev_priv,
			  struct intel_sdvo *sdvo)
{
	struct sdvo_device_mapping *mapping;

	if (sdvo->port == PORT_B)
		mapping = &dev_priv->vbt.sdvo_mappings[0];
	else
		mapping = &dev_priv->vbt.sdvo_mappings[1];

	if (mapping->initialized)
		sdvo->ddc_bus = 1 << ((mapping->ddc_pin & 0xf0) >> 4);
	else
		intel_sdvo_guess_ddc_bus(sdvo);
}