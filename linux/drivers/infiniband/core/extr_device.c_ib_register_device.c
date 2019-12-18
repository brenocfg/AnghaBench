#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {void (* dealloc_driver ) (struct ib_device*) ;} ;
struct ib_device {TYPE_2__ dev; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  __ib_unregister_device (struct ib_device*) ; 
 int assign_name (struct ib_device*,char const*) ; 
 int /*<<< orphan*/  dev_set_uevent_suppress (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_del (TYPE_2__*) ; 
 int enable_device_and_get (struct ib_device*) ; 
 int /*<<< orphan*/  ib_cache_cleanup_one (struct ib_device*) ; 
 int ib_cache_setup_one (struct ib_device*) ; 
 int /*<<< orphan*/  ib_device_put (struct ib_device*) ; 
 int /*<<< orphan*/  ib_device_register_rdmacg (struct ib_device*) ; 
 int ib_device_register_sysfs (struct ib_device*) ; 
 int /*<<< orphan*/  ib_device_unregister_rdmacg (struct ib_device*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_counter_init (struct ib_device*) ; 
 int setup_device (struct ib_device*) ; 

int ib_register_device(struct ib_device *device, const char *name)
{
	int ret;

	ret = assign_name(device, name);
	if (ret)
		return ret;

	ret = setup_device(device);
	if (ret)
		return ret;

	ret = ib_cache_setup_one(device);
	if (ret) {
		dev_warn(&device->dev,
			 "Couldn't set up InfiniBand P_Key/GID cache\n");
		return ret;
	}

	ib_device_register_rdmacg(device);

	rdma_counter_init(device);

	/*
	 * Ensure that ADD uevent is not fired because it
	 * is too early amd device is not initialized yet.
	 */
	dev_set_uevent_suppress(&device->dev, true);
	ret = device_add(&device->dev);
	if (ret)
		goto cg_cleanup;

	ret = ib_device_register_sysfs(device);
	if (ret) {
		dev_warn(&device->dev,
			 "Couldn't register device with driver model\n");
		goto dev_cleanup;
	}

	ret = enable_device_and_get(device);
	dev_set_uevent_suppress(&device->dev, false);
	/* Mark for userspace that device is ready */
	kobject_uevent(&device->dev.kobj, KOBJ_ADD);
	if (ret) {
		void (*dealloc_fn)(struct ib_device *);

		/*
		 * If we hit this error flow then we don't want to
		 * automatically dealloc the device since the caller is
		 * expected to call ib_dealloc_device() after
		 * ib_register_device() fails. This is tricky due to the
		 * possibility for a parallel unregistration along with this
		 * error flow. Since we have a refcount here we know any
		 * parallel flow is stopped in disable_device and will see the
		 * NULL pointers, causing the responsibility to
		 * ib_dealloc_device() to revert back to this thread.
		 */
		dealloc_fn = device->ops.dealloc_driver;
		device->ops.dealloc_driver = NULL;
		ib_device_put(device);
		__ib_unregister_device(device);
		device->ops.dealloc_driver = dealloc_fn;
		return ret;
	}
	ib_device_put(device);

	return 0;

dev_cleanup:
	device_del(&device->dev);
cg_cleanup:
	dev_set_uevent_suppress(&device->dev, false);
	ib_device_unregister_rdmacg(device);
	ib_cache_cleanup_one(device);
	return ret;
}