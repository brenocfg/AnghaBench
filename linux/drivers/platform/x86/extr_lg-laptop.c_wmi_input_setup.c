#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_7__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_8__ {char* name; char* phys; TYPE_1__ id; } ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int /*<<< orphan*/  INIT_INPUT_WMI_0 ; 
 int /*<<< orphan*/  INIT_INPUT_WMI_2 ; 
 int /*<<< orphan*/  INIT_SPARSE_KEYMAP ; 
 int /*<<< orphan*/  WMI_EVENT_GUID0 ; 
 int /*<<< orphan*/  WMI_EVENT_GUID2 ; 
 int /*<<< orphan*/  inited ; 
 TYPE_2__* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (TYPE_2__*) ; 
 scalar_t__ input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ sparse_keymap_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* wmi_input_dev ; 
 int /*<<< orphan*/  wmi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  wmi_keymap ; 
 int /*<<< orphan*/  wmi_notify ; 

__attribute__((used)) static void wmi_input_setup(void)
{
	acpi_status status;

	wmi_input_dev = input_allocate_device();
	if (wmi_input_dev) {
		wmi_input_dev->name = "LG WMI hotkeys";
		wmi_input_dev->phys = "wmi/input0";
		wmi_input_dev->id.bustype = BUS_HOST;

		if (sparse_keymap_setup(wmi_input_dev, wmi_keymap, NULL) ||
		    input_register_device(wmi_input_dev)) {
			pr_info("Cannot initialize input device");
			input_free_device(wmi_input_dev);
			return;
		}

		inited |= INIT_SPARSE_KEYMAP;
		status = wmi_install_notify_handler(WMI_EVENT_GUID0, wmi_notify,
						    (void *)0);
		if (ACPI_SUCCESS(status))
			inited |= INIT_INPUT_WMI_0;

		status = wmi_install_notify_handler(WMI_EVENT_GUID2, wmi_notify,
						    (void *)2);
		if (ACPI_SUCCESS(status))
			inited |= INIT_INPUT_WMI_2;
	} else {
		pr_info("Cannot allocate input device");
	}
}