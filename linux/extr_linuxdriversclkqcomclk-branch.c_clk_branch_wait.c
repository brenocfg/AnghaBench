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
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;
struct clk_branch {int halt_check; TYPE_1__ clkr; } ;

/* Variables and functions */
 int BRANCH_HALT ; 
 int BRANCH_HALT_DELAY ; 
 int BRANCH_HALT_ENABLE ; 
 int BRANCH_HALT_SKIP ; 
 int BRANCH_VOTED ; 
 int EBUSY ; 
 int /*<<< orphan*/  WARN (int,char*,char const*,char*) ; 
 scalar_t__ clk_branch_in_hwcg_mode (struct clk_branch const*) ; 
 char* clk_hw_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int clk_branch_wait(const struct clk_branch *br, bool enabling,
		bool (check_halt)(const struct clk_branch *, bool))
{
	bool voted = br->halt_check & BRANCH_VOTED;
	const char *name = clk_hw_get_name(&br->clkr.hw);

	/*
	 * Skip checking halt bit if we're explicitly ignoring the bit or the
	 * clock is in hardware gated mode
	 */
	if (br->halt_check == BRANCH_HALT_SKIP || clk_branch_in_hwcg_mode(br))
		return 0;

	if (br->halt_check == BRANCH_HALT_DELAY || (!enabling && voted)) {
		udelay(10);
	} else if (br->halt_check == BRANCH_HALT_ENABLE ||
		   br->halt_check == BRANCH_HALT ||
		   (enabling && voted)) {
		int count = 200;

		while (count-- > 0) {
			if (check_halt(br, enabling))
				return 0;
			udelay(1);
		}
		WARN(1, "%s status stuck at 'o%s'", name,
				enabling ? "ff" : "n");
		return -EBUSY;
	}
	return 0;
}