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
typedef  int u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  machine_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc86xx_hpcd ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 

__attribute__((used)) static void hpcd_quirk_uli1575(struct pci_dev *dev)
{
	u32 temp32;

	if (!machine_is(mpc86xx_hpcd))
		return;

	/* Disable INTx */
	pci_read_config_dword(dev, 0x48, &temp32);
	pci_write_config_dword(dev, 0x48, (temp32 | 1<<26));

	/* Enable sideband interrupt */
	pci_read_config_dword(dev, 0x90, &temp32);
	pci_write_config_dword(dev, 0x90, (temp32 | 1<<22));
}