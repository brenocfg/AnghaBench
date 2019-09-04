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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct cmdq* chans; } ;
struct cmdq {struct cmdq* thread; TYPE_1__ mbox; int /*<<< orphan*/  clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct cmdq*) ; 
 int /*<<< orphan*/  mbox_controller_unregister (TYPE_1__*) ; 
 struct cmdq* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int cmdq_remove(struct platform_device *pdev)
{
	struct cmdq *cmdq = platform_get_drvdata(pdev);

	mbox_controller_unregister(&cmdq->mbox);
	clk_unprepare(cmdq->clock);

	if (cmdq->mbox.chans)
		devm_kfree(&pdev->dev, cmdq->mbox.chans);

	if (cmdq->thread)
		devm_kfree(&pdev->dev, cmdq->thread);

	devm_kfree(&pdev->dev, cmdq);

	return 0;
}