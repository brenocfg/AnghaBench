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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MSR_IDE_CFG ; 
 scalar_t__ PCI_IDE_CFG ; 
 int pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_msr ; 
 int /*<<< orphan*/  wrmsr (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs5536_write(struct pci_dev *pdev, int reg, int val)
{
	if (unlikely(use_msr)) {
		wrmsr(MSR_IDE_CFG + reg, val, 0);
		return 0;
	}

	return pci_write_config_dword(pdev, PCI_IDE_CFG + reg * 4, val);
}