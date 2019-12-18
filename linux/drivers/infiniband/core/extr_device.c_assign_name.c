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
typedef  int /*<<< orphan*/  u32 ;
struct ib_device {int /*<<< orphan*/  index; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENFILE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_DEVICE_NAME_MAX ; 
 scalar_t__ __ib_device_get_by_name (int /*<<< orphan*/ ) ; 
 int alloc_name (struct ib_device*,char const*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int dev_set_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  devices ; 
 int /*<<< orphan*/  devices_rwsem ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int xa_alloc_cyclic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_limit_31b ; 

__attribute__((used)) static int assign_name(struct ib_device *device, const char *name)
{
	static u32 last_id;
	int ret;

	down_write(&devices_rwsem);
	/* Assign a unique name to the device */
	if (strchr(name, '%'))
		ret = alloc_name(device, name);
	else
		ret = dev_set_name(&device->dev, name);
	if (ret)
		goto out;

	if (__ib_device_get_by_name(dev_name(&device->dev))) {
		ret = -ENFILE;
		goto out;
	}
	strlcpy(device->name, dev_name(&device->dev), IB_DEVICE_NAME_MAX);

	ret = xa_alloc_cyclic(&devices, &device->index, device, xa_limit_31b,
			&last_id, GFP_KERNEL);
	if (ret > 0)
		ret = 0;

out:
	up_write(&devices_rwsem);
	return ret;
}