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
struct dc_bios {int dummy; } ;
struct bp_encoder_control {int dummy; } ;
struct TYPE_2__ {int (* dig_encoder_control ) (struct bios_parser*,struct bp_encoder_control*) ;} ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;

/* Variables and functions */
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int BP_RESULT_FAILURE ; 
 int stub1 (struct bios_parser*,struct bp_encoder_control*) ; 

__attribute__((used)) static enum bp_result bios_parser_encoder_control(
	struct dc_bios *dcb,
	struct bp_encoder_control *cntl)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);

	if (!bp->cmd_tbl.dig_encoder_control)
		return BP_RESULT_FAILURE;

	return bp->cmd_tbl.dig_encoder_control(bp, cntl);
}