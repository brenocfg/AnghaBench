#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  remote_node; int /*<<< orphan*/  asd; } ;
struct stm32_dcmi {TYPE_2__ notifier; TYPE_6__* dev; int /*<<< orphan*/  v4l2_dev; TYPE_1__ entity; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcmi_graph_notify_ops ; 
 int dcmi_graph_parse (struct stm32_dcmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int v4l2_async_notifier_add_subdev (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_init (TYPE_2__*) ; 
 int v4l2_async_notifier_register (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int dcmi_graph_init(struct stm32_dcmi *dcmi)
{
	int ret;

	/* Parse the graph to extract a list of subdevice DT nodes. */
	ret = dcmi_graph_parse(dcmi, dcmi->dev->of_node);
	if (ret < 0) {
		dev_err(dcmi->dev, "Failed to parse graph\n");
		return ret;
	}

	v4l2_async_notifier_init(&dcmi->notifier);

	ret = v4l2_async_notifier_add_subdev(&dcmi->notifier,
					     &dcmi->entity.asd);
	if (ret) {
		dev_err(dcmi->dev, "Failed to add subdev notifier\n");
		of_node_put(dcmi->entity.remote_node);
		return ret;
	}

	dcmi->notifier.ops = &dcmi_graph_notify_ops;

	ret = v4l2_async_notifier_register(&dcmi->v4l2_dev, &dcmi->notifier);
	if (ret < 0) {
		dev_err(dcmi->dev, "Failed to register notifier\n");
		v4l2_async_notifier_cleanup(&dcmi->notifier);
		return ret;
	}

	return 0;
}