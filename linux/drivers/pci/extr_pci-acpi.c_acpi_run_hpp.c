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
struct TYPE_3__ {int count; union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_2__ integer; TYPE_1__ package; } ;
struct pci_dev {int dummy; } ;
struct hpx_type0 {int revision; int /*<<< orphan*/  enable_perr; int /*<<< orphan*/  enable_serr; int /*<<< orphan*/  latency_timer; int /*<<< orphan*/  cache_line_size; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  hpx0 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct hpx_type0*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  program_hpx_type0 (struct pci_dev*,struct hpx_type0*) ; 

__attribute__((used)) static acpi_status acpi_run_hpp(struct pci_dev *dev, acpi_handle handle)
{
	acpi_status status;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *package, *fields;
	struct hpx_type0 hpx0;
	int i;

	memset(&hpx0, 0, sizeof(hpx0));

	status = acpi_evaluate_object(handle, "_HPP", NULL, &buffer);
	if (ACPI_FAILURE(status))
		return status;

	package = (union acpi_object *) buffer.pointer;
	if (package->type != ACPI_TYPE_PACKAGE ||
	    package->package.count != 4) {
		status = AE_ERROR;
		goto exit;
	}

	fields = package->package.elements;
	for (i = 0; i < 4; i++) {
		if (fields[i].type != ACPI_TYPE_INTEGER) {
			status = AE_ERROR;
			goto exit;
		}
	}

	hpx0.revision        = 1;
	hpx0.cache_line_size = fields[0].integer.value;
	hpx0.latency_timer   = fields[1].integer.value;
	hpx0.enable_serr     = fields[2].integer.value;
	hpx0.enable_perr     = fields[3].integer.value;

	program_hpx_type0(dev, &hpx0);

exit:
	kfree(buffer.pointer);
	return status;
}