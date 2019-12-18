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
typedef  int uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/ * transmitter_control; } ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;

/* Variables and functions */
 int BIOS_CMD_TABLE_REVISION (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  dig1transmittercontrol ; 
 int /*<<< orphan*/  dm_output_to_console (char*,int) ; 
 int /*<<< orphan*/ * transmitter_control_v1_6 ; 

__attribute__((used)) static void init_transmitter_control(struct bios_parser *bp)
{
	uint8_t frev;
	uint8_t crev;

	if (BIOS_CMD_TABLE_REVISION(dig1transmittercontrol, frev, crev) == false)
		BREAK_TO_DEBUGGER();
	switch (crev) {
	case 6:
		bp->cmd_tbl.transmitter_control = transmitter_control_v1_6;
		break;
	default:
		dm_output_to_console("Don't have transmitter_control for v%d\n", crev);
		bp->cmd_tbl.transmitter_control = NULL;
		break;
	}
}