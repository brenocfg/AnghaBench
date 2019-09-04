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
struct cmd_tbl {int (* encoder_control_dig1 ) (struct bios_parser*,struct bp_encoder_control*) ;int (* encoder_control_dig2 ) (struct bios_parser*,struct bp_encoder_control*) ;} ;
struct bp_encoder_control {int engine_id; } ;
struct bios_parser {struct cmd_tbl cmd_tbl; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;

/* Variables and functions */
 int BP_RESULT_FAILURE ; 
#define  ENGINE_ID_DIGA 129 
#define  ENGINE_ID_DIGB 128 
 int stub1 (struct bios_parser*,struct bp_encoder_control*) ; 
 int stub2 (struct bios_parser*,struct bp_encoder_control*) ; 

__attribute__((used)) static enum bp_result encoder_control_dig_v1(
	struct bios_parser *bp,
	struct bp_encoder_control *cntl)
{
	enum bp_result result = BP_RESULT_FAILURE;
	struct cmd_tbl *cmd_tbl = &bp->cmd_tbl;

	if (cntl != NULL)
		switch (cntl->engine_id) {
		case ENGINE_ID_DIGA:
			if (cmd_tbl->encoder_control_dig1 != NULL)
				result =
					cmd_tbl->encoder_control_dig1(bp, cntl);
			break;
		case ENGINE_ID_DIGB:
			if (cmd_tbl->encoder_control_dig2 != NULL)
				result =
					cmd_tbl->encoder_control_dig2(bp, cntl);
			break;

		default:
			break;
		}

	return result;
}