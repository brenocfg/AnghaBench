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
typedef  int u8 ;
struct sdvo_device_mapping {int slave_addr; } ;
struct intel_sdvo {scalar_t__ port; } ;
struct TYPE_2__ {struct sdvo_device_mapping* sdvo_mappings; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;

/* Variables and functions */
 scalar_t__ PORT_B ; 

__attribute__((used)) static u8
intel_sdvo_get_slave_addr(struct drm_i915_private *dev_priv,
			  struct intel_sdvo *sdvo)
{
	struct sdvo_device_mapping *my_mapping, *other_mapping;

	if (sdvo->port == PORT_B) {
		my_mapping = &dev_priv->vbt.sdvo_mappings[0];
		other_mapping = &dev_priv->vbt.sdvo_mappings[1];
	} else {
		my_mapping = &dev_priv->vbt.sdvo_mappings[1];
		other_mapping = &dev_priv->vbt.sdvo_mappings[0];
	}

	/* If the BIOS described our SDVO device, take advantage of it. */
	if (my_mapping->slave_addr)
		return my_mapping->slave_addr;

	/*
	 * If the BIOS only described a different SDVO device, use the
	 * address that it isn't using.
	 */
	if (other_mapping->slave_addr) {
		if (other_mapping->slave_addr == 0x70)
			return 0x72;
		else
			return 0x70;
	}

	/*
	 * No SDVO device info is found for another DVO port,
	 * so use mapping assumption we had before BIOS parsing.
	 */
	if (sdvo->port == PORT_B)
		return 0x70;
	else
		return 0x72;
}