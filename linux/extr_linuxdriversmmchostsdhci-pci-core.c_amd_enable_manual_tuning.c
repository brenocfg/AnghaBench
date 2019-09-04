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
 unsigned int AMD_FIFO_PTR ; 
 int /*<<< orphan*/  AMD_SD_MISC_CONTROL ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void amd_enable_manual_tuning(struct pci_dev *pdev)
{
	unsigned int val;

	pci_read_config_dword(pdev, AMD_SD_MISC_CONTROL, &val);
	val |= AMD_FIFO_PTR;
	pci_write_config_dword(pdev, AMD_SD_MISC_CONTROL, val);
}