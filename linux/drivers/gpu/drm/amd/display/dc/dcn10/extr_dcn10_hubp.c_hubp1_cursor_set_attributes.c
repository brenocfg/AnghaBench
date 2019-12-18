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
struct TYPE_2__ {int /*<<< orphan*/  low_part; int /*<<< orphan*/  high_part; } ;
struct dc_cursor_attributes {int /*<<< orphan*/  color_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__ address; int /*<<< orphan*/  pitch; } ;
struct hubp {struct dc_cursor_attributes curs_attr; } ;
struct dcn10_hubp {int dummy; } ;
typedef  enum cursor_pitch { ____Placeholder_cursor_pitch } cursor_pitch ;
typedef  enum cursor_lines_per_chunk { ____Placeholder_cursor_lines_per_chunk } cursor_lines_per_chunk ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR0_CHUNK_HDL_ADJUST ; 
 int /*<<< orphan*/  CURSOR0_DST_Y_OFFSET ; 
 int /*<<< orphan*/  CURSOR_CONTROL ; 
 int /*<<< orphan*/  CURSOR_HEIGHT ; 
 int /*<<< orphan*/  CURSOR_LINES_PER_CHUNK ; 
 int /*<<< orphan*/  CURSOR_MODE ; 
 int /*<<< orphan*/  CURSOR_PITCH ; 
 int /*<<< orphan*/  CURSOR_SETTINS ; 
 int /*<<< orphan*/  CURSOR_SIZE ; 
 int /*<<< orphan*/  CURSOR_SURFACE_ADDRESS ; 
 int /*<<< orphan*/  CURSOR_SURFACE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  CURSOR_WIDTH ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct dcn10_hubp* TO_DCN10_HUBP (struct hubp*) ; 
 int hubp1_get_cursor_pitch (int /*<<< orphan*/ ) ; 
 int hubp1_get_lines_per_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hubp1_cursor_set_attributes(
		struct hubp *hubp,
		const struct dc_cursor_attributes *attr)
{
	struct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	enum cursor_pitch hw_pitch = hubp1_get_cursor_pitch(attr->pitch);
	enum cursor_lines_per_chunk lpc = hubp1_get_lines_per_chunk(
			attr->width, attr->color_format);

	hubp->curs_attr = *attr;

	REG_UPDATE(CURSOR_SURFACE_ADDRESS_HIGH,
			CURSOR_SURFACE_ADDRESS_HIGH, attr->address.high_part);
	REG_UPDATE(CURSOR_SURFACE_ADDRESS,
			CURSOR_SURFACE_ADDRESS, attr->address.low_part);

	REG_UPDATE_2(CURSOR_SIZE,
			CURSOR_WIDTH, attr->width,
			CURSOR_HEIGHT, attr->height);

	REG_UPDATE_3(CURSOR_CONTROL,
			CURSOR_MODE, attr->color_format,
			CURSOR_PITCH, hw_pitch,
			CURSOR_LINES_PER_CHUNK, lpc);

	REG_SET_2(CURSOR_SETTINS, 0,
			/* no shift of the cursor HDL schedule */
			CURSOR0_DST_Y_OFFSET, 0,
			 /* used to shift the cursor chunk request deadline */
			CURSOR0_CHUNK_HDL_ADJUST, 3);
}