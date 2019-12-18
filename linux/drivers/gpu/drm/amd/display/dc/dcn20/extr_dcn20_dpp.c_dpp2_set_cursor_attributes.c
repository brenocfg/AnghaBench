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
struct dpp {int dummy; } ;
struct dcn20_dpp {int dummy; } ;
struct TYPE_3__ {scalar_t__ ENABLE_CURSOR_DEGAMMA; } ;
struct TYPE_4__ {TYPE_1__ bits; } ;
struct dc_cursor_attributes {int color_format; TYPE_2__ attribute_flags; } ;
typedef  enum dc_cursor_color_format { ____Placeholder_dc_cursor_color_format } dc_cursor_color_format ;

/* Variables and functions */
 int /*<<< orphan*/  CUR0_COLOR0 ; 
 int /*<<< orphan*/  CUR0_COLOR1 ; 
 int /*<<< orphan*/  CUR0_EXPANSION_MODE ; 
 int /*<<< orphan*/  CUR0_MODE ; 
 int /*<<< orphan*/  CUR0_ROM_EN ; 
 int /*<<< orphan*/  CURSOR0_COLOR0 ; 
 int /*<<< orphan*/  CURSOR0_COLOR1 ; 
 int /*<<< orphan*/  CURSOR0_CONTROL ; 
 int CURSOR_MODE_COLOR_PRE_MULTIPLIED_ALPHA ; 
 int CURSOR_MODE_COLOR_UN_PRE_MULTIPLIED_ALPHA ; 
 int CURSOR_MODE_MONO ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 

void dpp2_set_cursor_attributes(
		struct dpp *dpp_base,
		struct dc_cursor_attributes *cursor_attributes)
{
	enum dc_cursor_color_format color_format = cursor_attributes->color_format;
	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);
	int cur_rom_en = 0;

	if (color_format == CURSOR_MODE_COLOR_PRE_MULTIPLIED_ALPHA ||
		color_format == CURSOR_MODE_COLOR_UN_PRE_MULTIPLIED_ALPHA) {
		if (cursor_attributes->attribute_flags.bits.ENABLE_CURSOR_DEGAMMA) {
			cur_rom_en = 1;
		}
	}

	REG_UPDATE_3(CURSOR0_CONTROL,
			CUR0_MODE, color_format,
			CUR0_EXPANSION_MODE, 0,
			CUR0_ROM_EN, cur_rom_en);

	if (color_format == CURSOR_MODE_MONO) {
		/* todo: clarify what to program these to */
		REG_UPDATE(CURSOR0_COLOR0,
				CUR0_COLOR0, 0x00000000);
		REG_UPDATE(CURSOR0_COLOR1,
				CUR0_COLOR1, 0xFFFFFFFF);
	}
}