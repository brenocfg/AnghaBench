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
struct TYPE_2__ {int /*<<< orphan*/ * enable_spread_spectrum_on_ppll; } ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;

/* Variables and functions */
 int BIOS_CMD_TABLE_PARA_REVISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableSpreadSpectrumOnPPLL ; 
 int /*<<< orphan*/  dm_output_to_console (char*,int) ; 
 int /*<<< orphan*/ * enable_spread_spectrum_on_ppll_v1 ; 
 int /*<<< orphan*/ * enable_spread_spectrum_on_ppll_v2 ; 
 int /*<<< orphan*/ * enable_spread_spectrum_on_ppll_v3 ; 

__attribute__((used)) static void init_enable_spread_spectrum_on_ppll(struct bios_parser *bp)
{
	switch (BIOS_CMD_TABLE_PARA_REVISION(EnableSpreadSpectrumOnPPLL)) {
	case 1:
		bp->cmd_tbl.enable_spread_spectrum_on_ppll =
				enable_spread_spectrum_on_ppll_v1;
		break;
	case 2:
		bp->cmd_tbl.enable_spread_spectrum_on_ppll =
				enable_spread_spectrum_on_ppll_v2;
		break;
	case 3:
		bp->cmd_tbl.enable_spread_spectrum_on_ppll =
				enable_spread_spectrum_on_ppll_v3;
		break;
	default:
		dm_output_to_console("Don't have enable_spread_spectrum_on_ppll for v%d\n",
			 BIOS_CMD_TABLE_PARA_REVISION(EnableSpreadSpectrumOnPPLL));
		bp->cmd_tbl.enable_spread_spectrum_on_ppll = NULL;
		break;
	}
}