#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct endpoint_list {int /*<<< orphan*/  fifo; } ;
struct device_node {int dummy; } ;
struct component_match {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_KFIFO (int /*<<< orphan*/ ) ; 
 int component_master_add_with_match (TYPE_1__*,int /*<<< orphan*/ *,struct component_match*) ; 
 scalar_t__ kfifo_get (int /*<<< orphan*/ *,struct device_node**) ; 
 int /*<<< orphan*/  kfifo_put (int /*<<< orphan*/ *,struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int) ; 
 int sun4i_drv_add_endpoints (TYPE_1__*,struct endpoint_list*,struct component_match**,struct device_node*) ; 
 int /*<<< orphan*/  sun4i_drv_master_ops ; 

__attribute__((used)) static int sun4i_drv_probe(struct platform_device *pdev)
{
	struct component_match *match = NULL;
	struct device_node *np = pdev->dev.of_node, *endpoint;
	struct endpoint_list list;
	int i, ret, count = 0;

	INIT_KFIFO(list.fifo);

	for (i = 0;; i++) {
		struct device_node *pipeline = of_parse_phandle(np,
								"allwinner,pipelines",
								i);
		if (!pipeline)
			break;

		kfifo_put(&list.fifo, pipeline);
	}

	while (kfifo_get(&list.fifo, &endpoint)) {
		/* process this endpoint */
		ret = sun4i_drv_add_endpoints(&pdev->dev, &list, &match,
					      endpoint);

		/* sun4i_drv_add_endpoints can fail to allocate memory */
		if (ret < 0)
			return ret;

		count += ret;
	}

	if (count)
		return component_master_add_with_match(&pdev->dev,
						       &sun4i_drv_master_ops,
						       match);
	else
		return 0;
}