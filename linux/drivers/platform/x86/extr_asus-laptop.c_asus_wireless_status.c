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
struct asus_laptop {int wireless_status; int /*<<< orphan*/  handle; int /*<<< orphan*/  have_rsts; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int EINVAL ; 
 int /*<<< orphan*/  METHOD_WL_STATUS ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int asus_wireless_status(struct asus_laptop *asus, int mask)
{
	unsigned long long status;
	acpi_status rv = AE_OK;

	if (!asus->have_rsts)
		return (asus->wireless_status & mask) ? 1 : 0;

	rv = acpi_evaluate_integer(asus->handle, METHOD_WL_STATUS,
				   NULL, &status);
	if (ACPI_FAILURE(rv)) {
		pr_warn("Error reading Wireless status\n");
		return -EINVAL;
	}
	return !!(status & mask);
}