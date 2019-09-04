#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int length; scalar_t__* pointer; } ;
struct TYPE_3__ {int value; } ;
union acpi_object {scalar_t__ type; TYPE_2__ buffer; TYPE_1__ integer; } ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  guid_t ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 union acpi_object* acpi_evaluate_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool acpi_check_dsm(acpi_handle handle, const guid_t *guid, u64 rev, u64 funcs)
{
	int i;
	u64 mask = 0;
	union acpi_object *obj;

	if (funcs == 0)
		return false;

	obj = acpi_evaluate_dsm(handle, guid, rev, 0, NULL);
	if (!obj)
		return false;

	/* For compatibility, old BIOSes may return an integer */
	if (obj->type == ACPI_TYPE_INTEGER)
		mask = obj->integer.value;
	else if (obj->type == ACPI_TYPE_BUFFER)
		for (i = 0; i < obj->buffer.length && i < 8; i++)
			mask |= (((u64)obj->buffer.pointer[i]) << (i * 8));
	ACPI_FREE(obj);

	/*
	 * Bit 0 indicates whether there's support for any functions other than
	 * function 0 for the specified GUID and revision.
	 */
	if ((mask & 0x1) && (mask & funcs) == funcs)
		return true;

	return false;
}