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
struct fimc_dev {int /*<<< orphan*/ * clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_FIMC_CLOCKS ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_clk_put(struct fimc_dev *fimc)
{
	int i;
	for (i = 0; i < MAX_FIMC_CLOCKS; i++) {
		if (IS_ERR(fimc->clock[i]))
			continue;
		clk_unprepare(fimc->clock[i]);
		clk_put(fimc->clock[i]);
		fimc->clock[i] = ERR_PTR(-EINVAL);
	}
}