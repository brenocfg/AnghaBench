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
typedef  int u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int AMD_AUTO_TUNE_SEL ; 
 unsigned int AMD_BIT_MASK ; 
 int /*<<< orphan*/  AMD_SD_AUTO_PATTERN ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void amd_config_tuning_phase(struct pci_dev *pdev, u8 phase)
{
	unsigned int val;

	pci_read_config_dword(pdev, AMD_SD_AUTO_PATTERN, &val);
	val &= ~AMD_BIT_MASK;
	val |= (AMD_AUTO_TUNE_SEL | (phase << 1));
	pci_write_config_dword(pdev, AMD_SD_AUTO_PATTERN, val);
}