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
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_3__ {int length; int /*<<< orphan*/ * pointer; } ;
union acpi_object {scalar_t__ type; TYPE_2__ integer; TYPE_1__ buffer; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_BUFFER ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int EINVAL ; 
 size_t MIN (size_t,int) ; 
 union acpi_object* __call_snc_method (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int sony_nc_buffer_call(acpi_handle handle, char *name, u64 *value,
		void *buffer, size_t buflen)
{
	int ret = 0;
	size_t len;
	union acpi_object *object = __call_snc_method(handle, name, value);

	if (!object)
		return -EINVAL;

	if (object->type == ACPI_TYPE_BUFFER) {
		len = MIN(buflen, object->buffer.length);
		memcpy(buffer, object->buffer.pointer, len);

	} else if (object->type == ACPI_TYPE_INTEGER) {
		len = MIN(buflen, sizeof(object->integer.value));
		memcpy(buffer, &object->integer.value, len);

	} else {
		pr_warn("Invalid acpi_object: expected 0x%x got 0x%x\n",
				ACPI_TYPE_BUFFER, object->type);
		ret = -EINVAL;
	}

	kfree(object);
	return ret;
}