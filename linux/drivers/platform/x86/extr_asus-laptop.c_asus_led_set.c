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
struct asus_laptop {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_GLED ; 
 int /*<<< orphan*/  METHOD_MLED ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int write_acpi_int (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int asus_led_set(struct asus_laptop *asus, const char *method,
			 int value)
{
	if (!strcmp(method, METHOD_MLED))
		value = !value;
	else if (!strcmp(method, METHOD_GLED))
		value = !value + 1;
	else
		value = !!value;

	return write_acpi_int(asus->handle, method, value);
}