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
struct TYPE_3__ {TYPE_2__* parent; } ;
struct acpiphp_context {TYPE_1__ func; } ;
struct acpi_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ is_going_away; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_lock_hp_context () ; 
 int /*<<< orphan*/  acpi_unlock_hp_context () ; 
 struct acpiphp_context* acpiphp_get_context (struct acpi_device*) ; 
 int /*<<< orphan*/  acpiphp_put_context (struct acpiphp_context*) ; 
 int /*<<< orphan*/  get_bridge (TYPE_2__*) ; 

__attribute__((used)) static struct acpiphp_context *acpiphp_grab_context(struct acpi_device *adev)
{
	struct acpiphp_context *context;

	acpi_lock_hp_context();
	context = acpiphp_get_context(adev);
	if (!context || context->func.parent->is_going_away) {
		acpi_unlock_hp_context();
		return NULL;
	}
	get_bridge(context->func.parent);
	acpiphp_put_context(context);
	acpi_unlock_hp_context();
	return context;
}