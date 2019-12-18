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
typedef  int uint32_t ;
struct hubbub {int dummy; } ;
struct dcn10_hubbub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBBUB_GLOBAL_SOFT_RESET ; 
 int /*<<< orphan*/  DCHUBBUB_SOFT_RESET ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn10_hubbub* TO_DCN10_HUBBUB (struct hubbub*) ; 

void hubbub1_soft_reset(struct hubbub *hubbub, bool reset)
{
	struct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	uint32_t reset_en = reset ? 1 : 0;

	REG_UPDATE(DCHUBBUB_SOFT_RESET,
			DCHUBBUB_GLOBAL_SOFT_RESET, reset_en);
}