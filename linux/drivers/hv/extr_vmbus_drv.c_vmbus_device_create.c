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
struct vmbus_channel {int dummy; } ;
struct hv_device {int vendor_id; int /*<<< orphan*/  dev_instance; int /*<<< orphan*/  dev_type; struct vmbus_channel* channel; } ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  guid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 struct hv_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

struct hv_device *vmbus_device_create(const guid_t *type,
				      const guid_t *instance,
				      struct vmbus_channel *channel)
{
	struct hv_device *child_device_obj;

	child_device_obj = kzalloc(sizeof(struct hv_device), GFP_KERNEL);
	if (!child_device_obj) {
		pr_err("Unable to allocate device object for child device\n");
		return NULL;
	}

	child_device_obj->channel = channel;
	guid_copy(&child_device_obj->dev_type, type);
	guid_copy(&child_device_obj->dev_instance, instance);
	child_device_obj->vendor_id = 0x1414; /* MSFT vendor ID */

	return child_device_obj;
}