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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * set_crtc_timing; } ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;

/* Variables and functions */
 int BIOS_CMD_TABLE_PARA_REVISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_output_to_console (char*,int) ; 
 int /*<<< orphan*/ * set_crtc_using_dtd_timing_v3 ; 
 int /*<<< orphan*/  setcrtc_usingdtdtiming ; 

__attribute__((used)) static void init_set_crtc_timing(struct bios_parser *bp)
{
	uint32_t dtd_version =
			BIOS_CMD_TABLE_PARA_REVISION(setcrtc_usingdtdtiming);

	switch (dtd_version) {
	case 3:
		bp->cmd_tbl.set_crtc_timing =
			set_crtc_using_dtd_timing_v3;
		break;
	default:
		dm_output_to_console("Don't have set_crtc_timing for v%d\n", dtd_version);
		bp->cmd_tbl.set_crtc_timing = NULL;
		break;
	}
}