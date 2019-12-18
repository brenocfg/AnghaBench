#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hubbub {int dummy; } ;
struct dcn10_hubbub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_ENABLE ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_VALUE ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DRAM_STATE_CNTL ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn10_hubbub* TO_DCN10_HUBBUB (struct hubbub*) ; 

void hubbub1_allow_self_refresh_control(struct hubbub *hubbub, bool allow)
{
	struct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	/*
	 * DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_ENABLE = 1 means do not allow stutter
	 * DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_ENABLE = 0 means allow stutter
	 */

	REG_UPDATE_2(DCHUBBUB_ARB_DRAM_STATE_CNTL,
			DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_VALUE, 0,
			DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_ENABLE, !allow);
}