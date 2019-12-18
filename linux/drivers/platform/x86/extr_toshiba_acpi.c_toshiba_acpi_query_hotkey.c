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
struct toshiba_acpi_dev {TYPE_1__* acpi_dev; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int toshiba_acpi_query_hotkey(struct toshiba_acpi_dev *dev)
{
	unsigned long long value;
	acpi_status status;

	status = acpi_evaluate_integer(dev->acpi_dev->handle, "INFO",
				      NULL, &value);
	if (ACPI_FAILURE(status)) {
		pr_err("ACPI INFO method execution failed\n");
		return -EIO;
	}

	return value;
}