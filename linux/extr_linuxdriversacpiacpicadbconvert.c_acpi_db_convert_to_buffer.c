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
struct TYPE_2__ {size_t length; int /*<<< orphan*/ * pointer; } ;
union acpi_object {TYPE_1__ buffer; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/ * ACPI_ALLOCATE (size_t) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_db_hex_byte_to_binary (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static acpi_status
acpi_db_convert_to_buffer(char *string, union acpi_object *object)
{
	u32 i;
	u32 j;
	u32 length;
	u8 *buffer;
	acpi_status status;

	/* Generate the final buffer length */

	for (i = 0, length = 0; string[i];) {
		i += 2;
		length++;

		while (string[i] && ((string[i] == ',') || (string[i] == ' '))) {
			i++;
		}
	}

	buffer = ACPI_ALLOCATE(length);
	if (!buffer) {
		return (AE_NO_MEMORY);
	}

	/* Convert the command line bytes to the buffer */

	for (i = 0, j = 0; string[i];) {
		status = acpi_db_hex_byte_to_binary(&string[i], &buffer[j]);
		if (ACPI_FAILURE(status)) {
			ACPI_FREE(buffer);
			return (status);
		}

		j++;
		i += 2;
		while (string[i] && ((string[i] == ',') || (string[i] == ' '))) {
			i++;
		}
	}

	object->type = ACPI_TYPE_BUFFER;
	object->buffer.pointer = buffer;
	object->buffer.length = length;
	return (AE_OK);
}