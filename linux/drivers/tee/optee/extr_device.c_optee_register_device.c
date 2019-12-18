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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/ * bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  uuid; } ;
struct tee_client_device {TYPE_2__ dev; TYPE_1__ id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct tee_client_device*) ; 
 struct tee_client_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  tee_bus_type ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int optee_register_device(const uuid_t *device_uuid, u32 device_id)
{
	struct tee_client_device *optee_device = NULL;
	int rc;

	optee_device = kzalloc(sizeof(*optee_device), GFP_KERNEL);
	if (!optee_device)
		return -ENOMEM;

	optee_device->dev.bus = &tee_bus_type;
	dev_set_name(&optee_device->dev, "optee-clnt%u", device_id);
	uuid_copy(&optee_device->id.uuid, device_uuid);

	rc = device_register(&optee_device->dev);
	if (rc) {
		pr_err("device registration failed, err: %d\n", rc);
		kfree(optee_device);
	}

	return rc;
}