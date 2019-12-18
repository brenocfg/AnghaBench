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
struct input_pixel_processor {int dummy; } ;
struct dce_ipp {int dummy; } ;
struct dc_cursor_position {int enable; int /*<<< orphan*/  y_hotspot; int /*<<< orphan*/  x_hotspot; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct dc_cursor_mi_param {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_EN ; 
 int /*<<< orphan*/  CURSOR_HOT_SPOT_X ; 
 int /*<<< orphan*/  CURSOR_HOT_SPOT_Y ; 
 int /*<<< orphan*/  CURSOR_UPDATE_LOCK ; 
 int /*<<< orphan*/  CURSOR_X_POSITION ; 
 int /*<<< orphan*/  CURSOR_Y_POSITION ; 
 int /*<<< orphan*/  CUR_CONTROL ; 
 int /*<<< orphan*/  CUR_HOT_SPOT ; 
 int /*<<< orphan*/  CUR_POSITION ; 
 int /*<<< orphan*/  CUR_UPDATE ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dce_ipp* TO_DCE_IPP (struct input_pixel_processor*) ; 

__attribute__((used)) static void dce_ipp_cursor_set_position(
	struct input_pixel_processor *ipp,
	const struct dc_cursor_position *position,
	const struct dc_cursor_mi_param *param)
{
	struct dce_ipp *ipp_dce = TO_DCE_IPP(ipp);

	/* lock cursor registers */
	REG_UPDATE(CUR_UPDATE, CURSOR_UPDATE_LOCK, true);

	/* Flag passed in structure differentiates cursor enable/disable. */
	/* Update if it differs from cached state. */
	REG_UPDATE(CUR_CONTROL, CURSOR_EN, position->enable);

	REG_SET_2(CUR_POSITION, 0,
		CURSOR_X_POSITION, position->x,
		CURSOR_Y_POSITION, position->y);

	REG_SET_2(CUR_HOT_SPOT, 0,
		CURSOR_HOT_SPOT_X, position->x_hotspot,
		CURSOR_HOT_SPOT_Y, position->y_hotspot);

	/* unlock cursor registers */
	REG_UPDATE(CUR_UPDATE, CURSOR_UPDATE_LOCK, false);
}