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
struct TYPE_3__ {int id; int /*<<< orphan*/  of_node; struct device* parent; int /*<<< orphan*/  class; } ;
struct fpga_region {int (* get_bridges ) (struct fpga_region*) ;TYPE_1__ dev; int /*<<< orphan*/  bridge_list; int /*<<< orphan*/  mutex; struct fpga_manager* mgr; } ;
struct fpga_manager {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int dev_set_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  fpga_region_class ; 
 int /*<<< orphan*/  fpga_region_ida ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct fpga_region*) ; 
 struct fpga_region* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct fpga_region
*fpga_region_create(struct device *dev,
		    struct fpga_manager *mgr,
		    int (*get_bridges)(struct fpga_region *))
{
	struct fpga_region *region;
	int id, ret = 0;

	region = kzalloc(sizeof(*region), GFP_KERNEL);
	if (!region)
		return NULL;

	id = ida_simple_get(&fpga_region_ida, 0, 0, GFP_KERNEL);
	if (id < 0)
		goto err_free;

	region->mgr = mgr;
	region->get_bridges = get_bridges;
	mutex_init(&region->mutex);
	INIT_LIST_HEAD(&region->bridge_list);

	device_initialize(&region->dev);
	region->dev.class = fpga_region_class;
	region->dev.parent = dev;
	region->dev.of_node = dev->of_node;
	region->dev.id = id;

	ret = dev_set_name(&region->dev, "region%d", id);
	if (ret)
		goto err_remove;

	return region;

err_remove:
	ida_simple_remove(&fpga_region_ida, id);
err_free:
	kfree(region);

	return NULL;
}