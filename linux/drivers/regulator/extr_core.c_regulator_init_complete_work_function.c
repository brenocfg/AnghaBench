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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  class_for_each_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_class ; 
 int /*<<< orphan*/  regulator_late_cleanup ; 
 int /*<<< orphan*/  regulator_register_resolve_supply ; 

__attribute__((used)) static void regulator_init_complete_work_function(struct work_struct *work)
{
	/*
	 * Regulators may had failed to resolve their input supplies
	 * when were registered, either because the input supply was
	 * not registered yet or because its parent device was not
	 * bound yet. So attempt to resolve the input supplies for
	 * pending regulators before trying to disable unused ones.
	 */
	class_for_each_device(&regulator_class, NULL, NULL,
			      regulator_register_resolve_supply);

	/* If we have a full configuration then disable any regulators
	 * we have permission to change the status for and which are
	 * not in use or always_on.  This is effectively the default
	 * for DT and ACPI as they have full constraints.
	 */
	class_for_each_device(&regulator_class, NULL, NULL,
			      regulator_late_cleanup);
}