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
struct TYPE_2__ {int /*<<< orphan*/ * adjust_display_pll; } ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustDisplayPll ; 
 int BIOS_CMD_TABLE_PARA_REVISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * adjust_display_pll_v2 ; 
 int /*<<< orphan*/ * adjust_display_pll_v3 ; 
 int /*<<< orphan*/  dm_output_to_console (char*,int) ; 

__attribute__((used)) static void init_adjust_display_pll(struct bios_parser *bp)
{
	switch (BIOS_CMD_TABLE_PARA_REVISION(AdjustDisplayPll)) {
	case 2:
		bp->cmd_tbl.adjust_display_pll = adjust_display_pll_v2;
		break;
	case 3:
		bp->cmd_tbl.adjust_display_pll = adjust_display_pll_v3;
		break;
	default:
		dm_output_to_console("Don't have adjust_display_pll for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(AdjustDisplayPll));
		bp->cmd_tbl.adjust_display_pll = NULL;
		break;
	}
}