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
struct device {TYPE_1__* parent; } ;
struct rproc {struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  stop; int /*<<< orphan*/  start; } ;
struct qcom_rproc_subdev {TYPE_2__ subdev; struct device* dev; int /*<<< orphan*/  node; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rproc_add_subdev (struct rproc*,TYPE_2__*) ; 
 int /*<<< orphan*/  smd_subdev_start ; 
 int /*<<< orphan*/  smd_subdev_stop ; 

void qcom_add_smd_subdev(struct rproc *rproc, struct qcom_rproc_subdev *smd)
{
	struct device *dev = &rproc->dev;

	smd->node = of_get_child_by_name(dev->parent->of_node, "smd-edge");
	if (!smd->node)
		return;

	smd->dev = dev;
	smd->subdev.start = smd_subdev_start;
	smd->subdev.stop = smd_subdev_stop;

	rproc_add_subdev(rproc, &smd->subdev);
}