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
 int cirrus_kick_out_firmware_fb (struct pci_dev*) ; 
 int /*<<< orphan*/  driver ; 
 int drm_get_pci_dev (struct pci_dev*,struct pci_device_id const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cirrus_pci_probe(struct pci_dev *pdev,
			    const struct pci_device_id *ent)
{
	int ret;

	ret = cirrus_kick_out_firmware_fb(pdev);
	if (ret)
		return ret;

	return drm_get_pci_dev(pdev, ent, &driver);
}