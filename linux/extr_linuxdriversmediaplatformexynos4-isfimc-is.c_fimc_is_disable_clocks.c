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
struct fimc_is {int /*<<< orphan*/ * clocks; } ;

/* Variables and functions */
 int ISS_GATE_CLKS_MAX ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fimc_is_clocks ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_is_disable_clocks(struct fimc_is *is)
{
	int i;

	for (i = 0; i < ISS_GATE_CLKS_MAX; i++) {
		if (!IS_ERR(is->clocks[i])) {
			clk_disable_unprepare(is->clocks[i]);
			pr_debug("disabled clock: %s\n", fimc_is_clocks[i]);
		}
	}
}