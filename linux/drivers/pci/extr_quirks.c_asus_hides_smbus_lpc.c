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
 int /*<<< orphan*/  asus_hides_smbus ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,...) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 

__attribute__((used)) static void asus_hides_smbus_lpc(struct pci_dev *dev)
{
	u16 val;

	if (likely(!asus_hides_smbus))
		return;

	pci_read_config_word(dev, 0xF2, &val);
	if (val & 0x8) {
		pci_write_config_word(dev, 0xF2, val & (~0x8));
		pci_read_config_word(dev, 0xF2, &val);
		if (val & 0x8)
			pci_info(dev, "i801 SMBus device continues to play 'hide and seek'! 0x%x\n",
				 val);
		else
			pci_info(dev, "Enabled i801 SMBus device\n");
	}
}