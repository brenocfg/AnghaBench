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
struct TYPE_2__ {int count; int /*<<< orphan*/ * elements; } ;
union acpi_object {scalar_t__ type; int /*<<< orphan*/  target; int /*<<< orphan*/  source; TYPE_1__ package; } ;
struct trt {scalar_t__ type; int /*<<< orphan*/  target; int /*<<< orphan*/  source; TYPE_1__ package; } ;
struct acpi_device {int dummy; } ;
struct acpi_buffer {int member_0; char* member_1; int length; union acpi_object* pointer; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int EFAULT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_extract_package (int /*<<< orphan*/ *,struct acpi_buffer*,struct acpi_buffer*) ; 
 union acpi_object* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 

int acpi_parse_trt(acpi_handle handle, int *trt_count, struct trt **trtp,
		bool create_dev)
{
	acpi_status status;
	int result = 0;
	int i;
	int nr_bad_entries = 0;
	struct trt *trts;
	struct acpi_device *adev;
	union acpi_object *p;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	struct acpi_buffer element = { 0, NULL };
	struct acpi_buffer trt_format = { sizeof("RRNNNNNN"), "RRNNNNNN" };

	status = acpi_evaluate_object(handle, "_TRT", NULL, &buffer);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	p = buffer.pointer;
	if (!p || (p->type != ACPI_TYPE_PACKAGE)) {
		pr_err("Invalid _TRT data\n");
		result = -EFAULT;
		goto end;
	}

	*trt_count = p->package.count;
	trts = kcalloc(*trt_count, sizeof(struct trt), GFP_KERNEL);
	if (!trts) {
		result = -ENOMEM;
		goto end;
	}

	for (i = 0; i < *trt_count; i++) {
		struct trt *trt = &trts[i - nr_bad_entries];

		element.length = sizeof(struct trt);
		element.pointer = trt;

		status = acpi_extract_package(&(p->package.elements[i]),
					      &trt_format, &element);
		if (ACPI_FAILURE(status)) {
			nr_bad_entries++;
			pr_warn("_TRT package %d is invalid, ignored\n", i);
			continue;
		}
		if (!create_dev)
			continue;

		result = acpi_bus_get_device(trt->source, &adev);
		if (result)
			pr_warn("Failed to get source ACPI device\n");

		result = acpi_bus_get_device(trt->target, &adev);
		if (result)
			pr_warn("Failed to get target ACPI device\n");
	}

	result = 0;

	*trtp = trts;
	/* don't count bad entries */
	*trt_count -= nr_bad_entries;
end:
	kfree(buffer.pointer);
	return result;
}