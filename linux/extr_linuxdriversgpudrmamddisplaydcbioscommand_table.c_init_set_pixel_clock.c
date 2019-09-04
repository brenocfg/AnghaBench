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
struct TYPE_2__ {int /*<<< orphan*/ * set_pixel_clock; } ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;

/* Variables and functions */
 int BIOS_CMD_TABLE_PARA_REVISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPixelClock ; 
 int /*<<< orphan*/  dm_output_to_console (char*,int) ; 
 int /*<<< orphan*/ * set_pixel_clock_v3 ; 
 int /*<<< orphan*/ * set_pixel_clock_v5 ; 
 int /*<<< orphan*/ * set_pixel_clock_v6 ; 
 int /*<<< orphan*/ * set_pixel_clock_v7 ; 

__attribute__((used)) static void init_set_pixel_clock(struct bios_parser *bp)
{
	switch (BIOS_CMD_TABLE_PARA_REVISION(SetPixelClock)) {
	case 3:
		bp->cmd_tbl.set_pixel_clock = set_pixel_clock_v3;
		break;
	case 5:
		bp->cmd_tbl.set_pixel_clock = set_pixel_clock_v5;
		break;
	case 6:
		bp->cmd_tbl.set_pixel_clock = set_pixel_clock_v6;
		break;
	case 7:
		bp->cmd_tbl.set_pixel_clock = set_pixel_clock_v7;
		break;
	default:
		dm_output_to_console("Don't have set_pixel_clock for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(SetPixelClock));
		bp->cmd_tbl.set_pixel_clock = NULL;
		break;
	}
}