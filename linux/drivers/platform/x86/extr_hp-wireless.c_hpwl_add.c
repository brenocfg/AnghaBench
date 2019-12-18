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
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int hp_wireless_input_setup () ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int hpwl_add(struct acpi_device *device)
{
	int err;

	err = hp_wireless_input_setup();
	if (err)
		pr_err("Failed to setup hp wireless hotkeys\n");

	return err;
}