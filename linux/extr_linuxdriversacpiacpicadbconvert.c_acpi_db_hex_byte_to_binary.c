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
typedef  int u8 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_db_hex_char_to_value (char,int*) ; 

__attribute__((used)) static acpi_status acpi_db_hex_byte_to_binary(char *hex_byte, u8 *return_value)
{
	u8 local0;
	u8 local1;
	acpi_status status;

	/* High byte */

	status = acpi_db_hex_char_to_value(hex_byte[0], &local0);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	/* Low byte */

	status = acpi_db_hex_char_to_value(hex_byte[1], &local1);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	*return_value = (u8)((local0 << 4) | local1);
	return (AE_OK);
}