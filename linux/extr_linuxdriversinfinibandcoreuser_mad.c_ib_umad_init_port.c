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
struct TYPE_7__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  kobj; void* owner; } ;
struct ib_umad_port {int dev_num; int port_num; TYPE_2__ cdev; TYPE_2__ sm_cdev; void* sm_dev; void* dev; int /*<<< orphan*/  file_list; int /*<<< orphan*/  file_mutex; int /*<<< orphan*/  sm_sem; struct ib_device* ib_dev; } ;
struct ib_umad_device {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct ib_device {TYPE_1__ dev; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int IB_UMAD_MAX_PORTS ; 
 int IB_UMAD_NUM_FIXED_MINOR ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (void*) ; 
 void* THIS_MODULE ; 
 scalar_t__ base_issm_dev ; 
 scalar_t__ base_umad_dev ; 
 scalar_t__ cdev_add (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_2__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdev_set_parent (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_ibdev ; 
 int /*<<< orphan*/  dev_attr_port ; 
 int /*<<< orphan*/  dev_map ; 
 void* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_umad_port*,char*,int) ; 
 scalar_t__ device_create_file (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dynamic_issm_dev ; 
 scalar_t__ dynamic_umad_dev ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kobject_set_name (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umad_class ; 
 int /*<<< orphan*/  umad_fops ; 
 int /*<<< orphan*/  umad_sm_fops ; 

__attribute__((used)) static int ib_umad_init_port(struct ib_device *device, int port_num,
			     struct ib_umad_device *umad_dev,
			     struct ib_umad_port *port)
{
	int devnum;
	dev_t base_umad;
	dev_t base_issm;

	devnum = find_first_zero_bit(dev_map, IB_UMAD_MAX_PORTS);
	if (devnum >= IB_UMAD_MAX_PORTS)
		return -1;
	port->dev_num = devnum;
	set_bit(devnum, dev_map);
	if (devnum >= IB_UMAD_NUM_FIXED_MINOR) {
		base_umad = dynamic_umad_dev + devnum - IB_UMAD_NUM_FIXED_MINOR;
		base_issm = dynamic_issm_dev + devnum - IB_UMAD_NUM_FIXED_MINOR;
	} else {
		base_umad = devnum + base_umad_dev;
		base_issm = devnum + base_issm_dev;
	}

	port->ib_dev   = device;
	port->port_num = port_num;
	sema_init(&port->sm_sem, 1);
	mutex_init(&port->file_mutex);
	INIT_LIST_HEAD(&port->file_list);

	cdev_init(&port->cdev, &umad_fops);
	port->cdev.owner = THIS_MODULE;
	cdev_set_parent(&port->cdev, &umad_dev->kobj);
	kobject_set_name(&port->cdev.kobj, "umad%d", port->dev_num);
	if (cdev_add(&port->cdev, base_umad, 1))
		goto err_cdev;

	port->dev = device_create(umad_class, device->dev.parent,
				  port->cdev.dev, port,
				  "umad%d", port->dev_num);
	if (IS_ERR(port->dev))
		goto err_cdev;

	if (device_create_file(port->dev, &dev_attr_ibdev))
		goto err_dev;
	if (device_create_file(port->dev, &dev_attr_port))
		goto err_dev;

	cdev_init(&port->sm_cdev, &umad_sm_fops);
	port->sm_cdev.owner = THIS_MODULE;
	cdev_set_parent(&port->sm_cdev, &umad_dev->kobj);
	kobject_set_name(&port->sm_cdev.kobj, "issm%d", port->dev_num);
	if (cdev_add(&port->sm_cdev, base_issm, 1))
		goto err_sm_cdev;

	port->sm_dev = device_create(umad_class, device->dev.parent,
				     port->sm_cdev.dev, port,
				     "issm%d", port->dev_num);
	if (IS_ERR(port->sm_dev))
		goto err_sm_cdev;

	if (device_create_file(port->sm_dev, &dev_attr_ibdev))
		goto err_sm_dev;
	if (device_create_file(port->sm_dev, &dev_attr_port))
		goto err_sm_dev;

	return 0;

err_sm_dev:
	device_destroy(umad_class, port->sm_cdev.dev);

err_sm_cdev:
	cdev_del(&port->sm_cdev);

err_dev:
	device_destroy(umad_class, port->cdev.dev);

err_cdev:
	cdev_del(&port->cdev);
	clear_bit(devnum, dev_map);

	return -1;
}