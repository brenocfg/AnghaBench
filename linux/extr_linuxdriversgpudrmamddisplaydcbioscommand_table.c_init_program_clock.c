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
struct TYPE_2__ {int /*<<< orphan*/ * program_clock; } ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;

/* Variables and functions */
 int BIOS_CMD_TABLE_PARA_REVISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPixelClock ; 
 int /*<<< orphan*/  dm_output_to_console (char*,int) ; 
 int /*<<< orphan*/ * program_clock_v5 ; 
 int /*<<< orphan*/ * program_clock_v6 ; 

__attribute__((used)) static void init_program_clock(struct bios_parser *bp)
{
	switch (BIOS_CMD_TABLE_PARA_REVISION(SetPixelClock)) {
	case 5:
		bp->cmd_tbl.program_clock = program_clock_v5;
		break;
	case 6:
		bp->cmd_tbl.program_clock = program_clock_v6;
		break;
	default:
		dm_output_to_console("Don't have program_clock for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(SetPixelClock));
		bp->cmd_tbl.program_clock = NULL;
		break;
	}
}