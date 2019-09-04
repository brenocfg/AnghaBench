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
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 void* ACPI_TO_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoul (void*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void *acpi_db_get_pointer(void *target)
{
	void *obj_ptr;
	acpi_size address;

	address = strtoul(target, NULL, 16);
	obj_ptr = ACPI_TO_POINTER(address);
	return (obj_ptr);
}