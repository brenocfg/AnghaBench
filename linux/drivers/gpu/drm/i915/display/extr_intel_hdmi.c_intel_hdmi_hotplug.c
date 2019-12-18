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
struct intel_encoder {int dummy; } ;
struct intel_connector {int dummy; } ;
typedef  enum intel_hotplug_state { ____Placeholder_intel_hotplug_state } intel_hotplug_state ;

/* Variables and functions */
 int INTEL_HOTPLUG_RETRY ; 
 int INTEL_HOTPLUG_UNCHANGED ; 
 int intel_encoder_hotplug (struct intel_encoder*,struct intel_connector*,int) ; 

__attribute__((used)) static enum intel_hotplug_state
intel_hdmi_hotplug(struct intel_encoder *encoder,
		   struct intel_connector *connector, bool irq_received)
{
	enum intel_hotplug_state state;

	state = intel_encoder_hotplug(encoder, connector, irq_received);

	/*
	 * On many platforms the HDMI live state signal is known to be
	 * unreliable, so we can't use it to detect if a sink is connected or
	 * not. Instead we detect if it's connected based on whether we can
	 * read the EDID or not. That in turn has a problem during disconnect,
	 * since the HPD interrupt may be raised before the DDC lines get
	 * disconnected (due to how the required length of DDC vs. HPD
	 * connector pins are specified) and so we'll still be able to get a
	 * valid EDID. To solve this schedule another detection cycle if this
	 * time around we didn't detect any change in the sink's connection
	 * status.
	 */
	if (state == INTEL_HOTPLUG_UNCHANGED && irq_received)
		state = INTEL_HOTPLUG_RETRY;

	return state;
}