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
struct graphics_object_id {int type; int /*<<< orphan*/  enum_id; int /*<<< orphan*/  id; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {TYPE_1__* v1_4; } ;
struct bios_parser {TYPE_2__ object_info_tbl; } ;
struct atom_display_object_path_v2 {int /*<<< orphan*/  display_objid; int /*<<< orphan*/  encoderobjid; } ;
struct TYPE_3__ {unsigned int number_of_path; struct atom_display_object_path_v2* display_path; } ;

/* Variables and functions */
#define  OBJECT_TYPE_CONNECTOR 130 
#define  OBJECT_TYPE_ENCODER 129 
#define  OBJECT_TYPE_GENERIC 128 
 struct graphics_object_id object_id_from_bios_object_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct atom_display_object_path_v2 *get_bios_object(
		struct bios_parser *bp,
		struct graphics_object_id id)
{
	unsigned int i;
	struct graphics_object_id obj_id = {0};

	switch (id.type) {
	case OBJECT_TYPE_ENCODER:
		for (i = 0; i < bp->object_info_tbl.v1_4->number_of_path; i++) {
			obj_id = object_id_from_bios_object_id(
					bp->object_info_tbl.v1_4->display_path[i].encoderobjid);
			if (id.type == obj_id.type && id.id == obj_id.id
					&& id.enum_id == obj_id.enum_id)
				return &bp->object_info_tbl.v1_4->display_path[i];
		}
		/* fall through */
	case OBJECT_TYPE_CONNECTOR:
	case OBJECT_TYPE_GENERIC:
		/* Both Generic and Connector Object ID
		 * will be stored on display_objid
		 */
		for (i = 0; i < bp->object_info_tbl.v1_4->number_of_path; i++) {
			obj_id = object_id_from_bios_object_id(
					bp->object_info_tbl.v1_4->display_path[i].display_objid);
			if (id.type == obj_id.type && id.id == obj_id.id
					&& id.enum_id == obj_id.enum_id)
				return &bp->object_info_tbl.v1_4->display_path[i];
		}
		/* fall through */
	default:
		return NULL;
	}
}