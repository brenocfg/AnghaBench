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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int ISS_CLKS_MAX ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_is_put_clocks(struct fimc_is *is)
{
	int i;

	for (i = 0; i < ISS_CLKS_MAX; i++) {
		if (IS_ERR(is->clocks[i]))
			continue;
		clk_put(is->clocks[i]);
		is->clocks[i] = ERR_PTR(-EINVAL);
	}
}