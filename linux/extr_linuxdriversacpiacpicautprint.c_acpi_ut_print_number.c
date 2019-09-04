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
 int /*<<< orphan*/  FALSE ; 
 char* acpi_ut_put_number (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

const char *acpi_ut_print_number(char *string, u64 number)
{
	char ascii_string[20];
	const char *pos1;
	char *pos2;

	pos1 = acpi_ut_put_number(ascii_string, number, 10, FALSE);
	pos2 = string;

	while (pos1 != ascii_string) {
		*(pos2++) = *(--pos1);
	}

	*pos2 = 0;
	return (string);
}