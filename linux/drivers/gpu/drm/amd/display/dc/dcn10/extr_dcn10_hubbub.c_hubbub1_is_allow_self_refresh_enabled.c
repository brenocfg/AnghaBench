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
typedef  scalar_t__ uint32_t ;
struct hubbub {int dummy; } ;
struct dcn10_hubbub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_ENABLE ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DRAM_STATE_CNTL ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct dcn10_hubbub* TO_DCN10_HUBBUB (struct hubbub*) ; 

bool hubbub1_is_allow_self_refresh_enabled(struct hubbub *hubbub)
{
	struct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	uint32_t enable = 0;

	REG_GET(DCHUBBUB_ARB_DRAM_STATE_CNTL,
			DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_ENABLE, &enable);

	return enable ? true : false;
}