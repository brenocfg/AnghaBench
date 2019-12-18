#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  enum tegra_io_pad { ____Placeholder_tegra_io_pad } tegra_io_pad ;
struct TYPE_6__ {int /*<<< orphan*/  powergates_lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IO_DPD_REQ_CODE_OFF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* pmc ; 
 int tegra_io_pad_poll (TYPE_1__*,unsigned long,int,int /*<<< orphan*/ ,int) ; 
 int tegra_io_pad_prepare (TYPE_1__*,int,unsigned long*,unsigned long*,int*) ; 
 int /*<<< orphan*/  tegra_io_pad_unprepare (TYPE_1__*) ; 
 int /*<<< orphan*/  tegra_pmc_writel (TYPE_1__*,int,unsigned long) ; 

int tegra_io_pad_power_enable(enum tegra_io_pad id)
{
	unsigned long request, status;
	u32 mask;
	int err;

	mutex_lock(&pmc->powergates_lock);

	err = tegra_io_pad_prepare(pmc, id, &request, &status, &mask);
	if (err < 0) {
		dev_err(pmc->dev, "failed to prepare I/O pad: %d\n", err);
		goto unlock;
	}

	tegra_pmc_writel(pmc, IO_DPD_REQ_CODE_OFF | mask, request);

	err = tegra_io_pad_poll(pmc, status, mask, 0, 250);
	if (err < 0) {
		dev_err(pmc->dev, "failed to enable I/O pad: %d\n", err);
		goto unlock;
	}

	tegra_io_pad_unprepare(pmc);

unlock:
	mutex_unlock(&pmc->powergates_lock);
	return err;
}