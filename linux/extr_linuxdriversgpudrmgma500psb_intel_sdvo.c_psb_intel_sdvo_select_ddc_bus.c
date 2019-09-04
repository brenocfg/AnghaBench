#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sdvo_device_mapping {int ddc_pin; scalar_t__ initialized; } ;
struct psb_intel_sdvo {int ddc_bus; } ;
struct drm_psb_private {struct sdvo_device_mapping* sdvo_mappings; } ;

/* Variables and functions */
 scalar_t__ IS_SDVOB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psb_intel_sdvo_guess_ddc_bus (struct psb_intel_sdvo*) ; 

__attribute__((used)) static void
psb_intel_sdvo_select_ddc_bus(struct drm_psb_private *dev_priv,
			  struct psb_intel_sdvo *sdvo, u32 reg)
{
	struct sdvo_device_mapping *mapping;

	if (IS_SDVOB(reg))
		mapping = &(dev_priv->sdvo_mappings[0]);
	else
		mapping = &(dev_priv->sdvo_mappings[1]);

	if (mapping->initialized)
		sdvo->ddc_bus = 1 << ((mapping->ddc_pin & 0xf0) >> 4);
	else
		psb_intel_sdvo_guess_ddc_bus(sdvo);
}