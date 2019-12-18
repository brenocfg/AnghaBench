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
struct TYPE_2__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  asd_list; } ;
struct xvip_composite_device {int /*<<< orphan*/  dev; TYPE_1__ notifier; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int v4l2_async_notifier_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  xvip_graph_cleanup (struct xvip_composite_device*) ; 
 int xvip_graph_dma_init (struct xvip_composite_device*) ; 
 int /*<<< orphan*/  xvip_graph_notify_ops ; 
 int xvip_graph_parse (struct xvip_composite_device*) ; 

__attribute__((used)) static int xvip_graph_init(struct xvip_composite_device *xdev)
{
	int ret;

	/* Init the DMA channels. */
	ret = xvip_graph_dma_init(xdev);
	if (ret < 0) {
		dev_err(xdev->dev, "DMA initialization failed\n");
		goto done;
	}

	/* Parse the graph to extract a list of subdevice DT nodes. */
	ret = xvip_graph_parse(xdev);
	if (ret < 0) {
		dev_err(xdev->dev, "graph parsing failed\n");
		goto done;
	}

	if (list_empty(&xdev->notifier.asd_list)) {
		dev_err(xdev->dev, "no subdev found in graph\n");
		goto done;
	}

	/* Register the subdevices notifier. */
	xdev->notifier.ops = &xvip_graph_notify_ops;

	ret = v4l2_async_notifier_register(&xdev->v4l2_dev, &xdev->notifier);
	if (ret < 0) {
		dev_err(xdev->dev, "notifier registration failed\n");
		goto done;
	}

	ret = 0;

done:
	if (ret < 0)
		xvip_graph_cleanup(xdev);

	return ret;
}