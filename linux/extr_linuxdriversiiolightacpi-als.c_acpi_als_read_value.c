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
struct acpi_als {TYPE_1__* device; } ;
typedef  unsigned long long s32 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int EIO ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 

__attribute__((used)) static int acpi_als_read_value(struct acpi_als *als, char *prop, s32 *val)
{
	unsigned long long temp_val;
	acpi_status status;

	status = acpi_evaluate_integer(als->device->handle, prop, NULL,
				       &temp_val);

	if (ACPI_FAILURE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "Error reading ALS %s", prop));
		return -EIO;
	}

	*val = temp_val;

	return 0;
}