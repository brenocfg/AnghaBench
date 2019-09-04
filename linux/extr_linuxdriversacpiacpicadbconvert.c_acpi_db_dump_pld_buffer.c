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
struct TYPE_4__ {int length; int /*<<< orphan*/  pointer; } ;
struct TYPE_3__ {union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_2__ buffer; TYPE_1__ package; } ;
struct acpi_pld_info {int /*<<< orphan*/  horizontal_offset; int /*<<< orphan*/  vertical_offset; int /*<<< orphan*/  order; int /*<<< orphan*/  rotation; int /*<<< orphan*/  reference; int /*<<< orphan*/  card_cage_number; int /*<<< orphan*/  cabinet_number; int /*<<< orphan*/  ospm_eject_required; int /*<<< orphan*/  ejectable; int /*<<< orphan*/  bay; int /*<<< orphan*/  group_position; int /*<<< orphan*/  group_token; int /*<<< orphan*/  group_orientation; int /*<<< orphan*/  shape; int /*<<< orphan*/  horizontal_position; int /*<<< orphan*/  vertical_position; int /*<<< orphan*/  panel; int /*<<< orphan*/  lid; int /*<<< orphan*/  dock; int /*<<< orphan*/  user_visible; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  ignore_color; int /*<<< orphan*/  revision; } ;
typedef  struct acpi_pld_info u8 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_pld_info*) ; 
 int /*<<< orphan*/  ACPI_PLD_OUTPUT ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  DB_BYTE_DISPLAY ; 
 struct acpi_pld_info* acpi_db_encode_pld_buffer (struct acpi_pld_info*) ; 
 int /*<<< orphan*/  acpi_decode_pld_buffer (int /*<<< orphan*/ ,int,struct acpi_pld_info**) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 
 int /*<<< orphan*/  acpi_ut_dump_buffer (struct acpi_pld_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (struct acpi_pld_info*,int /*<<< orphan*/ ,int) ; 

void acpi_db_dump_pld_buffer(union acpi_object *obj_desc)
{
	union acpi_object *buffer_desc;
	struct acpi_pld_info *pld_info;
	u8 *new_buffer;
	acpi_status status;

	/* Object must be of type Package with at least one Buffer element */

	if (obj_desc->type != ACPI_TYPE_PACKAGE) {
		return;
	}

	buffer_desc = &obj_desc->package.elements[0];
	if (buffer_desc->type != ACPI_TYPE_BUFFER) {
		return;
	}

	/* Convert _PLD buffer to local _PLD struct */

	status = acpi_decode_pld_buffer(buffer_desc->buffer.pointer,
					buffer_desc->buffer.length, &pld_info);
	if (ACPI_FAILURE(status)) {
		return;
	}

	/* Encode local _PLD struct back to a _PLD buffer */

	new_buffer = acpi_db_encode_pld_buffer(pld_info);
	if (!new_buffer) {
		goto exit;
	}

	/* The two bit-packed buffers should match */

	if (memcmp(new_buffer, buffer_desc->buffer.pointer,
		   buffer_desc->buffer.length)) {
		acpi_os_printf
		    ("Converted _PLD buffer does not compare. New:\n");

		acpi_ut_dump_buffer(new_buffer,
				    buffer_desc->buffer.length, DB_BYTE_DISPLAY,
				    0);
	}

	/* First 32-bit dword */

	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_Revision", pld_info->revision);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_IgnoreColor",
		       pld_info->ignore_color);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_Red", pld_info->red);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_Green", pld_info->green);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_Blue", pld_info->blue);

	/* Second 32-bit dword */

	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_Width", pld_info->width);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_Height", pld_info->height);

	/* Third 32-bit dword */

	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_UserVisible",
		       pld_info->user_visible);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_Dock", pld_info->dock);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_Lid", pld_info->lid);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_Panel", pld_info->panel);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_VerticalPosition",
		       pld_info->vertical_position);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_HorizontalPosition",
		       pld_info->horizontal_position);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_Shape", pld_info->shape);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_GroupOrientation",
		       pld_info->group_orientation);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_GroupToken",
		       pld_info->group_token);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_GroupPosition",
		       pld_info->group_position);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_Bay", pld_info->bay);

	/* Fourth 32-bit dword */

	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_Ejectable", pld_info->ejectable);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_EjectRequired",
		       pld_info->ospm_eject_required);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_CabinetNumber",
		       pld_info->cabinet_number);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_CardCageNumber",
		       pld_info->card_cage_number);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_Reference", pld_info->reference);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_Rotation", pld_info->rotation);
	acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_Order", pld_info->order);

	/* Fifth 32-bit dword */

	if (buffer_desc->buffer.length > 16) {
		acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_VerticalOffset",
			       pld_info->vertical_offset);
		acpi_os_printf(ACPI_PLD_OUTPUT, "PLD_HorizontalOffset",
			       pld_info->horizontal_offset);
	}

	ACPI_FREE(new_buffer);
exit:
	ACPI_FREE(pld_info);
}