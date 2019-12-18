#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  GET_AUX0 ; 
 int /*<<< orphan*/  GET_AUX1 ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long long*) ; 

__attribute__((used)) static int sensor_get_auxtrip(acpi_handle handle, int index,
							unsigned long long *value)
{
	acpi_status status;

	if ((index != 0 && index != 1) || !value)
		return -EINVAL;

	status = acpi_evaluate_integer(handle, index ? GET_AUX1 : GET_AUX0,
				       NULL, value);
	if (ACPI_FAILURE(status))
		return -EIO;

	return 0;
}