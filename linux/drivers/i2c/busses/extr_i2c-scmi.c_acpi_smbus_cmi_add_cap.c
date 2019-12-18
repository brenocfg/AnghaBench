#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ value; } ;
struct TYPE_4__ {union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_2__ integer; TYPE_1__ package; } ;
struct acpi_smbus_cmi {int cap_info; int cap_read; int cap_write; TYPE_3__* methods; struct acpi_handle* handle; } ;
struct acpi_handle {int dummy; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_6__ {int /*<<< orphan*/  mt_sbw; int /*<<< orphan*/  mt_sbr; int /*<<< orphan*/  mt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int EIO ; 
 int /*<<< orphan*/  acpi_evaluate_object (struct acpi_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_handle_debug (struct acpi_handle*,char*,...) ; 
 int /*<<< orphan*/  acpi_handle_err (struct acpi_handle*,char*,...) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_smbus_cmi_add_cap(struct acpi_smbus_cmi *smbus_cmi,
				  const char *name)
{
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	struct acpi_handle *handle = smbus_cmi->handle;
	union acpi_object *obj;
	acpi_status status;

	if (!strcmp(name, smbus_cmi->methods->mt_info)) {
		status = acpi_evaluate_object(smbus_cmi->handle,
					smbus_cmi->methods->mt_info,
					NULL, &buffer);
		if (ACPI_FAILURE(status)) {
			acpi_handle_err(handle, "Failed to evaluate %s: %i\n",
					smbus_cmi->methods->mt_info, status);
			return -EIO;
		}

		obj = buffer.pointer;
		if (obj && obj->type == ACPI_TYPE_PACKAGE)
			obj = obj->package.elements;
		else {
			acpi_handle_err(handle, "Invalid argument type\n");
			kfree(buffer.pointer);
			return -EIO;
		}

		if (obj->type != ACPI_TYPE_INTEGER) {
			acpi_handle_err(handle, "Invalid argument type\n");
			kfree(buffer.pointer);
			return -EIO;
		} else
			acpi_handle_debug(handle, "SMBus CMI Version %x\n",
					  (int)obj->integer.value);

		kfree(buffer.pointer);
		smbus_cmi->cap_info = 1;
	} else if (!strcmp(name, smbus_cmi->methods->mt_sbr))
		smbus_cmi->cap_read = 1;
	else if (!strcmp(name, smbus_cmi->methods->mt_sbw))
		smbus_cmi->cap_write = 1;
	else
		acpi_handle_debug(handle, "Unsupported CMI method: %s\n", name);

	return 0;
}