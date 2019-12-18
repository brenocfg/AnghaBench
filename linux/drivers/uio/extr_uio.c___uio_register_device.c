#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct uio_info {scalar_t__ irq; struct uio_device* uio_dev; int /*<<< orphan*/  name; int /*<<< orphan*/  irq_flags; int /*<<< orphan*/  version; } ;
struct TYPE_7__ {int /*<<< orphan*/  release; struct device* parent; int /*<<< orphan*/ * class; int /*<<< orphan*/  devt; } ;
struct uio_device {TYPE_1__ dev; int /*<<< orphan*/  minor; int /*<<< orphan*/  event; int /*<<< orphan*/  wait; int /*<<< orphan*/  info_lock; struct uio_info* info; struct module* owner; } ;
struct module {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UIO_IRQ_CUSTOM ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct uio_device*) ; 
 int dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_del (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct uio_device*) ; 
 struct uio_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio_device*) ; 
 int /*<<< orphan*/  uio_class ; 
 int /*<<< orphan*/  uio_class_registered ; 
 int uio_dev_add_attributes (struct uio_device*) ; 
 int /*<<< orphan*/  uio_dev_del_attributes (struct uio_device*) ; 
 int /*<<< orphan*/  uio_device_release ; 
 int /*<<< orphan*/  uio_free_minor (struct uio_device*) ; 
 int uio_get_minor (struct uio_device*) ; 
 int /*<<< orphan*/  uio_interrupt ; 
 int /*<<< orphan*/  uio_major ; 

int __uio_register_device(struct module *owner,
			  struct device *parent,
			  struct uio_info *info)
{
	struct uio_device *idev;
	int ret = 0;

	if (!uio_class_registered)
		return -EPROBE_DEFER;

	if (!parent || !info || !info->name || !info->version)
		return -EINVAL;

	info->uio_dev = NULL;

	idev = kzalloc(sizeof(*idev), GFP_KERNEL);
	if (!idev) {
		return -ENOMEM;
	}

	idev->owner = owner;
	idev->info = info;
	mutex_init(&idev->info_lock);
	init_waitqueue_head(&idev->wait);
	atomic_set(&idev->event, 0);

	ret = uio_get_minor(idev);
	if (ret) {
		kfree(idev);
		return ret;
	}

	device_initialize(&idev->dev);
	idev->dev.devt = MKDEV(uio_major, idev->minor);
	idev->dev.class = &uio_class;
	idev->dev.parent = parent;
	idev->dev.release = uio_device_release;
	dev_set_drvdata(&idev->dev, idev);

	ret = dev_set_name(&idev->dev, "uio%d", idev->minor);
	if (ret)
		goto err_device_create;

	ret = device_add(&idev->dev);
	if (ret)
		goto err_device_create;

	ret = uio_dev_add_attributes(idev);
	if (ret)
		goto err_uio_dev_add_attributes;

	info->uio_dev = idev;

	if (info->irq && (info->irq != UIO_IRQ_CUSTOM)) {
		/*
		 * Note that we deliberately don't use devm_request_irq
		 * here. The parent module can unregister the UIO device
		 * and call pci_disable_msi, which requires that this
		 * irq has been freed. However, the device may have open
		 * FDs at the time of unregister and therefore may not be
		 * freed until they are released.
		 */
		ret = request_irq(info->irq, uio_interrupt,
				  info->irq_flags, info->name, idev);
		if (ret) {
			info->uio_dev = NULL;
			goto err_request_irq;
		}
	}

	return 0;

err_request_irq:
	uio_dev_del_attributes(idev);
err_uio_dev_add_attributes:
	device_del(&idev->dev);
err_device_create:
	uio_free_minor(idev);
	put_device(&idev->dev);
	return ret;
}