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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct set_crtc_using_dtd_timing_parameters {void* modemiscinfo; void* v_syncoffset; void* v_syncwidth; void* h_syncwidth; void* h_syncoffset; void* v_blanking_time; void* v_size; void* h_blanking_time; void* h_size; int /*<<< orphan*/  crtc_id; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {scalar_t__ HSYNC_POSITIVE_POLARITY; scalar_t__ VSYNC_POSITIVE_POLARITY; scalar_t__ HORZ_COUNT_BY_TWO; scalar_t__ INTERLACE; } ;
struct bp_hw_crtc_timing_parameters {TYPE_2__ flags; scalar_t__ v_sync_width; scalar_t__ v_addressable; scalar_t__ v_sync_start; scalar_t__ h_sync_width; scalar_t__ h_addressable; scalar_t__ h_sync_start; scalar_t__ v_total; scalar_t__ h_total; int /*<<< orphan*/  controller_id; } ;
struct bios_parser {TYPE_1__* cmd_helper; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_3__ {scalar_t__ (* controller_id_to_atom ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ATOM_HSYNC_POLARITY ; 
 int ATOM_INTERLACE ; 
 int ATOM_VSYNC_POLARITY ; 
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,struct set_crtc_using_dtd_timing_parameters) ; 
 void* cpu_to_le16 (int) ; 
 int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  setcrtc_usingdtdtiming ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum bp_result set_crtc_using_dtd_timing_v3(
	struct bios_parser *bp,
	struct bp_hw_crtc_timing_parameters *bp_params)
{
	enum bp_result result = BP_RESULT_FAILURE;
	struct set_crtc_using_dtd_timing_parameters params = {0};
	uint8_t atom_controller_id;

	if (bp->cmd_helper->controller_id_to_atom(
			bp_params->controller_id, &atom_controller_id))
		params.crtc_id = atom_controller_id;

	/* bios usH_Size wants h addressable size */
	params.h_size = cpu_to_le16((uint16_t)bp_params->h_addressable);
	/* bios usH_Blanking_Time wants borders included in blanking */
	params.h_blanking_time =
			cpu_to_le16((uint16_t)(bp_params->h_total -
					bp_params->h_addressable));
	/* bios usV_Size wants v addressable size */
	params.v_size = cpu_to_le16((uint16_t)bp_params->v_addressable);
	/* bios usV_Blanking_Time wants borders included in blanking */
	params.v_blanking_time =
			cpu_to_le16((uint16_t)(bp_params->v_total -
					bp_params->v_addressable));
	/* bios usHSyncOffset is the offset from the end of h addressable,
	 * our horizontalSyncStart is the offset from the beginning
	 * of h addressable
	 */
	params.h_syncoffset =
			cpu_to_le16((uint16_t)(bp_params->h_sync_start -
					bp_params->h_addressable));
	params.h_syncwidth = cpu_to_le16((uint16_t)bp_params->h_sync_width);
	/* bios usHSyncOffset is the offset from the end of v addressable,
	 * our verticalSyncStart is the offset from the beginning of
	 * v addressable
	 */
	params.v_syncoffset =
			cpu_to_le16((uint16_t)(bp_params->v_sync_start -
					bp_params->v_addressable));
	params.v_syncwidth = cpu_to_le16((uint16_t)bp_params->v_sync_width);

	/* we assume that overscan from original timing does not get bigger
	 * than 255
	 * we will program all the borders in the Set CRTC Overscan call below
	 */

	if (bp_params->flags.HSYNC_POSITIVE_POLARITY == 0)
		params.modemiscinfo =
				cpu_to_le16(le16_to_cpu(params.modemiscinfo) |
						ATOM_HSYNC_POLARITY);

	if (bp_params->flags.VSYNC_POSITIVE_POLARITY == 0)
		params.modemiscinfo =
				cpu_to_le16(le16_to_cpu(params.modemiscinfo) |
						ATOM_VSYNC_POLARITY);

	if (bp_params->flags.INTERLACE)	{
		params.modemiscinfo =
				cpu_to_le16(le16_to_cpu(params.modemiscinfo) |
						ATOM_INTERLACE);

		/* original DAL code has this condition to apply this
		 * for non-TV/CV only
		 * due to complex MV testing for possible impact
		 * if ( pACParameters->signal != SignalType_YPbPr &&
		 *  pACParameters->signal != SignalType_Composite &&
		 *  pACParameters->signal != SignalType_SVideo)
		 */
		{
			/* HW will deduct 0.5 line from 2nd feild.
			 * i.e. for 1080i, it is 2 lines for 1st field,
			 * 2.5 lines for the 2nd feild. we need input as 5
			 * instead of 4.
			 * but it is 4 either from Edid data (spec CEA 861)
			 * or CEA timing table.
			 */
			params.v_syncoffset =
				cpu_to_le16(le16_to_cpu(params.v_syncoffset) +
						1);

		}
	}

	if (bp_params->flags.HORZ_COUNT_BY_TWO)
		params.modemiscinfo =
			cpu_to_le16(le16_to_cpu(params.modemiscinfo) |
					0x100); /* ATOM_DOUBLE_CLOCK_MODE */

	if (EXEC_BIOS_CMD_TABLE(setcrtc_usingdtdtiming, params))
		result = BP_RESULT_OK;

	return result;
}