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
struct tg_color {int color_b_cb; int color_g_y; int color_r_cr; } ;
struct output_pixel_processor {int dummy; } ;
struct dcn20_opp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct tg_color const*) ; 
 int /*<<< orphan*/  DPG_COLOUR0_B_CB ; 
 int /*<<< orphan*/  DPG_COLOUR0_G_Y ; 
 int /*<<< orphan*/  DPG_COLOUR0_R_CR ; 
 int /*<<< orphan*/  DPG_COLOUR1_B_CB ; 
 int /*<<< orphan*/  DPG_COLOUR1_G_Y ; 
 int /*<<< orphan*/  DPG_COLOUR1_R_CR ; 
 int /*<<< orphan*/  DPG_COLOUR_B_CB ; 
 int /*<<< orphan*/  DPG_COLOUR_G_Y ; 
 int /*<<< orphan*/  DPG_COLOUR_R_CR ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct dcn20_opp* TO_DCN20_OPP (struct output_pixel_processor*) ; 

void opp2_dpg_set_blank_color(
		struct output_pixel_processor *opp,
		const struct tg_color *color)
{
	struct dcn20_opp *oppn20 = TO_DCN20_OPP(opp);

	/* 16-bit MSB aligned value. Bits 3:0 of this field are hardwired to ZERO */
	ASSERT(color);
	REG_SET_2(DPG_COLOUR_B_CB, 0,
			DPG_COLOUR1_B_CB, color->color_b_cb << 6,
			DPG_COLOUR0_B_CB, color->color_b_cb << 6);
	REG_SET_2(DPG_COLOUR_G_Y, 0,
			DPG_COLOUR1_G_Y, color->color_g_y << 6,
			DPG_COLOUR0_G_Y, color->color_g_y << 6);
	REG_SET_2(DPG_COLOUR_R_CR, 0,
			DPG_COLOUR1_R_CR, color->color_r_cr << 6,
			DPG_COLOUR0_R_CR, color->color_r_cr << 6);
}