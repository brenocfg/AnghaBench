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
typedef  int /*<<< orphan*/  uint32_t ;
struct graphics_object_id {int dummy; } ;
struct dc_bios {int dummy; } ;
struct connector_device_tag_info {int /*<<< orphan*/  dev_id; scalar_t__ acpi_device; } ;
struct bios_parser {int dummy; } ;
struct atom_display_object_path_v2 {int /*<<< orphan*/  device_tag; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;

/* Variables and functions */
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int BP_RESULT_BADINPUT ; 
 int BP_RESULT_OK ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  device_type_from_device_id (int /*<<< orphan*/ ) ; 
 struct atom_display_object_path_v2* get_bios_object (struct bios_parser*,struct graphics_object_id) ; 

__attribute__((used)) static enum bp_result bios_parser_get_device_tag(
	struct dc_bios *dcb,
	struct graphics_object_id connector_object_id,
	uint32_t device_tag_index,
	struct connector_device_tag_info *info)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);
	struct atom_display_object_path_v2 *object;

	if (!info)
		return BP_RESULT_BADINPUT;

	/* getBiosObject will return MXM object */
	object = get_bios_object(bp, connector_object_id);

	if (!object) {
		BREAK_TO_DEBUGGER(); /* Invalid object id */
		return BP_RESULT_BADINPUT;
	}

	info->acpi_device = 0; /* BIOS no longer provides this */
	info->dev_id = device_type_from_device_id(object->device_tag);

	return BP_RESULT_OK;
}