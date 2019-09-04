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

/* Variables and functions */
 size_t PCIIO_ASIC_TYPE_PIC ; 
 size_t PCIIO_ASIC_TYPE_TIOCP ; 
 int /*<<< orphan*/  pcibr_provider ; 
 int /*<<< orphan*/ ** sn_pci_provider ; 

int
pcibr_init_provider(void)
{
	sn_pci_provider[PCIIO_ASIC_TYPE_PIC] = &pcibr_provider;
	sn_pci_provider[PCIIO_ASIC_TYPE_TIOCP] = &pcibr_provider;

	return 0;
}