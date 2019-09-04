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
typedef  int /*<<< orphan*/  uint32_t ;
struct object_info_table {TYPE_2__* v1_4; } ;
struct graphics_object_id {int type; int /*<<< orphan*/  enum_id; int /*<<< orphan*/  id; int /*<<< orphan*/  member_0; } ;
struct dc_bios {int dummy; } ;
struct bios_parser {struct object_info_table object_info_tbl; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_4__ {unsigned int number_of_path; TYPE_1__* display_path; } ;
struct TYPE_3__ {int encoderobjid; int display_objid; } ;

/* Variables and functions */
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int BP_RESULT_BADINPUT ; 
 int BP_RESULT_OK ; 
#define  OBJECT_TYPE_CONNECTOR 129 
#define  OBJECT_TYPE_ENCODER 128 
 struct graphics_object_id object_id_from_bios_object_id (int) ; 

__attribute__((used)) static enum bp_result bios_parser_get_src_obj(struct dc_bios *dcb,
	struct graphics_object_id object_id, uint32_t index,
	struct graphics_object_id *src_object_id)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);
	unsigned int i;
	enum bp_result  bp_result = BP_RESULT_BADINPUT;
	struct graphics_object_id obj_id = {0};
	struct object_info_table *tbl = &bp->object_info_tbl;

	if (!src_object_id)
		return bp_result;

	switch (object_id.type) {
	/* Encoder's Source is GPU.  BIOS does not provide GPU, since all
	 * displaypaths point to same GPU (0x1100).  Hardcode GPU object type
	 */
	case OBJECT_TYPE_ENCODER:
		/* TODO: since num of src must be less than 2.
		 * If found in for loop, should break.
		 * DAL2 implementation may be changed too
		 */
		for (i = 0; i < tbl->v1_4->number_of_path; i++) {
			obj_id = object_id_from_bios_object_id(
			tbl->v1_4->display_path[i].encoderobjid);
			if (object_id.type == obj_id.type &&
					object_id.id == obj_id.id &&
						object_id.enum_id ==
							obj_id.enum_id) {
				*src_object_id =
				object_id_from_bios_object_id(0x1100);
				/* break; */
			}
		}
		bp_result = BP_RESULT_OK;
		break;
	case OBJECT_TYPE_CONNECTOR:
		for (i = 0; i < tbl->v1_4->number_of_path; i++) {
			obj_id = object_id_from_bios_object_id(
				tbl->v1_4->display_path[i].display_objid);

			if (object_id.type == obj_id.type &&
				object_id.id == obj_id.id &&
					object_id.enum_id == obj_id.enum_id) {
				*src_object_id =
				object_id_from_bios_object_id(
				tbl->v1_4->display_path[i].encoderobjid);
				/* break; */
			}
		}
		bp_result = BP_RESULT_OK;
		break;
	default:
		break;
	}

	return bp_result;
}