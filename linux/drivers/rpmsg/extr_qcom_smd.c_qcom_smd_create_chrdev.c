#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qcom_smd_edge {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct TYPE_4__ {TYPE_1__ dev; int /*<<< orphan*/ * ops; } ;
struct qcom_smd_device {TYPE_2__ rpdev; struct qcom_smd_edge* edge; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct qcom_smd_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_smd_device_ops ; 
 int /*<<< orphan*/  qcom_smd_release_device ; 
 int rpmsg_chrdev_register_device (TYPE_2__*) ; 

__attribute__((used)) static int qcom_smd_create_chrdev(struct qcom_smd_edge *edge)
{
	struct qcom_smd_device *qsdev;

	qsdev = kzalloc(sizeof(*qsdev), GFP_KERNEL);
	if (!qsdev)
		return -ENOMEM;

	qsdev->edge = edge;
	qsdev->rpdev.ops = &qcom_smd_device_ops;
	qsdev->rpdev.dev.parent = &edge->dev;
	qsdev->rpdev.dev.release = qcom_smd_release_device;

	return rpmsg_chrdev_register_device(&qsdev->rpdev);
}