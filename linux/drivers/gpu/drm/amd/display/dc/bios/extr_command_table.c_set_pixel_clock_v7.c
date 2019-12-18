#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {scalar_t__ SET_GENLOCK_REF_DIV_SRC; scalar_t__ SET_XTALIN_REF_SRC; scalar_t__ SUPPORT_YUV_420; scalar_t__ PROGRAM_PHY_PLL_ONLY; scalar_t__ SET_EXTERNAL_REF_DIV_SRC; scalar_t__ FORCE_PROGRAMMING_OF_PLL; } ;
struct bp_pixel_clock_parameters {scalar_t__ signal_type; TYPE_2__ flags; int /*<<< orphan*/  color_depth; int /*<<< orphan*/  target_pixel_clock_100hz; int /*<<< orphan*/  encoder_object_id; int /*<<< orphan*/  controller_id; int /*<<< orphan*/  pll_id; } ;
struct bios_parser {TYPE_1__* cmd_helper; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
typedef  int /*<<< orphan*/  clk ;
struct TYPE_8__ {int /*<<< orphan*/  ucMiscInfo; void* ucDeepColorRatio; int /*<<< orphan*/  ulPixelClock; void* ucEncoderMode; int /*<<< orphan*/  ucTransmitterID; void* ucPpll; void* ucCRTC; } ;
struct TYPE_6__ {scalar_t__ (* transmitter_color_depth_to_atom ) (int /*<<< orphan*/ ) ;scalar_t__ (* encoder_mode_bp_to_atom ) (scalar_t__,int) ;int /*<<< orphan*/  (* encoder_id_to_atom ) (int /*<<< orphan*/ ) ;scalar_t__ (* controller_id_to_atom ) (int /*<<< orphan*/ ,void**) ;scalar_t__ (* clock_source_id_to_atom ) (int /*<<< orphan*/ ,scalar_t__*) ;} ;
typedef  TYPE_3__ PIXEL_CLOCK_PARAMETERS_V7 ;

/* Variables and functions */
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,TYPE_3__) ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V7_MISC_DVI_DUALLINK_EN ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V7_MISC_FORCE_PROG_PPLL ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V7_MISC_PROG_PHYPLL ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V7_MISC_REF_DIV_SRC ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V7_MISC_REF_DIV_SRC_GENLK ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V7_MISC_REF_DIV_SRC_XTALIN ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V7_MISC_YUV420_MODE ; 
 scalar_t__ SIGNAL_TYPE_DVI_DUAL_LINK ; 
 int /*<<< orphan*/  SetPixelClock ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dal_graphics_object_id_get_encoder_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (scalar_t__,int) ; 
 scalar_t__ stub5 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bp_result set_pixel_clock_v7(
	struct bios_parser *bp,
	struct bp_pixel_clock_parameters *bp_params)
{
	enum bp_result result = BP_RESULT_FAILURE;
	PIXEL_CLOCK_PARAMETERS_V7 clk;
	uint8_t controller_id;
	uint32_t pll_id;

	memset(&clk, 0, sizeof(clk));

	if (bp->cmd_helper->clock_source_id_to_atom(bp_params->pll_id, &pll_id)
			&& bp->cmd_helper->controller_id_to_atom(bp_params->controller_id, &controller_id)) {
		/* Note: VBIOS still wants to use ucCRTC name which is now
		 * 1 byte in ULONG
		 *typedef struct _CRTC_PIXEL_CLOCK_FREQ
		 *{
		 * target the pixel clock to drive the CRTC timing.
		 * ULONG ulPixelClock:24;
		 * 0 means disable PPLL/DCPLL. Expanded to 24 bits comparing to
		 * previous version.
		 * ATOM_CRTC1~6, indicate the CRTC controller to
		 * ULONG ucCRTC:8;
		 * drive the pixel clock. not used for DCPLL case.
		 *}CRTC_PIXEL_CLOCK_FREQ;
		 *union
		 *{
		 * pixel clock and CRTC id frequency
		 * CRTC_PIXEL_CLOCK_FREQ ulCrtcPclkFreq;
		 * ULONG ulDispEngClkFreq; dispclk frequency
		 *};
		 */
		clk.ucCRTC = controller_id;
		clk.ucPpll = (uint8_t) pll_id;
		clk.ucTransmitterID = bp->cmd_helper->encoder_id_to_atom(dal_graphics_object_id_get_encoder_id(bp_params->encoder_object_id));
		clk.ucEncoderMode = (uint8_t) bp->cmd_helper->encoder_mode_bp_to_atom(bp_params->signal_type, false);

		clk.ulPixelClock = cpu_to_le32(bp_params->target_pixel_clock_100hz);

		clk.ucDeepColorRatio = (uint8_t) bp->cmd_helper->transmitter_color_depth_to_atom(bp_params->color_depth);

		if (bp_params->flags.FORCE_PROGRAMMING_OF_PLL)
			clk.ucMiscInfo |= PIXEL_CLOCK_V7_MISC_FORCE_PROG_PPLL;

		if (bp_params->flags.SET_EXTERNAL_REF_DIV_SRC)
			clk.ucMiscInfo |= PIXEL_CLOCK_V7_MISC_REF_DIV_SRC;

		if (bp_params->flags.PROGRAM_PHY_PLL_ONLY)
			clk.ucMiscInfo |= PIXEL_CLOCK_V7_MISC_PROG_PHYPLL;

		if (bp_params->flags.SUPPORT_YUV_420)
			clk.ucMiscInfo |= PIXEL_CLOCK_V7_MISC_YUV420_MODE;

		if (bp_params->flags.SET_XTALIN_REF_SRC)
			clk.ucMiscInfo |= PIXEL_CLOCK_V7_MISC_REF_DIV_SRC_XTALIN;

		if (bp_params->flags.SET_GENLOCK_REF_DIV_SRC)
			clk.ucMiscInfo |= PIXEL_CLOCK_V7_MISC_REF_DIV_SRC_GENLK;

		if (bp_params->signal_type == SIGNAL_TYPE_DVI_DUAL_LINK)
			clk.ucMiscInfo |= PIXEL_CLOCK_V7_MISC_DVI_DUALLINK_EN;

		if (EXEC_BIOS_CMD_TABLE(SetPixelClock, clk))
			result = BP_RESULT_OK;
	}
	return result;
}