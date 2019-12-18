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
typedef  scalar_t__ u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ CXL_PCI_VSEC_ID ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_VNDR ; 
 int pci_find_next_ext_capability (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,scalar_t__*) ; 

__attribute__((used)) static int find_cxl_vsec(struct pci_dev *dev)
{
	int vsec = 0;
	u16 val;

	while ((vsec = pci_find_next_ext_capability(dev, vsec, PCI_EXT_CAP_ID_VNDR))) {
		pci_read_config_word(dev, vsec + 0x4, &val);
		if (val == CXL_PCI_VSEC_ID)
			return vsec;
	}
	return 0;

}