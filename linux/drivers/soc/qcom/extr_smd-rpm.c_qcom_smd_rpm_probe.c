#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct rpmsg_device {TYPE_1__ dev; int /*<<< orphan*/  ept; } ;
struct qcom_smd_rpm {int /*<<< orphan*/  rpm_channel; TYPE_1__* dev; int /*<<< orphan*/  ack; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct qcom_smd_rpm*) ; 
 struct qcom_smd_rpm* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_platform_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int qcom_smd_rpm_probe(struct rpmsg_device *rpdev)
{
	struct qcom_smd_rpm *rpm;

	rpm = devm_kzalloc(&rpdev->dev, sizeof(*rpm), GFP_KERNEL);
	if (!rpm)
		return -ENOMEM;

	mutex_init(&rpm->lock);
	init_completion(&rpm->ack);

	rpm->dev = &rpdev->dev;
	rpm->rpm_channel = rpdev->ept;
	dev_set_drvdata(&rpdev->dev, rpm);

	return of_platform_populate(rpdev->dev.of_node, NULL, NULL, &rpdev->dev);
}