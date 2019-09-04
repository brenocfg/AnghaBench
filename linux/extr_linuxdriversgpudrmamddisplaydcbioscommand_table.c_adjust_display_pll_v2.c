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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct bp_adjust_pixel_clock_parameters {int pixel_clock; int /*<<< orphan*/  signal_type; int /*<<< orphan*/  encoder_object_id; } ;
struct bios_parser {TYPE_1__* cmd_helper; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_4__ {scalar_t__ ucEncodeMode; int /*<<< orphan*/  ucTransmitterID; int /*<<< orphan*/  usPixelClock; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {scalar_t__ (* encoder_mode_bp_to_atom ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* encoder_id_to_atom ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ ADJUST_DISPLAY_PLL_PS_ALLOCATION ;

/* Variables and functions */
 int BP_RESULT_FAILURE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dal_graphics_object_id_get_encoder_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum bp_result adjust_display_pll_v2(
	struct bios_parser *bp,
	struct bp_adjust_pixel_clock_parameters *bp_params)
{
	enum bp_result result = BP_RESULT_FAILURE;
	ADJUST_DISPLAY_PLL_PS_ALLOCATION params = { 0 };

	/* We need to convert from KHz units into 10KHz units and then convert
	 * output pixel clock back 10KHz-->KHz */
	uint32_t pixel_clock_10KHz_in = bp_params->pixel_clock / 10;

	params.usPixelClock = cpu_to_le16((uint16_t)(pixel_clock_10KHz_in));
	params.ucTransmitterID =
			bp->cmd_helper->encoder_id_to_atom(
					dal_graphics_object_id_get_encoder_id(
							bp_params->encoder_object_id));
	params.ucEncodeMode =
			(uint8_t)bp->cmd_helper->encoder_mode_bp_to_atom(
					bp_params->signal_type, false);
	return result;
}