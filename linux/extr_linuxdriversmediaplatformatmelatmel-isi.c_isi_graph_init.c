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
struct atmel_isi {TYPE_1__ entity; TYPE_3__* dev; TYPE_2__ notifier; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct v4l2_async_subdev** devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isi_graph_notify_ops ; 
 int isi_graph_parse (struct atmel_isi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int v4l2_async_notifier_register (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int isi_graph_init(struct atmel_isi *isi)
{
	struct v4l2_async_subdev **subdevs = NULL;
	int ret;

	/* Parse the graph to extract a list of subdevice DT nodes. */
	ret = isi_graph_parse(isi, isi->dev->of_node);
	if (ret < 0) {
		dev_err(isi->dev, "Graph parsing failed\n");
		return ret;
	}

	/* Register the subdevices notifier. */
	subdevs = devm_kzalloc(isi->dev, sizeof(*subdevs), GFP_KERNEL);
	if (!subdevs) {
		of_node_put(isi->entity.node);
		return -ENOMEM;
	}

	subdevs[0] = &isi->entity.asd;

	isi->notifier.subdevs = subdevs;
	isi->notifier.num_subdevs = 1;
	isi->notifier.ops = &isi_graph_notify_ops;

	ret = v4l2_async_notifier_register(&isi->v4l2_dev, &isi->notifier);
	if (ret < 0) {
		dev_err(isi->dev, "Notifier registration failed\n");
		of_node_put(isi->entity.node);
		return ret;
	}

	return 0;
}