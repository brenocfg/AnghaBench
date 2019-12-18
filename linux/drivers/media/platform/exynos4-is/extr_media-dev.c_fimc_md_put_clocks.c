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
struct fimc_md {void** wbclk; TYPE_1__* camclk; } ;
struct TYPE_2__ {void* clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int FIMC_MAX_CAMCLKS ; 
 int FIMC_MAX_WBCLKS ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  clk_put (void*) ; 

__attribute__((used)) static void fimc_md_put_clocks(struct fimc_md *fmd)
{
	int i = FIMC_MAX_CAMCLKS;

	while (--i >= 0) {
		if (IS_ERR(fmd->camclk[i].clock))
			continue;
		clk_put(fmd->camclk[i].clock);
		fmd->camclk[i].clock = ERR_PTR(-EINVAL);
	}

	/* Writeback (PIXELASYNCMx) clocks */
	for (i = 0; i < FIMC_MAX_WBCLKS; i++) {
		if (IS_ERR(fmd->wbclk[i]))
			continue;
		clk_put(fmd->wbclk[i]);
		fmd->wbclk[i] = ERR_PTR(-EINVAL);
	}
}