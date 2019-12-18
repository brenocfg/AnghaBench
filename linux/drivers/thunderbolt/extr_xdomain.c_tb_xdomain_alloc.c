#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int /*<<< orphan*/  groups; int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; int /*<<< orphan*/  parent; } ;
struct tb_xdomain {int needs_uuid; struct tb_xdomain* local_uuid; TYPE_1__ dev; void* remote_uuid; int /*<<< orphan*/  properties_changed_work; int /*<<< orphan*/  get_properties_work; int /*<<< orphan*/  get_uuid_work; int /*<<< orphan*/  lock; int /*<<< orphan*/  service_ids; int /*<<< orphan*/  route; struct tb* tb; } ;
struct tb {int /*<<< orphan*/  index; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tb_xdomain*) ; 
 void* kmemdup (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 struct tb_xdomain* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_1__*) ; 
 int /*<<< orphan*/  tb_bus_type ; 
 int /*<<< orphan*/  tb_xdomain_get_properties ; 
 int /*<<< orphan*/  tb_xdomain_get_uuid ; 
 int /*<<< orphan*/  tb_xdomain_properties_changed ; 
 int /*<<< orphan*/  tb_xdomain_type ; 
 int /*<<< orphan*/  xdomain_attr_groups ; 

struct tb_xdomain *tb_xdomain_alloc(struct tb *tb, struct device *parent,
				    u64 route, const uuid_t *local_uuid,
				    const uuid_t *remote_uuid)
{
	struct tb_xdomain *xd;

	xd = kzalloc(sizeof(*xd), GFP_KERNEL);
	if (!xd)
		return NULL;

	xd->tb = tb;
	xd->route = route;
	ida_init(&xd->service_ids);
	mutex_init(&xd->lock);
	INIT_DELAYED_WORK(&xd->get_uuid_work, tb_xdomain_get_uuid);
	INIT_DELAYED_WORK(&xd->get_properties_work, tb_xdomain_get_properties);
	INIT_DELAYED_WORK(&xd->properties_changed_work,
			  tb_xdomain_properties_changed);

	xd->local_uuid = kmemdup(local_uuid, sizeof(uuid_t), GFP_KERNEL);
	if (!xd->local_uuid)
		goto err_free;

	if (remote_uuid) {
		xd->remote_uuid = kmemdup(remote_uuid, sizeof(uuid_t),
					  GFP_KERNEL);
		if (!xd->remote_uuid)
			goto err_free_local_uuid;
	} else {
		xd->needs_uuid = true;
	}

	device_initialize(&xd->dev);
	xd->dev.parent = get_device(parent);
	xd->dev.bus = &tb_bus_type;
	xd->dev.type = &tb_xdomain_type;
	xd->dev.groups = xdomain_attr_groups;
	dev_set_name(&xd->dev, "%u-%llx", tb->index, route);

	/*
	 * This keeps the DMA powered on as long as we have active
	 * connection to another host.
	 */
	pm_runtime_set_active(&xd->dev);
	pm_runtime_get_noresume(&xd->dev);
	pm_runtime_enable(&xd->dev);

	return xd;

err_free_local_uuid:
	kfree(xd->local_uuid);
err_free:
	kfree(xd);

	return NULL;
}