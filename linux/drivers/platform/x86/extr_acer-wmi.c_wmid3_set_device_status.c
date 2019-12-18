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
struct TYPE_2__ {int length; scalar_t__ pointer; } ;
union acpi_object {scalar_t__ type; TYPE_1__ buffer; } ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct wmid3_gds_set_input_param {int function_num; int devices; int /*<<< orphan*/  hotkey_number; } ;
struct wmid3_gds_return_value {int devices; scalar_t__ ec_return_value; scalar_t__ error_code; } ;
struct wmid3_gds_get_input_param {int function_num; int devices; int /*<<< orphan*/  hotkey_number; } ;
struct acpi_buffer {int member_0; union acpi_object* pointer; struct wmid3_gds_set_input_param* member_1; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  WMID_GUID3 ; 
 int /*<<< orphan*/  commun_fn_key_number ; 
 int commun_func_bitmap ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  pr_warn (char*,int,...) ; 
 int /*<<< orphan*/  wmi_evaluate_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct acpi_buffer*,struct acpi_buffer*) ; 

__attribute__((used)) static acpi_status wmid3_set_device_status(u32 value, u16 device)
{
	struct wmid3_gds_return_value return_value;
	acpi_status status;
	union acpi_object *obj;
	u16 devices;
	struct wmid3_gds_get_input_param get_params = {
		.function_num = 0x1,
		.hotkey_number = commun_fn_key_number,
		.devices = commun_func_bitmap,
	};
	struct acpi_buffer get_input = {
		sizeof(struct wmid3_gds_get_input_param),
		&get_params
	};
	struct wmid3_gds_set_input_param set_params = {
		.function_num = 0x2,
		.hotkey_number = commun_fn_key_number,
		.devices = commun_func_bitmap,
	};
	struct acpi_buffer set_input = {
		sizeof(struct wmid3_gds_set_input_param),
		&set_params
	};
	struct acpi_buffer output = { ACPI_ALLOCATE_BUFFER, NULL };
	struct acpi_buffer output2 = { ACPI_ALLOCATE_BUFFER, NULL };

	status = wmi_evaluate_method(WMID_GUID3, 0, 0x2, &get_input, &output);
	if (ACPI_FAILURE(status))
		return status;

	obj = output.pointer;

	if (!obj)
		return AE_ERROR;
	else if (obj->type != ACPI_TYPE_BUFFER) {
		kfree(obj);
		return AE_ERROR;
	}
	if (obj->buffer.length != 8) {
		pr_warn("Unknown buffer length %d\n", obj->buffer.length);
		kfree(obj);
		return AE_ERROR;
	}

	return_value = *((struct wmid3_gds_return_value *)obj->buffer.pointer);
	kfree(obj);

	if (return_value.error_code || return_value.ec_return_value) {
		pr_warn("Get Current Device Status failed: 0x%x - 0x%x\n",
			return_value.error_code,
			return_value.ec_return_value);
		return status;
	}

	devices = return_value.devices;
	set_params.devices = (value) ? (devices | device) : (devices & ~device);

	status = wmi_evaluate_method(WMID_GUID3, 0, 0x1, &set_input, &output2);
	if (ACPI_FAILURE(status))
		return status;

	obj = output2.pointer;

	if (!obj)
		return AE_ERROR;
	else if (obj->type != ACPI_TYPE_BUFFER) {
		kfree(obj);
		return AE_ERROR;
	}
	if (obj->buffer.length != 4) {
		pr_warn("Unknown buffer length %d\n", obj->buffer.length);
		kfree(obj);
		return AE_ERROR;
	}

	return_value = *((struct wmid3_gds_return_value *)obj->buffer.pointer);
	kfree(obj);

	if (return_value.error_code || return_value.ec_return_value)
		pr_warn("Set Device Status failed: 0x%x - 0x%x\n",
			return_value.error_code,
			return_value.ec_return_value);

	return status;
}