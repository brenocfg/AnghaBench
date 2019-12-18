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
struct dpp {int dummy; } ;
struct dcn10_dpp {int dummy; } ;
struct dc_cursor_attributes {int color_format; } ;
typedef  enum dc_cursor_color_format { ____Placeholder_dc_cursor_color_format } dc_cursor_color_format ;

/* Variables and functions */
 int /*<<< orphan*/  CUR0_COLOR0 ; 
 int /*<<< orphan*/  CUR0_COLOR1 ; 
 int /*<<< orphan*/  CUR0_EXPANSION_MODE ; 
 int /*<<< orphan*/  CUR0_MODE ; 
 int /*<<< orphan*/  CURSOR0_COLOR0 ; 
 int /*<<< orphan*/  CURSOR0_COLOR1 ; 
 int /*<<< orphan*/  CURSOR0_CONTROL ; 
 int CURSOR_MODE_MONO ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 

void dpp1_set_cursor_attributes(
		struct dpp *dpp_base,
		struct dc_cursor_attributes *cursor_attributes)
{
	enum dc_cursor_color_format color_format = cursor_attributes->color_format;
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_UPDATE_2(CURSOR0_CONTROL,
			CUR0_MODE, color_format,
			CUR0_EXPANSION_MODE, 0);

	if (color_format == CURSOR_MODE_MONO) {
		/* todo: clarify what to program these to */
		REG_UPDATE(CURSOR0_COLOR0,
				CUR0_COLOR0, 0x00000000);
		REG_UPDATE(CURSOR0_COLOR1,
				CUR0_COLOR1, 0xFFFFFFFF);
	}
}