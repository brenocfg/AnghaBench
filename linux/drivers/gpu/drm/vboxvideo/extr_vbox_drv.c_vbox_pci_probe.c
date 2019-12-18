#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct vbox_private* dev_private; struct pci_dev* pdev; } ;
struct vbox_private {TYPE_1__ ddev; int /*<<< orphan*/  num_crtcs; int /*<<< orphan*/  fb_helper; int /*<<< orphan*/  hw_mutex; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VBE_DISPI_ID_HGSMI ; 
 int /*<<< orphan*/  driver ; 
 int drm_dev_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dev_put (TYPE_1__*) ; 
 int drm_dev_register (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int drm_fb_helper_fbdev_setup (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vbox_private*) ; 
 struct vbox_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_check_supported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbox_fb_helper_funcs ; 
 int /*<<< orphan*/  vbox_fbdev_fini (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_hw_fini (struct vbox_private*) ; 
 int vbox_hw_init (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_irq_fini (struct vbox_private*) ; 
 int vbox_irq_init (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_mm_fini (struct vbox_private*) ; 
 int vbox_mm_init (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_mode_fini (struct vbox_private*) ; 
 int vbox_mode_init (struct vbox_private*) ; 

__attribute__((used)) static int vbox_pci_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct vbox_private *vbox;
	int ret = 0;

	if (!vbox_check_supported(VBE_DISPI_ID_HGSMI))
		return -ENODEV;

	vbox = kzalloc(sizeof(*vbox), GFP_KERNEL);
	if (!vbox)
		return -ENOMEM;

	ret = drm_dev_init(&vbox->ddev, &driver, &pdev->dev);
	if (ret) {
		kfree(vbox);
		return ret;
	}

	vbox->ddev.pdev = pdev;
	vbox->ddev.dev_private = vbox;
	pci_set_drvdata(pdev, vbox);
	mutex_init(&vbox->hw_mutex);

	ret = pci_enable_device(pdev);
	if (ret)
		goto err_dev_put;

	ret = vbox_hw_init(vbox);
	if (ret)
		goto err_pci_disable;

	ret = vbox_mm_init(vbox);
	if (ret)
		goto err_hw_fini;

	ret = vbox_mode_init(vbox);
	if (ret)
		goto err_mm_fini;

	ret = vbox_irq_init(vbox);
	if (ret)
		goto err_mode_fini;

	ret = drm_fb_helper_fbdev_setup(&vbox->ddev, &vbox->fb_helper,
					&vbox_fb_helper_funcs, 32,
					vbox->num_crtcs);
	if (ret)
		goto err_irq_fini;

	ret = drm_dev_register(&vbox->ddev, 0);
	if (ret)
		goto err_fbdev_fini;

	return 0;

err_fbdev_fini:
	vbox_fbdev_fini(vbox);
err_irq_fini:
	vbox_irq_fini(vbox);
err_mode_fini:
	vbox_mode_fini(vbox);
err_mm_fini:
	vbox_mm_fini(vbox);
err_hw_fini:
	vbox_hw_fini(vbox);
err_pci_disable:
	pci_disable_device(pdev);
err_dev_put:
	drm_dev_put(&vbox->ddev);
	return ret;
}