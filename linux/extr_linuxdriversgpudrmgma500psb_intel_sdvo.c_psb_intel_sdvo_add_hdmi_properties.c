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
struct psb_intel_sdvo_connector {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
psb_intel_sdvo_add_hdmi_properties(struct psb_intel_sdvo_connector *connector)
{
	/* FIXME: We don't support HDMI at the moment
	struct drm_device *dev = connector->base.base.dev;

	intel_attach_force_audio_property(&connector->base.base);
	intel_attach_broadcast_rgb_property(&connector->base.base);
	*/
}