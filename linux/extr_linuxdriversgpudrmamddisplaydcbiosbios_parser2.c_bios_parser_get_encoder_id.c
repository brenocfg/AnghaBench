#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct graphics_object_id {int dummy; } ;
struct dc_bios {int dummy; } ;
struct TYPE_6__ {TYPE_2__* v1_4; } ;
struct bios_parser {TYPE_3__ object_info_tbl; } ;
struct TYPE_5__ {size_t number_of_path; TYPE_1__* display_path; } ;
struct TYPE_4__ {int /*<<< orphan*/  encoderobjid; } ;

/* Variables and functions */
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int /*<<< orphan*/  ENUM_ID_UNKNOWN ; 
 int /*<<< orphan*/  OBJECT_TYPE_UNKNOWN ; 
 struct graphics_object_id dal_graphics_object_id_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct graphics_object_id object_id_from_bios_object_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct graphics_object_id bios_parser_get_encoder_id(
	struct dc_bios *dcb,
	uint32_t i)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);
	struct graphics_object_id object_id = dal_graphics_object_id_init(
		0, ENUM_ID_UNKNOWN, OBJECT_TYPE_UNKNOWN);

	if (bp->object_info_tbl.v1_4->number_of_path > i)
		object_id = object_id_from_bios_object_id(
		bp->object_info_tbl.v1_4->display_path[i].encoderobjid);

	return object_id;
}