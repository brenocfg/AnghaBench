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
struct opregion_acpi {scalar_t__ csts; } ;
struct notifier_block {int dummy; } ;
struct TYPE_2__ {struct opregion_acpi* acpi; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 TYPE_1__* system_opregion ; 

__attribute__((used)) static int psb_intel_opregion_video_event(struct notifier_block *nb,
					  unsigned long val, void *data)
{
	/* The only video events relevant to opregion are 0x80. These indicate
	   either a docking event, lid switch or display switch request. In
	   Linux, these are handled by the dock, button and video drivers.
	   We might want to fix the video driver to be opregion-aware in
	   future, but right now we just indicate to the firmware that the
	   request has been handled */

	struct opregion_acpi *acpi;

	if (!system_opregion)
		return NOTIFY_DONE;

	acpi = system_opregion->acpi;
	acpi->csts = 0;

	return NOTIFY_OK;
}