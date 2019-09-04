#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int has_lpi; int power; } ;
struct TYPE_5__ {int count; TYPE_1__* lpi_states; } ;
struct acpi_processor {TYPE_3__ flags; TYPE_2__ power; int /*<<< orphan*/  handle; } ;
struct acpi_lpi_states_array {int dummy; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_4__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_PROCESSOR_CONTAINER_HID ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int /*<<< orphan*/  acpi_device_hid (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_get_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_has_method (int /*<<< orphan*/ ,char*) ; 
 int acpi_processor_evaluate_lpi (int /*<<< orphan*/ ,struct acpi_lpi_states_array*) ; 
 int flat_state_cnt ; 
 int /*<<< orphan*/  flatten_lpi_states (struct acpi_processor*,struct acpi_lpi_states_array*,struct acpi_lpi_states_array*) ; 
 int /*<<< orphan*/  osc_pc_lpi_support_confirmed ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_processor_get_lpi_info(struct acpi_processor *pr)
{
	int ret, i;
	acpi_status status;
	acpi_handle handle = pr->handle, pr_ahandle;
	struct acpi_device *d = NULL;
	struct acpi_lpi_states_array info[2], *tmp, *prev, *curr;

	if (!osc_pc_lpi_support_confirmed)
		return -EOPNOTSUPP;

	if (!acpi_has_method(handle, "_LPI"))
		return -EINVAL;

	flat_state_cnt = 0;
	prev = &info[0];
	curr = &info[1];
	handle = pr->handle;
	ret = acpi_processor_evaluate_lpi(handle, prev);
	if (ret)
		return ret;
	flatten_lpi_states(pr, prev, NULL);

	status = acpi_get_parent(handle, &pr_ahandle);
	while (ACPI_SUCCESS(status)) {
		acpi_bus_get_device(pr_ahandle, &d);
		handle = pr_ahandle;

		if (strcmp(acpi_device_hid(d), ACPI_PROCESSOR_CONTAINER_HID))
			break;

		/* can be optional ? */
		if (!acpi_has_method(handle, "_LPI"))
			break;

		ret = acpi_processor_evaluate_lpi(handle, curr);
		if (ret)
			break;

		/* flatten all the LPI states in this level of hierarchy */
		flatten_lpi_states(pr, curr, prev);

		tmp = prev, prev = curr, curr = tmp;

		status = acpi_get_parent(handle, &pr_ahandle);
	}

	pr->power.count = flat_state_cnt;
	/* reset the index after flattening */
	for (i = 0; i < pr->power.count; i++)
		pr->power.lpi_states[i].index = i;

	/* Tell driver that _LPI is supported. */
	pr->flags.has_lpi = 1;
	pr->flags.power = 1;

	return 0;
}