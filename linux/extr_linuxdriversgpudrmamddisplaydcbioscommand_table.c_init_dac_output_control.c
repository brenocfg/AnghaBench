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
struct TYPE_2__ {int /*<<< orphan*/ * dac2_output_control; int /*<<< orphan*/ * dac1_output_control; } ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;

/* Variables and functions */
 int BIOS_CMD_TABLE_PARA_REVISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DAC1OutputControl ; 
 int /*<<< orphan*/  DAC2OutputControl ; 
 int /*<<< orphan*/ * dac1_output_control_v1 ; 
 int /*<<< orphan*/ * dac2_output_control_v1 ; 

__attribute__((used)) static void init_dac_output_control(struct bios_parser *bp)
{
	switch (BIOS_CMD_TABLE_PARA_REVISION(DAC1OutputControl)) {
	case 1:
		bp->cmd_tbl.dac1_output_control = dac1_output_control_v1;
		break;
	default:
		bp->cmd_tbl.dac1_output_control = NULL;
		break;
	}
	switch (BIOS_CMD_TABLE_PARA_REVISION(DAC2OutputControl)) {
	case 1:
		bp->cmd_tbl.dac2_output_control = dac2_output_control_v1;
		break;
	default:
		bp->cmd_tbl.dac2_output_control = NULL;
		break;
	}
}