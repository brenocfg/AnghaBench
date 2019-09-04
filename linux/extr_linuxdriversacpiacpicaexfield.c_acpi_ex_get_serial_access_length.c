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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_GSBUS_BUFFER_SIZE ; 
#define  AML_FIELD_ATTRIB_BLOCK 137 
#define  AML_FIELD_ATTRIB_BLOCK_CALL 136 
#define  AML_FIELD_ATTRIB_BYTE 135 
#define  AML_FIELD_ATTRIB_MULTIBYTE 134 
#define  AML_FIELD_ATTRIB_QUICK 133 
#define  AML_FIELD_ATTRIB_RAW_BYTES 132 
#define  AML_FIELD_ATTRIB_RAW_PROCESS 131 
#define  AML_FIELD_ATTRIB_SEND_RCV 130 
#define  AML_FIELD_ATTRIB_WORD 129 
#define  AML_FIELD_ATTRIB_WORD_CALL 128 

__attribute__((used)) static u32
acpi_ex_get_serial_access_length(u32 accessor_type, u32 access_length)
{
	u32 length;

	switch (accessor_type) {
	case AML_FIELD_ATTRIB_QUICK:

		length = 0;
		break;

	case AML_FIELD_ATTRIB_SEND_RCV:
	case AML_FIELD_ATTRIB_BYTE:

		length = 1;
		break;

	case AML_FIELD_ATTRIB_WORD:
	case AML_FIELD_ATTRIB_WORD_CALL:

		length = 2;
		break;

	case AML_FIELD_ATTRIB_MULTIBYTE:
	case AML_FIELD_ATTRIB_RAW_BYTES:
	case AML_FIELD_ATTRIB_RAW_PROCESS:

		length = access_length;
		break;

	case AML_FIELD_ATTRIB_BLOCK:
	case AML_FIELD_ATTRIB_BLOCK_CALL:
	default:

		length = ACPI_GSBUS_BUFFER_SIZE - 2;
		break;
	}

	return (length);
}