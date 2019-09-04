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
struct TYPE_2__ {int /*<<< orphan*/ * select_crtc_source; } ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;

/* Variables and functions */
 int BIOS_CMD_TABLE_PARA_REVISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectCRTC_Source ; 
 int /*<<< orphan*/  dm_output_to_console (char*,int) ; 
 int /*<<< orphan*/ * select_crtc_source_v2 ; 
 int /*<<< orphan*/ * select_crtc_source_v3 ; 

__attribute__((used)) static void init_select_crtc_source(struct bios_parser *bp)
{
	switch (BIOS_CMD_TABLE_PARA_REVISION(SelectCRTC_Source)) {
	case 2:
		bp->cmd_tbl.select_crtc_source = select_crtc_source_v2;
		break;
	case 3:
		bp->cmd_tbl.select_crtc_source = select_crtc_source_v3;
		break;
	default:
		dm_output_to_console("Don't select_crtc_source enable_crtc for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(SelectCRTC_Source));
		bp->cmd_tbl.select_crtc_source = NULL;
		break;
	}
}