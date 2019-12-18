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
struct wcnss_ctrl {int /*<<< orphan*/  probe_work; int /*<<< orphan*/  cbc; int /*<<< orphan*/  ack; int /*<<< orphan*/  channel; int /*<<< orphan*/ * dev; } ;
struct rpmsg_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  ept; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct wcnss_ctrl*) ; 
 struct wcnss_ctrl* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcnss_async_probe ; 

__attribute__((used)) static int wcnss_ctrl_probe(struct rpmsg_device *rpdev)
{
	struct wcnss_ctrl *wcnss;

	wcnss = devm_kzalloc(&rpdev->dev, sizeof(*wcnss), GFP_KERNEL);
	if (!wcnss)
		return -ENOMEM;

	wcnss->dev = &rpdev->dev;
	wcnss->channel = rpdev->ept;

	init_completion(&wcnss->ack);
	init_completion(&wcnss->cbc);
	INIT_WORK(&wcnss->probe_work, wcnss_async_probe);

	dev_set_drvdata(&rpdev->dev, wcnss);

	schedule_work(&wcnss->probe_work);

	return 0;
}