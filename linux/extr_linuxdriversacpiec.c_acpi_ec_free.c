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
struct acpi_ec {int dummy; } ;

/* Variables and functions */
 struct acpi_ec* boot_ec ; 
 struct acpi_ec* first_ec ; 
 int /*<<< orphan*/  kfree (struct acpi_ec*) ; 

__attribute__((used)) static void acpi_ec_free(struct acpi_ec *ec)
{
	if (first_ec == ec)
		first_ec = NULL;
	if (boot_ec == ec)
		boot_ec = NULL;
	kfree(ec);
}