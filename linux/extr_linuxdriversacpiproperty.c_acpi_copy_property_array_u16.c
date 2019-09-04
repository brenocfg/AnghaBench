#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ value; } ;
union acpi_object {scalar_t__ type; TYPE_1__ integer; } ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int EOVERFLOW ; 
 int EPROTO ; 
 scalar_t__ U16_MAX ; 

__attribute__((used)) static int acpi_copy_property_array_u16(const union acpi_object *items,
					u16 *val, size_t nval)
{
	int i;

	for (i = 0; i < nval; i++) {
		if (items[i].type != ACPI_TYPE_INTEGER)
			return -EPROTO;
		if (items[i].integer.value > U16_MAX)
			return -EOVERFLOW;

		val[i] = items[i].integer.value;
	}
	return 0;
}