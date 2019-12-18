#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int /*<<< orphan*/  driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; TYPE_2__* resource; } ;
struct nvkm_device {int dummy; } ;
struct drm_device {struct pci_dev* pdev; } ;
struct apertures_struct {int count; TYPE_1__* ranges; } ;
struct TYPE_7__ {int /*<<< orphan*/  driver_features; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {void* size; void* base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_ATOMIC ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int IORESOURCE_ROM_SHADOW ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 size_t PCI_ROM_RESOURCE ; 
 int PTR_ERR (struct drm_device*) ; 
 struct apertures_struct* alloc_apertures (int) ; 
 TYPE_3__ driver_pci ; 
 struct drm_device* drm_dev_alloc (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_remove_conflicting_framebuffers (struct apertures_struct*,char*,int) ; 
 int /*<<< orphan*/  kfree (struct apertures_struct*) ; 
 scalar_t__ nouveau_atomic ; 
 int /*<<< orphan*/  nouveau_config ; 
 char* nouveau_debug ; 
 int /*<<< orphan*/  nouveau_drm_device_fini (struct drm_device*) ; 
 int nouveau_drm_device_init (struct drm_device*) ; 
 int nouveau_modeset ; 
 int /*<<< orphan*/  nvkm_device_del (struct nvkm_device**) ; 
 int nvkm_device_pci_new (struct pci_dev*,int /*<<< orphan*/ ,char*,int,int,unsigned long long,struct nvkm_device**) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 void* pci_resource_len (struct pci_dev*,int) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct drm_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 scalar_t__ vga_switcheroo_client_probe_defer (struct pci_dev*) ; 

__attribute__((used)) static int nouveau_drm_probe(struct pci_dev *pdev,
			     const struct pci_device_id *pent)
{
	struct nvkm_device *device;
	struct drm_device *drm_dev;
	struct apertures_struct *aper;
	bool boot = false;
	int ret;

	if (vga_switcheroo_client_probe_defer(pdev))
		return -EPROBE_DEFER;

	/* We need to check that the chipset is supported before booting
	 * fbdev off the hardware, as there's no way to put it back.
	 */
	ret = nvkm_device_pci_new(pdev, nouveau_config, "error",
				  true, false, 0, &device);
	if (ret)
		return ret;

	nvkm_device_del(&device);

	/* Remove conflicting drivers (vesafb, efifb etc). */
	aper = alloc_apertures(3);
	if (!aper)
		return -ENOMEM;

	aper->ranges[0].base = pci_resource_start(pdev, 1);
	aper->ranges[0].size = pci_resource_len(pdev, 1);
	aper->count = 1;

	if (pci_resource_len(pdev, 2)) {
		aper->ranges[aper->count].base = pci_resource_start(pdev, 2);
		aper->ranges[aper->count].size = pci_resource_len(pdev, 2);
		aper->count++;
	}

	if (pci_resource_len(pdev, 3)) {
		aper->ranges[aper->count].base = pci_resource_start(pdev, 3);
		aper->ranges[aper->count].size = pci_resource_len(pdev, 3);
		aper->count++;
	}

#ifdef CONFIG_X86
	boot = pdev->resource[PCI_ROM_RESOURCE].flags & IORESOURCE_ROM_SHADOW;
#endif
	if (nouveau_modeset != 2)
		drm_fb_helper_remove_conflicting_framebuffers(aper, "nouveaufb", boot);
	kfree(aper);

	ret = nvkm_device_pci_new(pdev, nouveau_config, nouveau_debug,
				  true, true, ~0ULL, &device);
	if (ret)
		return ret;

	pci_set_master(pdev);

	if (nouveau_atomic)
		driver_pci.driver_features |= DRIVER_ATOMIC;

	drm_dev = drm_dev_alloc(&driver_pci, &pdev->dev);
	if (IS_ERR(drm_dev)) {
		ret = PTR_ERR(drm_dev);
		goto fail_nvkm;
	}

	ret = pci_enable_device(pdev);
	if (ret)
		goto fail_drm;

	drm_dev->pdev = pdev;
	pci_set_drvdata(pdev, drm_dev);

	ret = nouveau_drm_device_init(drm_dev);
	if (ret)
		goto fail_pci;

	ret = drm_dev_register(drm_dev, pent->driver_data);
	if (ret)
		goto fail_drm_dev_init;

	return 0;

fail_drm_dev_init:
	nouveau_drm_device_fini(drm_dev);
fail_pci:
	pci_disable_device(pdev);
fail_drm:
	drm_dev_put(drm_dev);
fail_nvkm:
	nvkm_device_del(&device);
	return ret;
}