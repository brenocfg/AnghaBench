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
struct qoriq_tmu_data {int /*<<< orphan*/  clk; TYPE_1__* regs; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tmr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMR_DISABLE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct qoriq_tmu_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmu_write (struct qoriq_tmu_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qoriq_tmu_remove(struct platform_device *pdev)
{
	struct qoriq_tmu_data *data = platform_get_drvdata(pdev);

	/* Disable monitoring */
	tmu_write(data, TMR_DISABLE, &data->regs->tmr);

	clk_disable_unprepare(data->clk);

	platform_set_drvdata(pdev, NULL);

	return 0;
}