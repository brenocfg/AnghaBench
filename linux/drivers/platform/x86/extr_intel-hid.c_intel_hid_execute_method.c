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
struct TYPE_4__ {int count; union acpi_object* elements; } ;
struct TYPE_3__ {unsigned long long value; } ;
union acpi_object {TYPE_2__ package; int /*<<< orphan*/  type; TYPE_1__ integer; } ;
typedef  enum intel_hid_dsm_fn_codes { ____Placeholder_intel_hid_dsm_fn_codes } intel_hid_dsm_fn_codes ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 int INTEL_HID_DSM_FN_INVALID ; 
 int INTEL_HID_DSM_FN_MAX ; 
 union acpi_object* acpi_evaluate_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,union acpi_object*) ; 
 int /*<<< orphan*/  acpi_execute_simple_method (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  intel_dsm_guid ; 
 int intel_hid_dsm_fn_mask ; 
 scalar_t__* intel_hid_dsm_fn_to_method ; 

__attribute__((used)) static bool intel_hid_execute_method(acpi_handle handle,
				     enum intel_hid_dsm_fn_codes fn_index,
				     unsigned long long arg)
{
	union acpi_object *obj, argv4, req;
	acpi_status status;
	char *method_name;

	if (fn_index <= INTEL_HID_DSM_FN_INVALID ||
	    fn_index >= INTEL_HID_DSM_FN_MAX)
		return false;

	method_name = (char *)intel_hid_dsm_fn_to_method[fn_index];

	if (!(intel_hid_dsm_fn_mask & fn_index))
		goto skip_dsm_exec;

	/* All methods expects a package with one integer element */
	req.type = ACPI_TYPE_INTEGER;
	req.integer.value = arg;

	argv4.type = ACPI_TYPE_PACKAGE;
	argv4.package.count = 1;
	argv4.package.elements = &req;

	obj = acpi_evaluate_dsm(handle, &intel_dsm_guid, 1, fn_index, &argv4);
	if (obj) {
		acpi_handle_debug(handle, "Exec DSM Fn code: %d[%s] success\n",
				  fn_index, method_name);
		ACPI_FREE(obj);
		return true;
	}

skip_dsm_exec:
	status = acpi_execute_simple_method(handle, method_name, arg);
	if (ACPI_SUCCESS(status))
		return true;

	return false;
}