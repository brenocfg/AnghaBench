#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {scalar_t__ SET_EXTERNAL_REF_DIV_SRC; } ;
struct bp_pixel_clock_parameters {int target_pixel_clock_100hz; TYPE_2__ flags; int /*<<< orphan*/  pll_id; } ;
struct bios_parser {TYPE_1__* cmd_helper; } ;
typedef  int /*<<< orphan*/  params ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_9__ {int /*<<< orphan*/  ucMiscInfo; void* ucCRTC; int /*<<< orphan*/  usPixelClock; void* ucPpll; } ;
struct TYPE_10__ {TYPE_3__ sPCLKInput; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* clock_source_id_to_atom ) (int /*<<< orphan*/ ,scalar_t__*) ;} ;
typedef  TYPE_4__ SET_PIXEL_CLOCK_PS_ALLOCATION_V5 ;

/* Variables and functions */
 scalar_t__ ATOM_CRTC_INVALID ; 
 int BP_RESULT_BADINPUT ; 
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,TYPE_4__) ; 
 int /*<<< orphan*/  PIXEL_CLOCK_MISC_REF_DIV_SRC ; 
 int /*<<< orphan*/  SetPixelClock ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static enum bp_result program_clock_v5(
	struct bios_parser *bp,
	struct bp_pixel_clock_parameters *bp_params)
{
	enum bp_result result = BP_RESULT_FAILURE;

	SET_PIXEL_CLOCK_PS_ALLOCATION_V5 params;
	uint32_t atom_pll_id;

	memset(&params, 0, sizeof(params));
	if (!bp->cmd_helper->clock_source_id_to_atom(
			bp_params->pll_id, &atom_pll_id)) {
		BREAK_TO_DEBUGGER(); /* Invalid Inpute!! */
		return BP_RESULT_BADINPUT;
	}

	/* We need to convert from KHz units into 10KHz units */
	params.sPCLKInput.ucPpll = (uint8_t) atom_pll_id;
	params.sPCLKInput.usPixelClock =
			cpu_to_le16((uint16_t) (bp_params->target_pixel_clock_100hz / 100));
	params.sPCLKInput.ucCRTC = (uint8_t) ATOM_CRTC_INVALID;

	if (bp_params->flags.SET_EXTERNAL_REF_DIV_SRC)
		params.sPCLKInput.ucMiscInfo |= PIXEL_CLOCK_MISC_REF_DIV_SRC;

	if (EXEC_BIOS_CMD_TABLE(SetPixelClock, params))
		result = BP_RESULT_OK;

	return result;
}