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
struct TYPE_2__ {int count; union acpi_object* elements; } ;
union acpi_object {int type; TYPE_1__ package; } ;

/* Variables and functions */
#define  ACPI_TYPE_INTEGER 129 
#define  ACPI_TYPE_LOCAL_REFERENCE 128 
 int EPROTO ; 

__attribute__((used)) static int acpi_gpio_package_count(const union acpi_object *obj)
{
	const union acpi_object *element = obj->package.elements;
	const union acpi_object *end = element + obj->package.count;
	unsigned int count = 0;

	while (element < end) {
		switch (element->type) {
		case ACPI_TYPE_LOCAL_REFERENCE:
			element += 3;
			/* Fallthrough */
		case ACPI_TYPE_INTEGER:
			element++;
			count++;
			break;

		default:
			return -EPROTO;
		}
	}

	return count;
}