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
struct TYPE_4__ {scalar_t__ handle; } ;
struct TYPE_3__ {scalar_t__ count; union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_2__ reference; TYPE_1__ package; } ;
typedef  size_t u32 ;
struct acpi_object_list {int dummy; } ;
struct acpi_handle_list {size_t count; scalar_t__* handles; } ;
struct acpi_buffer {scalar_t__ length; union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_string ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_MAX_HANDLES ; 
 scalar_t__ ACPI_TYPE_LOCAL_REFERENCE ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AE_BAD_DATA ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_NULL_ENTRY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_object_list*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_util_eval_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 

acpi_status
acpi_evaluate_reference(acpi_handle handle,
			acpi_string pathname,
			struct acpi_object_list *arguments,
			struct acpi_handle_list *list)
{
	acpi_status status = AE_OK;
	union acpi_object *package = NULL;
	union acpi_object *element = NULL;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	u32 i = 0;


	if (!list) {
		return AE_BAD_PARAMETER;
	}

	/* Evaluate object. */

	status = acpi_evaluate_object(handle, pathname, arguments, &buffer);
	if (ACPI_FAILURE(status))
		goto end;

	package = buffer.pointer;

	if ((buffer.length == 0) || !package) {
		status = AE_BAD_DATA;
		acpi_util_eval_error(handle, pathname, status);
		goto end;
	}
	if (package->type != ACPI_TYPE_PACKAGE) {
		status = AE_BAD_DATA;
		acpi_util_eval_error(handle, pathname, status);
		goto end;
	}
	if (!package->package.count) {
		status = AE_BAD_DATA;
		acpi_util_eval_error(handle, pathname, status);
		goto end;
	}

	if (package->package.count > ACPI_MAX_HANDLES) {
		kfree(package);
		return AE_NO_MEMORY;
	}
	list->count = package->package.count;

	/* Extract package data. */

	for (i = 0; i < list->count; i++) {

		element = &(package->package.elements[i]);

		if (element->type != ACPI_TYPE_LOCAL_REFERENCE) {
			status = AE_BAD_DATA;
			acpi_util_eval_error(handle, pathname, status);
			break;
		}

		if (!element->reference.handle) {
			status = AE_NULL_ENTRY;
			acpi_util_eval_error(handle, pathname, status);
			break;
		}
		/* Get the  acpi_handle. */

		list->handles[i] = element->reference.handle;
		ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Found reference [%p]\n",
				  list->handles[i]));
	}

      end:
	if (ACPI_FAILURE(status)) {
		list->count = 0;
		//kfree(list->handles);
	}

	kfree(buffer.pointer);

	return status;
}