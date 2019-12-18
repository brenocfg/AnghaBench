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
 int intel_encoder_hotplug (struct intel_encoder*,struct intel_connector*,int) ; 
 int /*<<< orphan*/  intel_sdvo_enable_hotplug (struct intel_encoder*) ; 

__attribute__((used)) static enum intel_hotplug_state
intel_sdvo_hotplug(struct intel_encoder *encoder,
		   struct intel_connector *connector,
		   bool irq_received)
{
	intel_sdvo_enable_hotplug(encoder);

	return intel_encoder_hotplug(encoder, connector, irq_received);
}