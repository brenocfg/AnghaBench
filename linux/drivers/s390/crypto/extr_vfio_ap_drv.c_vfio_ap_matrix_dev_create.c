#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; struct device* parent; } ;
struct TYPE_8__ {TYPE_1__ device; int /*<<< orphan*/ * vfio_ap_drv; int /*<<< orphan*/  mdev_list; int /*<<< orphan*/  lock; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  VFIO_AP_DEV_NAME ; 
 int /*<<< orphan*/  VFIO_AP_ROOT_NAME ; 
 int ap_qci (int /*<<< orphan*/ *) ; 
 int bus_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int driver_register (int /*<<< orphan*/ *) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_bus ; 
 TYPE_2__* matrix_dev ; 
 int /*<<< orphan*/  matrix_driver ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 struct device* root_device_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  root_device_unregister (struct device*) ; 
 scalar_t__ test_facility (int) ; 
 int /*<<< orphan*/  vfio_ap_drv ; 
 int /*<<< orphan*/  vfio_ap_matrix_dev_release ; 

__attribute__((used)) static int vfio_ap_matrix_dev_create(void)
{
	int ret;
	struct device *root_device;

	root_device = root_device_register(VFIO_AP_ROOT_NAME);
	if (IS_ERR(root_device))
		return PTR_ERR(root_device);

	ret = bus_register(&matrix_bus);
	if (ret)
		goto bus_register_err;

	matrix_dev = kzalloc(sizeof(*matrix_dev), GFP_KERNEL);
	if (!matrix_dev) {
		ret = -ENOMEM;
		goto matrix_alloc_err;
	}

	/* Fill in config info via PQAP(QCI), if available */
	if (test_facility(12)) {
		ret = ap_qci(&matrix_dev->info);
		if (ret)
			goto matrix_alloc_err;
	}

	mutex_init(&matrix_dev->lock);
	INIT_LIST_HEAD(&matrix_dev->mdev_list);

	dev_set_name(&matrix_dev->device, "%s", VFIO_AP_DEV_NAME);
	matrix_dev->device.parent = root_device;
	matrix_dev->device.bus = &matrix_bus;
	matrix_dev->device.release = vfio_ap_matrix_dev_release;
	matrix_dev->vfio_ap_drv = &vfio_ap_drv;

	ret = device_register(&matrix_dev->device);
	if (ret)
		goto matrix_reg_err;

	ret = driver_register(&matrix_driver);
	if (ret)
		goto matrix_drv_err;

	return 0;

matrix_drv_err:
	device_unregister(&matrix_dev->device);
matrix_reg_err:
	put_device(&matrix_dev->device);
matrix_alloc_err:
	bus_unregister(&matrix_bus);
bus_register_err:
	root_device_unregister(root_device);
	return ret;
}