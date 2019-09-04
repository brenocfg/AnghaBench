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
typedef  scalar_t__ u8 ;
struct acpi_ec {int dummy; } ;

/* Variables and functions */
 int ACPI_EC_CLEAR_MAX ; 
 int acpi_ec_query (struct acpi_ec*,scalar_t__*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void acpi_ec_clear(struct acpi_ec *ec)
{
	int i, status;
	u8 value = 0;

	for (i = 0; i < ACPI_EC_CLEAR_MAX; i++) {
		status = acpi_ec_query(ec, &value);
		if (status || !value)
			break;
	}
	if (unlikely(i == ACPI_EC_CLEAR_MAX))
		pr_warn("Warning: Maximum of %d stale EC events cleared\n", i);
	else
		pr_info("%d stale EC events cleared\n", i);
}