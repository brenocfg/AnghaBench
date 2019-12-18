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
struct pci_device_id {unsigned long driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CHIP_BONAIRE 137 
#define  CHIP_HAINAN 136 
#define  CHIP_HAWAII 135 
#define  CHIP_KABINI 134 
#define  CHIP_KAVERI 133 
#define  CHIP_MULLINS 132 
#define  CHIP_OLAND 131 
#define  CHIP_PITCAIRN 130 
#define  CHIP_TAHITI 129 
#define  CHIP_VERDE 128 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 unsigned long RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int drm_fb_helper_remove_conflicting_pci_framebuffers (struct pci_dev*,int /*<<< orphan*/ ,char*) ; 
 int drm_get_pci_dev (struct pci_dev*,struct pci_device_id const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kms_driver ; 
 int /*<<< orphan*/  radeon_cik_support ; 
 int /*<<< orphan*/  radeon_si_support ; 
 scalar_t__ vga_switcheroo_client_probe_defer (struct pci_dev*) ; 

__attribute__((used)) static int radeon_pci_probe(struct pci_dev *pdev,
			    const struct pci_device_id *ent)
{
	unsigned long flags = 0;
	int ret;

	if (!ent)
		return -ENODEV; /* Avoid NULL-ptr deref in drm_get_pci_dev */

	flags = ent->driver_data;

	if (!radeon_si_support) {
		switch (flags & RADEON_FAMILY_MASK) {
		case CHIP_TAHITI:
		case CHIP_PITCAIRN:
		case CHIP_VERDE:
		case CHIP_OLAND:
		case CHIP_HAINAN:
			dev_info(&pdev->dev,
				 "SI support disabled by module param\n");
			return -ENODEV;
		}
	}
	if (!radeon_cik_support) {
		switch (flags & RADEON_FAMILY_MASK) {
		case CHIP_KAVERI:
		case CHIP_BONAIRE:
		case CHIP_HAWAII:
		case CHIP_KABINI:
		case CHIP_MULLINS:
			dev_info(&pdev->dev,
				 "CIK support disabled by module param\n");
			return -ENODEV;
		}
	}

	if (vga_switcheroo_client_probe_defer(pdev))
		return -EPROBE_DEFER;

	/* Get rid of things like offb */
	ret = drm_fb_helper_remove_conflicting_pci_framebuffers(pdev, 0, "radeondrmfb");
	if (ret)
		return ret;

	return drm_get_pci_dev(pdev, ent, &kms_driver);
}