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
struct TYPE_4__ {char* pointer; } ;
struct TYPE_3__ {char* pointer; } ;
union acpi_object {int type; TYPE_2__ buffer; TYPE_1__ string; } ;
typedef  char* uint ;
struct asus_laptop {int have_rsts; int /*<<< orphan*/  handle; int /*<<< orphan*/  name; int /*<<< orphan*/  dsdt_info; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_DSDT ; 
#define  ACPI_TYPE_BUFFER 129 
#define  ACPI_TYPE_STRING 128 
 int AE_OK ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  METHOD_WL_STATUS ; 
 int /*<<< orphan*/  acpi_check_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_get_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_notice (char*,char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  wapf ; 
 scalar_t__ write_acpi_int (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ write_acpi_int_ret (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct acpi_buffer*) ; 

__attribute__((used)) static int asus_laptop_get_info(struct asus_laptop *asus)
{
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *model = NULL;
	unsigned long long bsts_result;
	char *string = NULL;
	acpi_status status;

	/*
	 * Get DSDT headers early enough to allow for differentiating between
	 * models, but late enough to allow acpi_bus_register_driver() to fail
	 * before doing anything ACPI-specific. Should we encounter a machine,
	 * which needs special handling (i.e. its hotkey device has a different
	 * HID), this bit will be moved.
	 */
	status = acpi_get_table(ACPI_SIG_DSDT, 1, &asus->dsdt_info);
	if (ACPI_FAILURE(status))
		pr_warn("Couldn't get the DSDT table header\n");

	/* We have to write 0 on init this far for all ASUS models */
	if (write_acpi_int_ret(asus->handle, "INIT", 0, &buffer)) {
		pr_err("Hotkey initialization failed\n");
		return -ENODEV;
	}

	/* This needs to be called for some laptops to init properly */
	status =
	    acpi_evaluate_integer(asus->handle, "BSTS", NULL, &bsts_result);
	if (ACPI_FAILURE(status))
		pr_warn("Error calling BSTS\n");
	else if (bsts_result)
		pr_notice("BSTS called, 0x%02x returned\n",
		       (uint) bsts_result);

	/* This too ... */
	if (write_acpi_int(asus->handle, "CWAP", wapf))
		pr_err("Error calling CWAP(%d)\n", wapf);
	/*
	 * Try to match the object returned by INIT to the specific model.
	 * Handle every possible object (or the lack of thereof) the DSDT
	 * writers might throw at us. When in trouble, we pass NULL to
	 * asus_model_match() and try something completely different.
	 */
	if (buffer.pointer) {
		model = buffer.pointer;
		switch (model->type) {
		case ACPI_TYPE_STRING:
			string = model->string.pointer;
			break;
		case ACPI_TYPE_BUFFER:
			string = model->buffer.pointer;
			break;
		default:
			string = "";
			break;
		}
	}
	asus->name = kstrdup(string, GFP_KERNEL);
	if (!asus->name) {
		kfree(buffer.pointer);
		return -ENOMEM;
	}

	if (string)
		pr_notice("  %s model detected\n", string);

	if (!acpi_check_handle(asus->handle, METHOD_WL_STATUS, NULL))
		asus->have_rsts = true;

	kfree(model);

	return AE_OK;
}