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
struct TYPE_2__ {unsigned int (* get_smu_clock_info ) (struct bios_parser*,int /*<<< orphan*/ ) ;} ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;

/* Variables and functions */
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 unsigned int BP_RESULT_FAILURE ; 
 unsigned int stub1 (struct bios_parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int bios_parser_get_smu_clock_info(
	struct dc_bios *dcb)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);

	if (!bp->cmd_tbl.get_smu_clock_info)
		return BP_RESULT_FAILURE;

	return bp->cmd_tbl.get_smu_clock_info(bp, 0);
}