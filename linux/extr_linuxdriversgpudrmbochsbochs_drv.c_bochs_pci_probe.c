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
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  bochs_driver ; 
 int bochs_kick_out_firmware_fb (struct pci_dev*) ; 
 int drm_get_pci_dev (struct pci_dev*,struct pci_device_id const*,int /*<<< orphan*/ *) ; 
 unsigned long pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bochs_pci_probe(struct pci_dev *pdev,
			   const struct pci_device_id *ent)
{
	unsigned long fbsize;
	int ret;

	fbsize = pci_resource_len(pdev, 0);
	if (fbsize < 4 * 1024 * 1024) {
		DRM_ERROR("less than 4 MB video memory, ignoring device\n");
		return -ENOMEM;
	}

	ret = bochs_kick_out_firmware_fb(pdev);
	if (ret)
		return ret;

	return drm_get_pci_dev(pdev, ent, &bochs_driver);
}