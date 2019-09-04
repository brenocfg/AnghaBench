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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct dc_bios {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dac2_encoder_control ) (struct bios_parser*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dac2_output_control ) (struct bios_parser*,int) ;int /*<<< orphan*/  (* dac1_encoder_control ) (struct bios_parser*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dac1_output_control ) (struct bios_parser*,int) ;} ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;
typedef  enum engine_id { ____Placeholder_engine_id } engine_id ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DAC1_PS2 ; 
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
#define  ENGINE_ID_DACA 129 
#define  ENGINE_ID_DACB 128 
 int /*<<< orphan*/  stub1 (struct bios_parser*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct bios_parser*,int) ; 
 int /*<<< orphan*/  stub3 (struct bios_parser*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct bios_parser*,int) ; 
 int /*<<< orphan*/  stub5 (struct bios_parser*,int) ; 
 int /*<<< orphan*/  stub6 (struct bios_parser*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct bios_parser*,int) ; 
 int /*<<< orphan*/  stub8 (struct bios_parser*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bp_result bios_parser_crt_control(
	struct dc_bios *dcb,
	enum engine_id engine_id,
	bool enable,
	uint32_t pixel_clock)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);
	uint8_t standard;

	if (!bp->cmd_tbl.dac1_encoder_control &&
		engine_id == ENGINE_ID_DACA)
		return BP_RESULT_FAILURE;
	if (!bp->cmd_tbl.dac2_encoder_control &&
		engine_id == ENGINE_ID_DACB)
		return BP_RESULT_FAILURE;
	/* validate params */
	switch (engine_id) {
	case ENGINE_ID_DACA:
	case ENGINE_ID_DACB:
		break;
	default:
		/* unsupported engine */
		return BP_RESULT_FAILURE;
	}

	standard = ATOM_DAC1_PS2; /* == ATOM_DAC2_PS2 */

	if (enable) {
		if (engine_id == ENGINE_ID_DACA) {
			bp->cmd_tbl.dac1_encoder_control(bp, enable,
				pixel_clock, standard);
			if (bp->cmd_tbl.dac1_output_control != NULL)
				bp->cmd_tbl.dac1_output_control(bp, enable);
		} else {
			bp->cmd_tbl.dac2_encoder_control(bp, enable,
				pixel_clock, standard);
			if (bp->cmd_tbl.dac2_output_control != NULL)
				bp->cmd_tbl.dac2_output_control(bp, enable);
		}
	} else {
		if (engine_id == ENGINE_ID_DACA) {
			if (bp->cmd_tbl.dac1_output_control != NULL)
				bp->cmd_tbl.dac1_output_control(bp, enable);
			bp->cmd_tbl.dac1_encoder_control(bp, enable,
				pixel_clock, standard);
		} else {
			if (bp->cmd_tbl.dac2_output_control != NULL)
				bp->cmd_tbl.dac2_output_control(bp, enable);
			bp->cmd_tbl.dac2_encoder_control(bp, enable,
				pixel_clock, standard);
		}
	}

	return BP_RESULT_OK;
}