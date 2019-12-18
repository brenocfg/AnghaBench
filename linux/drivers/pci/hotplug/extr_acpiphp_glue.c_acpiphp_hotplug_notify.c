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
struct acpiphp_context {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 struct acpiphp_context* acpiphp_grab_context (struct acpi_device*) ; 
 int /*<<< orphan*/  acpiphp_let_context_go (struct acpiphp_context*) ; 
 int /*<<< orphan*/  hotplug_event (int /*<<< orphan*/ ,struct acpiphp_context*) ; 

__attribute__((used)) static int acpiphp_hotplug_notify(struct acpi_device *adev, u32 type)
{
	struct acpiphp_context *context;

	context = acpiphp_grab_context(adev);
	if (!context)
		return -ENODATA;

	hotplug_event(type, context);
	acpiphp_let_context_go(context);
	return 0;
}