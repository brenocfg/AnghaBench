#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  owner; } ;
struct TYPE_7__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_MINOR ; 
 int /*<<< orphan*/  DEVICE_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_3__ bcm2835_smi_cdev ; 
 void* bcm2835_smi_class ; 
 void* bcm2835_smi_dev ; 
 int /*<<< orphan*/  bcm2835_smi_devid ; 
 int /*<<< orphan*/  bcm2835_smi_fops ; 
 int /*<<< orphan*/  bcm2835_smi_get (struct device_node*) ; 
 int cdev_add (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_3__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_3__*,int /*<<< orphan*/ *) ; 
 void* class_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_destroy (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 void* device_create (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* inst ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_inst ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm2835_smi_dev_probe(struct platform_device *pdev)
{
	int err;
	void *ptr_err;
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node, *smi_node;

	if (!node) {
		dev_err(dev, "No device tree node supplied!");
		return -EINVAL;
	}

	smi_node = of_parse_phandle(node, "smi_handle", 0);

	if (!smi_node) {
		dev_err(dev, "No such property: smi_handle");
		return -ENXIO;
	}

	smi_inst = bcm2835_smi_get(smi_node);

	if (!smi_inst)
		return -EPROBE_DEFER;

	/* Allocate buffers and instance data */

	inst = devm_kzalloc(dev, sizeof(*inst), GFP_KERNEL);

	if (!inst)
		return -ENOMEM;

	inst->dev = dev;

	/* Create character device entries */

	err = alloc_chrdev_region(&bcm2835_smi_devid,
				  DEVICE_MINOR, 1, DEVICE_NAME);
	if (err != 0) {
		dev_err(inst->dev, "unable to allocate device number");
		return -ENOMEM;
	}
	cdev_init(&bcm2835_smi_cdev, &bcm2835_smi_fops);
	bcm2835_smi_cdev.owner = THIS_MODULE;
	err = cdev_add(&bcm2835_smi_cdev, bcm2835_smi_devid, 1);
	if (err != 0) {
		dev_err(inst->dev, "unable to register device");
		err = -ENOMEM;
		goto failed_cdev_add;
	}

	/* Create sysfs entries */

	bcm2835_smi_class = class_create(THIS_MODULE, DEVICE_NAME);
	ptr_err = bcm2835_smi_class;
	if (IS_ERR(ptr_err))
		goto failed_class_create;

	bcm2835_smi_dev = device_create(bcm2835_smi_class, NULL,
					bcm2835_smi_devid, NULL,
					"smi");
	ptr_err = bcm2835_smi_dev;
	if (IS_ERR(ptr_err))
		goto failed_device_create;

	dev_info(inst->dev, "initialised");

	return 0;

failed_device_create:
	class_destroy(bcm2835_smi_class);
failed_class_create:
	cdev_del(&bcm2835_smi_cdev);
	err = PTR_ERR(ptr_err);
failed_cdev_add:
	unregister_chrdev_region(bcm2835_smi_devid, 1);
	dev_err(dev, "could not load bcm2835_smi_dev");
	return err;
}