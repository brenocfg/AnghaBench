#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vmmdev_memory {int size; int /*<<< orphan*/  version; } ;
struct TYPE_3__ {void* minor; int /*<<< orphan*/ * fops; int /*<<< orphan*/  name; } ;
struct vbg_dev {int io_port; TYPE_1__ misc_device; TYPE_1__ misc_device_user; struct device* dev; struct vmmdev_memory* mmio; } ;
struct pci_device_id {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; struct device dev; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_NAME ; 
 int /*<<< orphan*/  DEVICE_NAME_USER ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 void* MISC_DYNAMIC_MINOR ; 
 int /*<<< orphan*/  VMMDEV_EVENT_MOUSE_POSITION_CHANGED ; 
 int /*<<< orphan*/  VMMDEV_MEMORY_VERSION ; 
 int /*<<< orphan*/  dev_attr_host_features ; 
 int /*<<< orphan*/  dev_attr_host_version ; 
 int /*<<< orphan*/  device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 struct vmmdev_memory* devm_ioremap (struct device*,int,int) ; 
 struct vbg_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vbg_dev*) ; 
 int /*<<< orphan*/ * devm_request_mem_region (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_request_region (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  misc_deregister (TYPE_1__*) ; 
 int misc_register (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int pci_resource_len (struct pci_dev*,int) ; 
 int pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct vbg_dev*) ; 
 int /*<<< orphan*/  vbg_core_exit (struct vbg_dev*) ; 
 int vbg_core_init (struct vbg_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbg_core_isr ; 
 int vbg_create_input_device (struct vbg_dev*) ; 
 int /*<<< orphan*/  vbg_err (char*,...) ; 
 struct vbg_dev* vbg_gdev ; 
 int /*<<< orphan*/  vbg_gdev_mutex ; 
 int /*<<< orphan*/  vbg_info (char*,void*,int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  vbg_misc_device_fops ; 
 int /*<<< orphan*/  vbg_misc_device_user_fops ; 

__attribute__((used)) static int vbg_pci_probe(struct pci_dev *pci, const struct pci_device_id *id)
{
	struct device *dev = &pci->dev;
	resource_size_t io, io_len, mmio, mmio_len;
	struct vmmdev_memory *vmmdev;
	struct vbg_dev *gdev;
	int ret;

	gdev = devm_kzalloc(dev, sizeof(*gdev), GFP_KERNEL);
	if (!gdev)
		return -ENOMEM;

	ret = pci_enable_device(pci);
	if (ret != 0) {
		vbg_err("vboxguest: Error enabling device: %d\n", ret);
		return ret;
	}

	ret = -ENODEV;

	io = pci_resource_start(pci, 0);
	io_len = pci_resource_len(pci, 0);
	if (!io || !io_len) {
		vbg_err("vboxguest: Error IO-port resource (0) is missing\n");
		goto err_disable_pcidev;
	}
	if (devm_request_region(dev, io, io_len, DEVICE_NAME) == NULL) {
		vbg_err("vboxguest: Error could not claim IO resource\n");
		ret = -EBUSY;
		goto err_disable_pcidev;
	}

	mmio = pci_resource_start(pci, 1);
	mmio_len = pci_resource_len(pci, 1);
	if (!mmio || !mmio_len) {
		vbg_err("vboxguest: Error MMIO resource (1) is missing\n");
		goto err_disable_pcidev;
	}

	if (devm_request_mem_region(dev, mmio, mmio_len, DEVICE_NAME) == NULL) {
		vbg_err("vboxguest: Error could not claim MMIO resource\n");
		ret = -EBUSY;
		goto err_disable_pcidev;
	}

	vmmdev = devm_ioremap(dev, mmio, mmio_len);
	if (!vmmdev) {
		vbg_err("vboxguest: Error ioremap failed; MMIO addr=%pap size=%pap\n",
			&mmio, &mmio_len);
		goto err_disable_pcidev;
	}

	/* Validate MMIO region version and size. */
	if (vmmdev->version != VMMDEV_MEMORY_VERSION ||
	    vmmdev->size < 32 || vmmdev->size > mmio_len) {
		vbg_err("vboxguest: Bogus VMMDev memory; version=%08x (expected %08x) size=%d (expected <= %d)\n",
			vmmdev->version, VMMDEV_MEMORY_VERSION,
			vmmdev->size, (int)mmio_len);
		goto err_disable_pcidev;
	}

	gdev->io_port = io;
	gdev->mmio = vmmdev;
	gdev->dev = dev;
	gdev->misc_device.minor = MISC_DYNAMIC_MINOR;
	gdev->misc_device.name = DEVICE_NAME;
	gdev->misc_device.fops = &vbg_misc_device_fops;
	gdev->misc_device_user.minor = MISC_DYNAMIC_MINOR;
	gdev->misc_device_user.name = DEVICE_NAME_USER;
	gdev->misc_device_user.fops = &vbg_misc_device_user_fops;

	ret = vbg_core_init(gdev, VMMDEV_EVENT_MOUSE_POSITION_CHANGED);
	if (ret)
		goto err_disable_pcidev;

	ret = vbg_create_input_device(gdev);
	if (ret) {
		vbg_err("vboxguest: Error creating input device: %d\n", ret);
		goto err_vbg_core_exit;
	}

	ret = devm_request_irq(dev, pci->irq, vbg_core_isr, IRQF_SHARED,
			       DEVICE_NAME, gdev);
	if (ret) {
		vbg_err("vboxguest: Error requesting irq: %d\n", ret);
		goto err_vbg_core_exit;
	}

	ret = misc_register(&gdev->misc_device);
	if (ret) {
		vbg_err("vboxguest: Error misc_register %s failed: %d\n",
			DEVICE_NAME, ret);
		goto err_vbg_core_exit;
	}

	ret = misc_register(&gdev->misc_device_user);
	if (ret) {
		vbg_err("vboxguest: Error misc_register %s failed: %d\n",
			DEVICE_NAME_USER, ret);
		goto err_unregister_misc_device;
	}

	mutex_lock(&vbg_gdev_mutex);
	if (!vbg_gdev)
		vbg_gdev = gdev;
	else
		ret = -EBUSY;
	mutex_unlock(&vbg_gdev_mutex);

	if (ret) {
		vbg_err("vboxguest: Error more then 1 vbox guest pci device\n");
		goto err_unregister_misc_device_user;
	}

	pci_set_drvdata(pci, gdev);
	device_create_file(dev, &dev_attr_host_version);
	device_create_file(dev, &dev_attr_host_features);

	vbg_info("vboxguest: misc device minor %d, IRQ %d, I/O port %x, MMIO at %pap (size %pap)\n",
		 gdev->misc_device.minor, pci->irq, gdev->io_port,
		 &mmio, &mmio_len);

	return 0;

err_unregister_misc_device_user:
	misc_deregister(&gdev->misc_device_user);
err_unregister_misc_device:
	misc_deregister(&gdev->misc_device);
err_vbg_core_exit:
	vbg_core_exit(gdev);
err_disable_pcidev:
	pci_disable_device(pci);

	return ret;
}