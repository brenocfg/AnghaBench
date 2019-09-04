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
typedef  size_t uint8_t ;
struct object_info_table {struct display_object_info_table_v1_4* v1_4; } ;
struct graphics_object_id {int dummy; } ;
struct display_object_info_table_v1_4 {size_t number_of_path; TYPE_1__* display_path; } ;
struct dc_bios {int dummy; } ;
struct bios_parser {struct object_info_table object_info_tbl; } ;
struct TYPE_2__ {scalar_t__ encoderobjid; scalar_t__ display_objid; } ;

/* Variables and functions */
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int /*<<< orphan*/  ENUM_ID_UNKNOWN ; 
 int /*<<< orphan*/  OBJECT_TYPE_UNKNOWN ; 
 struct graphics_object_id dal_graphics_object_id_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct graphics_object_id object_id_from_bios_object_id (scalar_t__) ; 

__attribute__((used)) static struct graphics_object_id bios_parser_get_connector_id(
	struct dc_bios *dcb,
	uint8_t i)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);
	struct graphics_object_id object_id = dal_graphics_object_id_init(
		0, ENUM_ID_UNKNOWN, OBJECT_TYPE_UNKNOWN);
	struct object_info_table *tbl = &bp->object_info_tbl;
	struct display_object_info_table_v1_4 *v1_4 = tbl->v1_4;

	if (v1_4->number_of_path > i) {
		/* If display_objid is generic object id,  the encoderObj
		 * /extencoderobjId should be 0
		 */
		if (v1_4->display_path[i].encoderobjid != 0 &&
				v1_4->display_path[i].display_objid != 0)
			object_id = object_id_from_bios_object_id(
					v1_4->display_path[i].display_objid);
	}

	return object_id;
}