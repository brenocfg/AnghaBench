#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * driver; int /*<<< orphan*/  release; int /*<<< orphan*/  parent; int /*<<< orphan*/ * bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  instance; int /*<<< orphan*/  dev_index; int /*<<< orphan*/  prod_code; int /*<<< orphan*/  manf_id; } ;
struct slim_device {TYPE_2__ dev; TYPE_1__ e_addr; int /*<<< orphan*/  stream_list_lock; int /*<<< orphan*/  stream_list; struct slim_controller* ctrl; } ;
struct slim_controller {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  slim_dev_release ; 
 int /*<<< orphan*/  slimbus_bus ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int slim_add_device(struct slim_controller *ctrl,
			   struct slim_device *sbdev,
			   struct device_node *node)
{
	sbdev->dev.bus = &slimbus_bus;
	sbdev->dev.parent = ctrl->dev;
	sbdev->dev.release = slim_dev_release;
	sbdev->dev.driver = NULL;
	sbdev->ctrl = ctrl;
	INIT_LIST_HEAD(&sbdev->stream_list);
	spin_lock_init(&sbdev->stream_list_lock);

	if (node)
		sbdev->dev.of_node = of_node_get(node);

	dev_set_name(&sbdev->dev, "%x:%x:%x:%x",
				  sbdev->e_addr.manf_id,
				  sbdev->e_addr.prod_code,
				  sbdev->e_addr.dev_index,
				  sbdev->e_addr.instance);

	return device_register(&sbdev->dev);
}