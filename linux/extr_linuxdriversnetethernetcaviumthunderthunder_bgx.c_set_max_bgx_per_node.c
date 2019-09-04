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
typedef  int u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_BGX_PER_CN81XX ; 
 scalar_t__ MAX_BGX_PER_CN83XX ; 
 scalar_t__ MAX_BGX_PER_CN88XX ; 
 int /*<<< orphan*/  PCI_SUBSYSTEM_ID ; 
#define  PCI_SUBSYS_DEVID_81XX_BGX 131 
#define  PCI_SUBSYS_DEVID_81XX_RGX 130 
#define  PCI_SUBSYS_DEVID_83XX_BGX 129 
#define  PCI_SUBSYS_DEVID_88XX_BGX 128 
 scalar_t__ max_bgx_per_node ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void set_max_bgx_per_node(struct pci_dev *pdev)
{
	u16 sdevid;

	if (max_bgx_per_node)
		return;

	pci_read_config_word(pdev, PCI_SUBSYSTEM_ID, &sdevid);
	switch (sdevid) {
	case PCI_SUBSYS_DEVID_81XX_BGX:
	case PCI_SUBSYS_DEVID_81XX_RGX:
		max_bgx_per_node = MAX_BGX_PER_CN81XX;
		break;
	case PCI_SUBSYS_DEVID_83XX_BGX:
		max_bgx_per_node = MAX_BGX_PER_CN83XX;
		break;
	case PCI_SUBSYS_DEVID_88XX_BGX:
	default:
		max_bgx_per_node = MAX_BGX_PER_CN88XX;
		break;
	}
}