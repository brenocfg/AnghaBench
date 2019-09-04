#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_async_subdev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  node; struct v4l2_async_subdev asd; } ;
struct TYPE_6__ {int num_subdevs; int /*<<< orphan*/ * ops; struct v4l2_async_subdev** subdevs; } ;
struct stm32_dcmi {TYPE_1__ entity; TYPE_3__* dev; TYPE_2__ notifier; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dcmi_graph_notify_ops ; 
 int dcmi_graph_parse (struct stm32_dcmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct v4l2_async_subdev** devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int v4l2_async_notifier_register (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int dcmi_graph_init(struct stm32_dcmi *dcmi)
{
	struct v4l2_async_subdev **subdevs = NULL;
	int ret;

	/* Parse the graph to extract a list of subdevice DT nodes. */
	ret = dcmi_graph_parse(dcmi, dcmi->dev->of_node);
	if (ret < 0) {
		dev_err(dcmi->dev, "Graph parsing failed\n");
		return ret;
	}

	/* Register the subdevices notifier. */
	subdevs = devm_kzalloc(dcmi->dev, sizeof(*subdevs), GFP_KERNEL);
	if (!subdevs) {
		of_node_put(dcmi->entity.node);
		return -ENOMEM;
	}

	subdevs[0] = &dcmi->entity.asd;

	dcmi->notifier.subdevs = subdevs;
	dcmi->notifier.num_subdevs = 1;
	dcmi->notifier.ops = &dcmi_graph_notify_ops;

	ret = v4l2_async_notifier_register(&dcmi->v4l2_dev, &dcmi->notifier);
	if (ret < 0) {
		dev_err(dcmi->dev, "Notifier registration failed\n");
		of_node_put(dcmi->entity.node);
		return ret;
	}

	return 0;
}