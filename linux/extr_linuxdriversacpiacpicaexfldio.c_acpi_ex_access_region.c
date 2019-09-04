#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int address; int /*<<< orphan*/  space_id; } ;
struct TYPE_3__ {int base_byte_offset; int /*<<< orphan*/  access_byte_width; union acpi_operand_object* region_obj; } ;
union acpi_operand_object {TYPE_2__ region; TYPE_1__ common_field; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_BFIELD ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (int) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_IO_MASK ; 
 int /*<<< orphan*/  ACPI_MUL_8 (int /*<<< orphan*/ ) ; 
 int ACPI_READ ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_NOT_EXIST ; 
 scalar_t__ AE_NOT_IMPLEMENTED ; 
 scalar_t__ acpi_ev_address_space_dispatch (union acpi_operand_object*,union acpi_operand_object*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_ex_setup_region (union acpi_operand_object*,int) ; 
 int /*<<< orphan*/  acpi_ut_get_region_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_access_region ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

acpi_status
acpi_ex_access_region(union acpi_operand_object *obj_desc,
		      u32 field_datum_byte_offset, u64 *value, u32 function)
{
	acpi_status status;
	union acpi_operand_object *rgn_desc;
	u32 region_offset;

	ACPI_FUNCTION_TRACE(ex_access_region);

	/*
	 * Ensure that the region operands are fully evaluated and verify
	 * the validity of the request
	 */
	status = acpi_ex_setup_region(obj_desc, field_datum_byte_offset);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/*
	 * The physical address of this field datum is:
	 *
	 * 1) The base of the region, plus
	 * 2) The base offset of the field, plus
	 * 3) The current offset into the field
	 */
	rgn_desc = obj_desc->common_field.region_obj;
	region_offset =
	    obj_desc->common_field.base_byte_offset + field_datum_byte_offset;

	if ((function & ACPI_IO_MASK) == ACPI_READ) {
		ACPI_DEBUG_PRINT((ACPI_DB_BFIELD, "[READ]"));
	} else {
		ACPI_DEBUG_PRINT((ACPI_DB_BFIELD, "[WRITE]"));
	}

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_BFIELD,
			      " Region [%s:%X], Width %X, ByteBase %X, Offset %X at %8.8X%8.8X\n",
			      acpi_ut_get_region_name(rgn_desc->region.
						      space_id),
			      rgn_desc->region.space_id,
			      obj_desc->common_field.access_byte_width,
			      obj_desc->common_field.base_byte_offset,
			      field_datum_byte_offset,
			      ACPI_FORMAT_UINT64(rgn_desc->region.address +
						 region_offset)));

	/* Invoke the appropriate address_space/op_region handler */

	status = acpi_ev_address_space_dispatch(rgn_desc, obj_desc,
						function, region_offset,
						ACPI_MUL_8(obj_desc->
							   common_field.
							   access_byte_width),
						value);

	if (ACPI_FAILURE(status)) {
		if (status == AE_NOT_IMPLEMENTED) {
			ACPI_ERROR((AE_INFO,
				    "Region %s (ID=%u) not implemented",
				    acpi_ut_get_region_name(rgn_desc->region.
							    space_id),
				    rgn_desc->region.space_id));
		} else if (status == AE_NOT_EXIST) {
			ACPI_ERROR((AE_INFO,
				    "Region %s (ID=%u) has no handler",
				    acpi_ut_get_region_name(rgn_desc->region.
							    space_id),
				    rgn_desc->region.space_id));
		}
	}

	return_ACPI_STATUS(status);
}