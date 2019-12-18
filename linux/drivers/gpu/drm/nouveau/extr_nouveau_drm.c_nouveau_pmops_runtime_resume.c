#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct nvif_device {int /*<<< orphan*/  object; } ;
struct TYPE_2__ {struct nvif_device device; } ;
struct nouveau_drm {int /*<<< orphan*/  hpd_work; TYPE_1__ client; } ;
struct drm_device {int /*<<< orphan*/  switch_power_state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_SWITCH_POWER_ON ; 
 int EBUSY ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*,int) ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int nouveau_do_resume (struct drm_device*,int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_pmops_runtime () ; 
 int /*<<< orphan*/  nvif_mask (int /*<<< orphan*/ *,int,int,int) ; 
 int pci_enable_device (struct pci_dev*) ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_forbid (struct device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int
nouveau_pmops_runtime_resume(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct drm_device *drm_dev = pci_get_drvdata(pdev);
	struct nouveau_drm *drm = nouveau_drm(drm_dev);
	struct nvif_device *device = &nouveau_drm(drm_dev)->client.device;
	int ret;

	if (!nouveau_pmops_runtime()) {
		pm_runtime_forbid(dev);
		return -EBUSY;
	}

	pci_set_power_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	ret = pci_enable_device(pdev);
	if (ret)
		return ret;
	pci_set_master(pdev);

	ret = nouveau_do_resume(drm_dev, true);
	if (ret) {
		NV_ERROR(drm, "resume failed with: %d\n", ret);
		return ret;
	}

	/* do magic */
	nvif_mask(&device->object, 0x088488, (1 << 25), (1 << 25));
	drm_dev->switch_power_state = DRM_SWITCH_POWER_ON;

	/* Monitors may have been connected / disconnected during suspend */
	schedule_work(&nouveau_drm(drm_dev)->hpd_work);

	return ret;
}