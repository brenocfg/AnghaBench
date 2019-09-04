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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
union acpi_object {scalar_t__ type; TYPE_1__ integer; } ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int EINVAL ; 

__attribute__((used)) static int obj_get_integer(union acpi_object *obj, u32 *value)
{
	if (obj->type != ACPI_TYPE_INTEGER)
		return -EINVAL;

	*value = obj->integer.value;
	return 0;
}