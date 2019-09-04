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
struct TYPE_4__ {int /*<<< orphan*/  pointer; scalar_t__ length; } ;
struct TYPE_3__ {int value; } ;
union acpi_object {TYPE_2__ buffer; TYPE_1__ integer; void* type; } ;
typedef  int /*<<< orphan*/  uint8_t ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 void* ACPI_TYPE_INTEGER ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_object_list*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_format_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nouveau_rom_call(acpi_handle rom_handle, uint8_t *bios,
			    int offset, int len)
{
	acpi_status status;
	union acpi_object rom_arg_elements[2], *obj;
	struct acpi_object_list rom_arg;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL};

	rom_arg.count = 2;
	rom_arg.pointer = &rom_arg_elements[0];

	rom_arg_elements[0].type = ACPI_TYPE_INTEGER;
	rom_arg_elements[0].integer.value = offset;

	rom_arg_elements[1].type = ACPI_TYPE_INTEGER;
	rom_arg_elements[1].integer.value = len;

	status = acpi_evaluate_object(rom_handle, NULL, &rom_arg, &buffer);
	if (ACPI_FAILURE(status)) {
		pr_info("failed to evaluate ROM got %s\n",
			acpi_format_exception(status));
		return -ENODEV;
	}
	obj = (union acpi_object *)buffer.pointer;
	len = min(len, (int)obj->buffer.length);
	memcpy(bios+offset, obj->buffer.pointer, len);
	kfree(buffer.pointer);
	return len;
}