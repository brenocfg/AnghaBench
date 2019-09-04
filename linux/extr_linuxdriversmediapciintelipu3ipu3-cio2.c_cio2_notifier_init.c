#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sensor_async_subdev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  num_subdevs; } ;
struct cio2_device {TYPE_2__ notifier; TYPE_1__* pci_dev; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  cio2_async_ops ; 
 int /*<<< orphan*/  cio2_fwnode_parse ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (TYPE_2__*) ; 
 int v4l2_async_notifier_parse_fwnode_endpoints (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int v4l2_async_notifier_register (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int cio2_notifier_init(struct cio2_device *cio2)
{
	int ret;

	ret = v4l2_async_notifier_parse_fwnode_endpoints(
		&cio2->pci_dev->dev, &cio2->notifier,
		sizeof(struct sensor_async_subdev),
		cio2_fwnode_parse);
	if (ret < 0)
		return ret;

	if (!cio2->notifier.num_subdevs)
		return -ENODEV;	/* no endpoint */

	cio2->notifier.ops = &cio2_async_ops;
	ret = v4l2_async_notifier_register(&cio2->v4l2_dev, &cio2->notifier);
	if (ret) {
		dev_err(&cio2->pci_dev->dev,
			"failed to register async notifier : %d\n", ret);
		v4l2_async_notifier_cleanup(&cio2->notifier);
	}

	return ret;
}