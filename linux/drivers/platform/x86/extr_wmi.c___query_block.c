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
struct TYPE_4__ {scalar_t__ value; } ;
union acpi_object {TYPE_2__ integer; int /*<<< orphan*/  type; } ;
typedef  scalar_t__ u8 ;
struct guid_block {scalar_t__ instance_count; int flags; int /*<<< orphan*/  object_id; } ;
struct wmi_block {scalar_t__ read_takes_no_args; TYPE_1__* acpi_device; struct guid_block gblock; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int ACPI_WMI_EVENT ; 
 int ACPI_WMI_EXPENSIVE ; 
 int ACPI_WMI_METHOD ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,struct acpi_object_list*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_execute_simple_method (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncat (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static acpi_status __query_block(struct wmi_block *wblock, u8 instance,
				 struct acpi_buffer *out)
{
	struct guid_block *block = NULL;
	acpi_handle handle;
	acpi_status status, wc_status = AE_ERROR;
	struct acpi_object_list input;
	union acpi_object wq_params[1];
	char method[5];
	char wc_method[5] = "WC";

	if (!out)
		return AE_BAD_PARAMETER;

	block = &wblock->gblock;
	handle = wblock->acpi_device->handle;

	if (block->instance_count <= instance)
		return AE_BAD_PARAMETER;

	/* Check GUID is a data block */
	if (block->flags & (ACPI_WMI_EVENT | ACPI_WMI_METHOD))
		return AE_ERROR;

	input.count = 1;
	input.pointer = wq_params;
	wq_params[0].type = ACPI_TYPE_INTEGER;
	wq_params[0].integer.value = instance;

	if (instance == 0 && wblock->read_takes_no_args)
		input.count = 0;

	/*
	 * If ACPI_WMI_EXPENSIVE, call the relevant WCxx method first to
	 * enable collection.
	 */
	if (block->flags & ACPI_WMI_EXPENSIVE) {
		strncat(wc_method, block->object_id, 2);

		/*
		 * Some GUIDs break the specification by declaring themselves
		 * expensive, but have no corresponding WCxx method. So we
		 * should not fail if this happens.
		 */
		wc_status = acpi_execute_simple_method(handle, wc_method, 1);
	}

	strcpy(method, "WQ");
	strncat(method, block->object_id, 2);

	status = acpi_evaluate_object(handle, method, &input, out);

	/*
	 * If ACPI_WMI_EXPENSIVE, call the relevant WCxx method, even if
	 * the WQxx method failed - we should disable collection anyway.
	 */
	if ((block->flags & ACPI_WMI_EXPENSIVE) && ACPI_SUCCESS(wc_status)) {
		status = acpi_execute_simple_method(handle, wc_method, 0);
	}

	return status;
}