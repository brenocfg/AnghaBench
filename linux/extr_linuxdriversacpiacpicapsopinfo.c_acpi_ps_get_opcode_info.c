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
typedef  size_t u8 ;
typedef  int u16 ;
struct acpi_opcode_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int AML_EXTENDED_OPCODE ; 
 size_t MAX_EXTENDED_OPCODE ; 
 size_t _UNK ; 
 struct acpi_opcode_info const* acpi_gbl_aml_op_info ; 
 size_t* acpi_gbl_long_op_index ; 
 size_t* acpi_gbl_short_op_index ; 
 int /*<<< orphan*/  opcode_name ; 
 int /*<<< orphan*/  ps_get_opcode_info ; 

const struct acpi_opcode_info *acpi_ps_get_opcode_info(u16 opcode)
{
#ifdef ACPI_DEBUG_OUTPUT
	const char *opcode_name = "Unknown AML opcode";
#endif

	ACPI_FUNCTION_NAME(ps_get_opcode_info);

	/*
	 * Detect normal 8-bit opcode or extended 16-bit opcode
	 */
	if (!(opcode & 0xFF00)) {

		/* Simple (8-bit) opcode: 0-255, can't index beyond table  */

		return (&acpi_gbl_aml_op_info
			[acpi_gbl_short_op_index[(u8)opcode]]);
	}

	if (((opcode & 0xFF00) == AML_EXTENDED_OPCODE) &&
	    (((u8)opcode) <= MAX_EXTENDED_OPCODE)) {

		/* Valid extended (16-bit) opcode */

		return (&acpi_gbl_aml_op_info
			[acpi_gbl_long_op_index[(u8)opcode]]);
	}
#if defined ACPI_ASL_COMPILER && defined ACPI_DEBUG_OUTPUT
#include "asldefine.h"

	switch (opcode) {
	case AML_RAW_DATA_BYTE:
		opcode_name = "-Raw Data Byte-";
		break;

	case AML_RAW_DATA_WORD:
		opcode_name = "-Raw Data Word-";
		break;

	case AML_RAW_DATA_DWORD:
		opcode_name = "-Raw Data Dword-";
		break;

	case AML_RAW_DATA_QWORD:
		opcode_name = "-Raw Data Qword-";
		break;

	case AML_RAW_DATA_BUFFER:
		opcode_name = "-Raw Data Buffer-";
		break;

	case AML_RAW_DATA_CHAIN:
		opcode_name = "-Raw Data Buffer Chain-";
		break;

	case AML_PACKAGE_LENGTH:
		opcode_name = "-Package Length-";
		break;

	case AML_UNASSIGNED_OPCODE:
		opcode_name = "-Unassigned Opcode-";
		break;

	case AML_DEFAULT_ARG_OP:
		opcode_name = "-Default Arg-";
		break;

	default:
		break;
	}
#endif

	/* Unknown AML opcode */

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "%s [%4.4X]\n", opcode_name, opcode));

	return (&acpi_gbl_aml_op_info[_UNK]);
}