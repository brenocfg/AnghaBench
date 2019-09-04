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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_ut_short_multiply (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (int) ; 

const char *acpi_ut_scan_number(const char *string, u64 *number_ptr)
{
	u64 number = 0;

	while (isdigit((int)*string)) {
		acpi_ut_short_multiply(number, 10, &number);
		number += *(string++) - '0';
	}

	*number_ptr = number;
	return (string);
}