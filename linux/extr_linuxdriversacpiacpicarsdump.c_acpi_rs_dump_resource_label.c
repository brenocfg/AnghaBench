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
struct acpi_resource_label {char* string_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  acpi_rs_out_string (char*,char*) ; 

__attribute__((used)) static void
acpi_rs_dump_resource_label(char *title,
			    struct acpi_resource_label *resource_label)
{
	ACPI_FUNCTION_ENTRY();

	acpi_rs_out_string(title,
			   resource_label->string_ptr ?
			   resource_label->string_ptr : "[Not Specified]");
}