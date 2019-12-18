#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hv_vmbus_device_id {int dummy; } ;
struct hv_driver {int /*<<< orphan*/  id_table; int /*<<< orphan*/  name; } ;
struct hv_device {scalar_t__ driver_override; int /*<<< orphan*/  dev_type; } ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 struct hv_vmbus_device_id* hv_vmbus_dev_match (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct hv_vmbus_device_id* hv_vmbus_dynid_match (struct hv_driver*,int /*<<< orphan*/  const*) ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 struct hv_vmbus_device_id vmbus_device_null ; 

__attribute__((used)) static const struct hv_vmbus_device_id *hv_vmbus_get_id(struct hv_driver *drv,
							struct hv_device *dev)
{
	const guid_t *guid = &dev->dev_type;
	const struct hv_vmbus_device_id *id;

	/* When driver_override is set, only bind to the matching driver */
	if (dev->driver_override && strcmp(dev->driver_override, drv->name))
		return NULL;

	/* Look at the dynamic ids first, before the static ones */
	id = hv_vmbus_dynid_match(drv, guid);
	if (!id)
		id = hv_vmbus_dev_match(drv->id_table, guid);

	/* driver_override will always match, send a dummy id */
	if (!id && dev->driver_override)
		id = &vmbus_device_null;

	return id;
}