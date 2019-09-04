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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct myri10ge_priv {int vendor_specific_offset; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 

__attribute__((used)) static u32 myri10ge_read_reboot(struct myri10ge_priv *mgp)
{
	struct pci_dev *pdev = mgp->pdev;
	int vs = mgp->vendor_specific_offset;
	u32 reboot;

	/*enter read32 mode */
	pci_write_config_byte(pdev, vs + 0x10, 0x3);

	/*read REBOOT_STATUS (0xfffffff0) */
	pci_write_config_dword(pdev, vs + 0x18, 0xfffffff0);
	pci_read_config_dword(pdev, vs + 0x14, &reboot);
	return reboot;
}