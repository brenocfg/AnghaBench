#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct bcm2835_gpiomem_instance {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  owner; } ;
struct TYPE_8__ {struct device* dev; int /*<<< orphan*/  gpio_regs_phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_MINOR ; 
 int /*<<< orphan*/  DEVICE_NAME ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_4__ bcm2835_gpiomem_cdev ; 
 void* bcm2835_gpiomem_class ; 
 void* bcm2835_gpiomem_dev ; 
 int /*<<< orphan*/  bcm2835_gpiomem_devid ; 
 int /*<<< orphan*/  bcm2835_gpiomem_fops ; 
 int cdev_add (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_4__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_4__*,int /*<<< orphan*/ *) ; 
 void* class_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_destroy (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* device_create (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* inst ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm2835_gpiomem_probe(struct platform_device *pdev)
{
	int err;
	void *ptr_err;
	struct device *dev = &pdev->dev;
	struct resource *ioresource;

	/* Allocate buffers and instance data */

	inst = kzalloc(sizeof(struct bcm2835_gpiomem_instance), GFP_KERNEL);

	if (!inst) {
		err = -ENOMEM;
		goto failed_inst_alloc;
	}

	inst->dev = dev;

	ioresource = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (ioresource) {
		inst->gpio_regs_phys = ioresource->start;
	} else {
		dev_err(inst->dev, "failed to get IO resource");
		err = -ENOENT;
		goto failed_get_resource;
	}

	/* Create character device entries */

	err = alloc_chrdev_region(&bcm2835_gpiomem_devid,
				  DEVICE_MINOR, 1, DEVICE_NAME);
	if (err != 0) {
		dev_err(inst->dev, "unable to allocate device number");
		goto failed_alloc_chrdev;
	}
	cdev_init(&bcm2835_gpiomem_cdev, &bcm2835_gpiomem_fops);
	bcm2835_gpiomem_cdev.owner = THIS_MODULE;
	err = cdev_add(&bcm2835_gpiomem_cdev, bcm2835_gpiomem_devid, 1);
	if (err != 0) {
		dev_err(inst->dev, "unable to register device");
		goto failed_cdev_add;
	}

	/* Create sysfs entries */

	bcm2835_gpiomem_class = class_create(THIS_MODULE, DEVICE_NAME);
	ptr_err = bcm2835_gpiomem_class;
	if (IS_ERR(ptr_err))
		goto failed_class_create;

	bcm2835_gpiomem_dev = device_create(bcm2835_gpiomem_class, NULL,
					bcm2835_gpiomem_devid, NULL,
					"gpiomem");
	ptr_err = bcm2835_gpiomem_dev;
	if (IS_ERR(ptr_err))
		goto failed_device_create;

	dev_info(inst->dev, "Initialised: Registers at 0x%08lx",
		inst->gpio_regs_phys);

	return 0;

failed_device_create:
	class_destroy(bcm2835_gpiomem_class);
failed_class_create:
	cdev_del(&bcm2835_gpiomem_cdev);
	err = PTR_ERR(ptr_err);
failed_cdev_add:
	unregister_chrdev_region(bcm2835_gpiomem_devid, 1);
failed_alloc_chrdev:
failed_get_resource:
	kfree(inst);
failed_inst_alloc:
	dev_err(inst->dev, "could not load bcm2835_gpiomem");
	return err;
}