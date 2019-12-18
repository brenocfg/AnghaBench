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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PCI_EXP_LNKSTA ; 
 int PCI_EXP_LNKSTA_CLS ; 
#define  PCI_EXP_LNKSTA_CLS_16_0GB 132 
#define  PCI_EXP_LNKSTA_CLS_2_5GB 131 
#define  PCI_EXP_LNKSTA_CLS_32_0GB 130 
#define  PCI_EXP_LNKSTA_CLS_5_0GB 129 
#define  PCI_EXP_LNKSTA_CLS_8_0GB 128 
 int pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t current_link_speed_show(struct device *dev,
				       struct device_attribute *attr, char *buf)
{
	struct pci_dev *pci_dev = to_pci_dev(dev);
	u16 linkstat;
	int err;
	const char *speed;

	err = pcie_capability_read_word(pci_dev, PCI_EXP_LNKSTA, &linkstat);
	if (err)
		return -EINVAL;

	switch (linkstat & PCI_EXP_LNKSTA_CLS) {
	case PCI_EXP_LNKSTA_CLS_32_0GB:
		speed = "32 GT/s";
		break;
	case PCI_EXP_LNKSTA_CLS_16_0GB:
		speed = "16 GT/s";
		break;
	case PCI_EXP_LNKSTA_CLS_8_0GB:
		speed = "8 GT/s";
		break;
	case PCI_EXP_LNKSTA_CLS_5_0GB:
		speed = "5 GT/s";
		break;
	case PCI_EXP_LNKSTA_CLS_2_5GB:
		speed = "2.5 GT/s";
		break;
	default:
		speed = "Unknown speed";
	}

	return sprintf(buf, "%s\n", speed);
}