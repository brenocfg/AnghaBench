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
typedef  int /*<<< orphan*/  u64 ;
struct acpi_resource_vendor_typed {int byte_length; scalar_t__ byte_data; } ;
struct TYPE_2__ {struct acpi_resource_vendor_typed vendor_typed; } ;
struct acpi_resource {TYPE_1__ data; } ;
struct acpi_buffer {struct acpi_resource* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  METHOD_NAME__CRS ; 
 int /*<<< orphan*/  acpi_get_vendor_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  hp_ccsr_uuid ; 
 int /*<<< orphan*/  kfree (struct acpi_resource*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static acpi_status hp_ccsr_locate(acpi_handle obj, u64 *base, u64 *length)
{
	acpi_status status;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	struct acpi_resource *resource;
	struct acpi_resource_vendor_typed *vendor;

	status = acpi_get_vendor_resource(obj, METHOD_NAME__CRS, &hp_ccsr_uuid,
		&buffer);

	resource = buffer.pointer;
	vendor = &resource->data.vendor_typed;

	if (ACPI_FAILURE(status) || vendor->byte_length < 16) {
		status = AE_NOT_FOUND;
		goto exit;
	}

	memcpy(base, vendor->byte_data, sizeof(*base));
	memcpy(length, vendor->byte_data + 8, sizeof(*length));

  exit:
	kfree(buffer.pointer);
	return status;
}