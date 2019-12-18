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
struct qmp_cooling_device {char* name; int /*<<< orphan*/  cdev; int /*<<< orphan*/  state; struct qmp* qmp; } ;
struct qmp {int /*<<< orphan*/  dev; } ;
struct device_node {scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  devm_thermal_of_cooling_device_register (int /*<<< orphan*/ ,struct device_node*,char*,struct qmp_cooling_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmp_cdev_init_state ; 
 int /*<<< orphan*/  qmp_cooling_device_ops ; 

__attribute__((used)) static int qmp_cooling_device_add(struct qmp *qmp,
				  struct qmp_cooling_device *qmp_cdev,
				  struct device_node *node)
{
	char *cdev_name = (char *)node->name;

	qmp_cdev->qmp = qmp;
	qmp_cdev->state = qmp_cdev_init_state;
	qmp_cdev->name = cdev_name;
	qmp_cdev->cdev = devm_thermal_of_cooling_device_register
				(qmp->dev, node,
				cdev_name,
				qmp_cdev, &qmp_cooling_device_ops);

	if (IS_ERR(qmp_cdev->cdev))
		dev_err(qmp->dev, "unable to register %s cooling device\n",
			cdev_name);

	return PTR_ERR_OR_ZERO(qmp_cdev->cdev);
}