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
struct vme_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/ * resource; scalar_t__ pci_buf; int /*<<< orphan*/ * kern_buf; void* size_buf; int /*<<< orphan*/ * device; int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
#define  CONTROL_MINOR 130 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int MASTER_MAX ; 
#define  MASTER_MINOR 129 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 void* PCI_BUF_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int SLAVE_MAX ; 
#define  SLAVE_MINOR 128 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  VME_A24 ; 
 int /*<<< orphan*/  VME_A32 ; 
 int /*<<< orphan*/  VME_D32 ; 
 int VME_DEVS ; 
 int /*<<< orphan*/  VME_MAJOR ; 
 int /*<<< orphan*/  VME_SCT ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* cdev_alloc () ; 
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/ * class_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * device_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  driver_name ; 
 TYPE_2__* image ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int register_chrdev_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int* type ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * vme_alloc_consistent (int /*<<< orphan*/ *,void*,scalar_t__*) ; 
 int /*<<< orphan*/  vme_free_consistent (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vme_master_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vme_master_request (struct vme_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vme_slave_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vme_slave_request (struct vme_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vme_dev* vme_user_bridge ; 
 TYPE_1__* vme_user_cdev ; 
 int /*<<< orphan*/  vme_user_fops ; 
 int /*<<< orphan*/ * vme_user_sysfs_class ; 

__attribute__((used)) static int vme_user_probe(struct vme_dev *vdev)
{
	int i, err;
	char *name;

	/* Save pointer to the bridge device */
	if (vme_user_bridge) {
		dev_err(&vdev->dev, "Driver can only be loaded for 1 device\n");
		err = -EINVAL;
		goto err_dev;
	}
	vme_user_bridge = vdev;

	/* Initialise descriptors */
	for (i = 0; i < VME_DEVS; i++) {
		image[i].kern_buf = NULL;
		image[i].pci_buf = 0;
		mutex_init(&image[i].mutex);
		image[i].device = NULL;
		image[i].resource = NULL;
	}

	/* Assign major and minor numbers for the driver */
	err = register_chrdev_region(MKDEV(VME_MAJOR, 0), VME_DEVS,
				     driver_name);
	if (err) {
		dev_warn(&vdev->dev, "Error getting Major Number %d for driver.\n",
			 VME_MAJOR);
		goto err_region;
	}

	/* Register the driver as a char device */
	vme_user_cdev = cdev_alloc();
	if (!vme_user_cdev) {
		err = -ENOMEM;
		goto err_char;
	}
	vme_user_cdev->ops = &vme_user_fops;
	vme_user_cdev->owner = THIS_MODULE;
	err = cdev_add(vme_user_cdev, MKDEV(VME_MAJOR, 0), VME_DEVS);
	if (err)
		goto err_class;

	/* Request slave resources and allocate buffers (128kB wide) */
	for (i = SLAVE_MINOR; i < (SLAVE_MAX + 1); i++) {
		/* XXX Need to properly request attributes */
		/* For ca91cx42 bridge there are only two slave windows
		 * supporting A16 addressing, so we request A24 supported
		 * by all windows.
		 */
		image[i].resource = vme_slave_request(vme_user_bridge,
						      VME_A24, VME_SCT);
		if (!image[i].resource) {
			dev_warn(&vdev->dev,
				 "Unable to allocate slave resource\n");
			err = -ENOMEM;
			goto err_slave;
		}
		image[i].size_buf = PCI_BUF_SIZE;
		image[i].kern_buf = vme_alloc_consistent(image[i].resource,
							 image[i].size_buf,
							 &image[i].pci_buf);
		if (!image[i].kern_buf) {
			dev_warn(&vdev->dev,
				 "Unable to allocate memory for buffer\n");
			image[i].pci_buf = 0;
			vme_slave_free(image[i].resource);
			err = -ENOMEM;
			goto err_slave;
		}
	}

	/*
	 * Request master resources allocate page sized buffers for small
	 * reads and writes
	 */
	for (i = MASTER_MINOR; i < (MASTER_MAX + 1); i++) {
		/* XXX Need to properly request attributes */
		image[i].resource = vme_master_request(vme_user_bridge,
						       VME_A32, VME_SCT,
						       VME_D32);
		if (!image[i].resource) {
			dev_warn(&vdev->dev,
				 "Unable to allocate master resource\n");
			err = -ENOMEM;
			goto err_master;
		}
		image[i].size_buf = PCI_BUF_SIZE;
		image[i].kern_buf = kmalloc(image[i].size_buf, GFP_KERNEL);
		if (!image[i].kern_buf) {
			err = -ENOMEM;
			vme_master_free(image[i].resource);
			goto err_master;
		}
	}

	/* Create sysfs entries - on udev systems this creates the dev files */
	vme_user_sysfs_class = class_create(THIS_MODULE, driver_name);
	if (IS_ERR(vme_user_sysfs_class)) {
		dev_err(&vdev->dev, "Error creating vme_user class.\n");
		err = PTR_ERR(vme_user_sysfs_class);
		goto err_master;
	}

	/* Add sysfs Entries */
	for (i = 0; i < VME_DEVS; i++) {
		int num;

		switch (type[i]) {
		case MASTER_MINOR:
			name = "bus/vme/m%d";
			break;
		case CONTROL_MINOR:
			name = "bus/vme/ctl";
			break;
		case SLAVE_MINOR:
			name = "bus/vme/s%d";
			break;
		default:
			err = -EINVAL;
			goto err_sysfs;
		}

		num = (type[i] == SLAVE_MINOR) ? i - (MASTER_MAX + 1) : i;
		image[i].device = device_create(vme_user_sysfs_class, NULL,
						MKDEV(VME_MAJOR, i), NULL,
						name, num);
		if (IS_ERR(image[i].device)) {
			dev_info(&vdev->dev, "Error creating sysfs device\n");
			err = PTR_ERR(image[i].device);
			goto err_sysfs;
		}
	}

	return 0;

err_sysfs:
	while (i > 0) {
		i--;
		device_destroy(vme_user_sysfs_class, MKDEV(VME_MAJOR, i));
	}
	class_destroy(vme_user_sysfs_class);

	/* Ensure counter set correctly to unalloc all master windows */
	i = MASTER_MAX + 1;
err_master:
	while (i > MASTER_MINOR) {
		i--;
		kfree(image[i].kern_buf);
		vme_master_free(image[i].resource);
	}

	/*
	 * Ensure counter set correctly to unalloc all slave windows and buffers
	 */
	i = SLAVE_MAX + 1;
err_slave:
	while (i > SLAVE_MINOR) {
		i--;
		vme_free_consistent(image[i].resource, image[i].size_buf,
				    image[i].kern_buf, image[i].pci_buf);
		vme_slave_free(image[i].resource);
	}
err_class:
	cdev_del(vme_user_cdev);
err_char:
	unregister_chrdev_region(MKDEV(VME_MAJOR, 0), VME_DEVS);
err_region:
err_dev:
	return err;
}