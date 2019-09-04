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
struct fimc_is {TYPE_1__* pdev; int /*<<< orphan*/ * clocks; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int ISS_CLKS_MAX ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fimc_is_clocks ; 
 int /*<<< orphan*/  fimc_is_put_clocks (struct fimc_is*) ; 

__attribute__((used)) static int fimc_is_get_clocks(struct fimc_is *is)
{
	int i, ret;

	for (i = 0; i < ISS_CLKS_MAX; i++)
		is->clocks[i] = ERR_PTR(-EINVAL);

	for (i = 0; i < ISS_CLKS_MAX; i++) {
		is->clocks[i] = clk_get(&is->pdev->dev, fimc_is_clocks[i]);
		if (IS_ERR(is->clocks[i])) {
			ret = PTR_ERR(is->clocks[i]);
			goto err;
		}
	}

	return 0;
err:
	fimc_is_put_clocks(is);
	dev_err(&is->pdev->dev, "failed to get clock: %s\n",
		fimc_is_clocks[i]);
	return ret;
}