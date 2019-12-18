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
struct qxl_device {int /*<<< orphan*/  ddev; } ;
struct pci_device_id {int /*<<< orphan*/  driver_data; } ;
struct pci_dev {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VGA_RSRC_LEGACY_IO ; 
 int drm_dev_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_fb_helper_remove_conflicting_pci_framebuffers (struct pci_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_fbdev_generic_setup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (int /*<<< orphan*/ *) ; 
 scalar_t__ is_vga (struct pci_dev*) ; 
 int /*<<< orphan*/  kfree (struct qxl_device*) ; 
 struct qxl_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  qxl_device_fini (struct qxl_device*) ; 
 int qxl_device_init (struct qxl_device*,int /*<<< orphan*/ *,struct pci_dev*) ; 
 int /*<<< orphan*/  qxl_driver ; 
 int /*<<< orphan*/  qxl_modeset_fini (struct qxl_device*) ; 
 int qxl_modeset_init (struct qxl_device*) ; 
 int vga_get_interruptible (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_put (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qxl_pci_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct qxl_device *qdev;
	int ret;

	if (pdev->revision < 4) {
		DRM_ERROR("qxl too old, doesn't support client_monitors_config,"
			  " use xf86-video-qxl in user mode");
		return -EINVAL; /* TODO: ENODEV ? */
	}

	qdev = kzalloc(sizeof(struct qxl_device), GFP_KERNEL);
	if (!qdev)
		return -ENOMEM;

	ret = pci_enable_device(pdev);
	if (ret)
		goto free_dev;

	ret = drm_fb_helper_remove_conflicting_pci_framebuffers(pdev, 0, "qxl");
	if (ret)
		goto disable_pci;

	if (is_vga(pdev)) {
		ret = vga_get_interruptible(pdev, VGA_RSRC_LEGACY_IO);
		if (ret) {
			DRM_ERROR("can't get legacy vga ioports\n");
			goto disable_pci;
		}
	}

	ret = qxl_device_init(qdev, &qxl_driver, pdev);
	if (ret)
		goto put_vga;

	ret = qxl_modeset_init(qdev);
	if (ret)
		goto unload;

	drm_kms_helper_poll_init(&qdev->ddev);

	/* Complete initialization. */
	ret = drm_dev_register(&qdev->ddev, ent->driver_data);
	if (ret)
		goto modeset_cleanup;

	drm_fbdev_generic_setup(&qdev->ddev, 32);
	return 0;

modeset_cleanup:
	qxl_modeset_fini(qdev);
unload:
	qxl_device_fini(qdev);
put_vga:
	if (is_vga(pdev))
		vga_put(pdev, VGA_RSRC_LEGACY_IO);
disable_pci:
	pci_disable_device(pdev);
free_dev:
	kfree(qdev);
	return ret;
}