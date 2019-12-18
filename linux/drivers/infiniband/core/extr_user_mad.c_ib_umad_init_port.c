#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* devt; } ;
struct TYPE_10__ {void* owner; } ;
struct ib_umad_port {int dev_num; int port_num; TYPE_1__ dev; TYPE_4__ cdev; TYPE_1__ sm_dev; TYPE_4__ sm_cdev; int /*<<< orphan*/  file_list; int /*<<< orphan*/  file_mutex; int /*<<< orphan*/  sm_sem; struct ib_umad_device* umad_dev; struct ib_device* ib_dev; } ;
struct ib_umad_device {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  void* dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_UMAD_MAX_PORTS ; 
 int IB_UMAD_NUM_FIXED_MINOR ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* THIS_MODULE ; 
 void* base_issm_dev ; 
 void* base_umad_dev ; 
 int cdev_device_add (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_device_del (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 void* dynamic_issm_dev ; 
 void* dynamic_umad_dev ; 
 int /*<<< orphan*/  ib_umad_init_port_dev (TYPE_1__*,struct ib_umad_port*,struct ib_device*) ; 
 int ida_alloc_max (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  umad_fops ; 
 int /*<<< orphan*/  umad_ida ; 
 int /*<<< orphan*/  umad_sm_fops ; 

__attribute__((used)) static int ib_umad_init_port(struct ib_device *device, int port_num,
			     struct ib_umad_device *umad_dev,
			     struct ib_umad_port *port)
{
	int devnum;
	dev_t base_umad;
	dev_t base_issm;
	int ret;

	devnum = ida_alloc_max(&umad_ida, IB_UMAD_MAX_PORTS - 1, GFP_KERNEL);
	if (devnum < 0)
		return -1;
	port->dev_num = devnum;
	if (devnum >= IB_UMAD_NUM_FIXED_MINOR) {
		base_umad = dynamic_umad_dev + devnum - IB_UMAD_NUM_FIXED_MINOR;
		base_issm = dynamic_issm_dev + devnum - IB_UMAD_NUM_FIXED_MINOR;
	} else {
		base_umad = devnum + base_umad_dev;
		base_issm = devnum + base_issm_dev;
	}

	port->ib_dev   = device;
	port->umad_dev = umad_dev;
	port->port_num = port_num;
	sema_init(&port->sm_sem, 1);
	mutex_init(&port->file_mutex);
	INIT_LIST_HEAD(&port->file_list);

	ib_umad_init_port_dev(&port->dev, port, device);
	port->dev.devt = base_umad;
	dev_set_name(&port->dev, "umad%d", port->dev_num);
	cdev_init(&port->cdev, &umad_fops);
	port->cdev.owner = THIS_MODULE;

	ret = cdev_device_add(&port->cdev, &port->dev);
	if (ret)
		goto err_cdev;

	ib_umad_init_port_dev(&port->sm_dev, port, device);
	port->sm_dev.devt = base_issm;
	dev_set_name(&port->sm_dev, "issm%d", port->dev_num);
	cdev_init(&port->sm_cdev, &umad_sm_fops);
	port->sm_cdev.owner = THIS_MODULE;

	ret = cdev_device_add(&port->sm_cdev, &port->sm_dev);
	if (ret)
		goto err_dev;

	return 0;

err_dev:
	put_device(&port->sm_dev);
	cdev_device_del(&port->cdev, &port->dev);
err_cdev:
	put_device(&port->dev);
	ida_free(&umad_ida, devnum);
	return ret;
}