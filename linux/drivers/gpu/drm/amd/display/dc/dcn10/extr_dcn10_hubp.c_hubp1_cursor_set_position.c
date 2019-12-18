#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {scalar_t__ quad_part; } ;
struct TYPE_9__ {scalar_t__ height; scalar_t__ width; TYPE_1__ address; } ;
struct hubp {TYPE_4__ curs_attr; TYPE_3__* funcs; } ;
struct dcn10_hubp {int dummy; } ;
struct dc_cursor_position {int x; int x_hotspot; int y; int y_hotspot; scalar_t__ enable; } ;
struct TYPE_7__ {int x; int y; int width; scalar_t__ height; } ;
struct TYPE_10__ {scalar_t__ value; } ;
struct dc_cursor_mi_param {scalar_t__ rotation; int ref_clk_khz; int pixel_clk_khz; TYPE_2__ viewport; TYPE_5__ h_scale_ratio; scalar_t__ mirror; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_cursor_attributes ) (struct hubp*,TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  CURSOR_CONTROL ; 
 int /*<<< orphan*/  CURSOR_DST_OFFSET ; 
 int /*<<< orphan*/  CURSOR_DST_X_OFFSET ; 
 int /*<<< orphan*/  CURSOR_ENABLE ; 
 int /*<<< orphan*/  CURSOR_HOT_SPOT ; 
 int /*<<< orphan*/  CURSOR_HOT_SPOT_X ; 
 int /*<<< orphan*/  CURSOR_HOT_SPOT_Y ; 
 int /*<<< orphan*/  CURSOR_POSITION ; 
 int /*<<< orphan*/  CURSOR_SURFACE_ADDRESS ; 
 int /*<<< orphan*/  CURSOR_X_POSITION ; 
 int /*<<< orphan*/  CURSOR_Y_POSITION ; 
 scalar_t__ REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ROTATION_ANGLE_270 ; 
 scalar_t__ ROTATION_ANGLE_90 ; 
 struct dcn10_hubp* TO_DCN10_HUBP (struct hubp*) ; 
 int /*<<< orphan*/  dc_fixpt_div (int /*<<< orphan*/ ,TYPE_5__) ; 
 int dc_fixpt_floor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_fixpt_from_int (int) ; 
 int /*<<< orphan*/  stub1 (struct hubp*,TYPE_4__*) ; 

void hubp1_cursor_set_position(
		struct hubp *hubp,
		const struct dc_cursor_position *pos,
		const struct dc_cursor_mi_param *param)
{
	struct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	int src_x_offset = pos->x - pos->x_hotspot - param->viewport.x;
	int src_y_offset = pos->y - pos->y_hotspot - param->viewport.y;
	int x_hotspot = pos->x_hotspot;
	int y_hotspot = pos->y_hotspot;
	uint32_t dst_x_offset;
	uint32_t cur_en = pos->enable ? 1 : 0;

	/*
	 * Guard aganst cursor_set_position() from being called with invalid
	 * attributes
	 *
	 * TODO: Look at combining cursor_set_position() and
	 * cursor_set_attributes() into cursor_update()
	 */
	if (hubp->curs_attr.address.quad_part == 0)
		return;

	if (param->rotation == ROTATION_ANGLE_90 || param->rotation == ROTATION_ANGLE_270) {
		src_x_offset = pos->y - pos->y_hotspot - param->viewport.x;
		y_hotspot = pos->x_hotspot;
		x_hotspot = pos->y_hotspot;
	}

	if (param->mirror) {
		x_hotspot = param->viewport.width - x_hotspot;
		src_x_offset = param->viewport.x + param->viewport.width - src_x_offset;
	}

	dst_x_offset = (src_x_offset >= 0) ? src_x_offset : 0;
	dst_x_offset *= param->ref_clk_khz;
	dst_x_offset /= param->pixel_clk_khz;

	ASSERT(param->h_scale_ratio.value);

	if (param->h_scale_ratio.value)
		dst_x_offset = dc_fixpt_floor(dc_fixpt_div(
				dc_fixpt_from_int(dst_x_offset),
				param->h_scale_ratio));

	if (src_x_offset >= (int)param->viewport.width)
		cur_en = 0;  /* not visible beyond right edge*/

	if (src_x_offset + (int)hubp->curs_attr.width <= 0)
		cur_en = 0;  /* not visible beyond left edge*/

	if (src_y_offset >= (int)param->viewport.height)
		cur_en = 0;  /* not visible beyond bottom edge*/

	if (src_y_offset + (int)hubp->curs_attr.height <= 0)
		cur_en = 0;  /* not visible beyond top edge*/

	if (cur_en && REG_READ(CURSOR_SURFACE_ADDRESS) == 0)
		hubp->funcs->set_cursor_attributes(hubp, &hubp->curs_attr);

	REG_UPDATE(CURSOR_CONTROL,
			CURSOR_ENABLE, cur_en);

	REG_SET_2(CURSOR_POSITION, 0,
			CURSOR_X_POSITION, pos->x,
			CURSOR_Y_POSITION, pos->y);

	REG_SET_2(CURSOR_HOT_SPOT, 0,
			CURSOR_HOT_SPOT_X, x_hotspot,
			CURSOR_HOT_SPOT_Y, y_hotspot);

	REG_SET(CURSOR_DST_OFFSET, 0,
			CURSOR_DST_X_OFFSET, dst_x_offset);
	/* TODO Handle surface pixel formats other than 4:4:4 */
}