#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct chelsio_pci_params {unsigned short speed; int width; int is_pcix; } ;
struct TYPE_3__ {int /*<<< orphan*/  pdev; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_PCICFG_MODE ; 
 int F_PCI_MODE_64BIT ; 
 int F_PCI_MODE_PCIX ; 
 size_t G_PCI_MODE_CLK (int) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void get_pci_mode(adapter_t *adapter, struct chelsio_pci_params *p)
{
	static const unsigned short speed_map[] = { 33, 66, 100, 133 };
	u32 pci_mode;

	pci_read_config_dword(adapter->pdev, A_PCICFG_MODE, &pci_mode);
	p->speed = speed_map[G_PCI_MODE_CLK(pci_mode)];
	p->width = (pci_mode & F_PCI_MODE_64BIT) ? 64 : 32;
	p->is_pcix = (pci_mode & F_PCI_MODE_PCIX) != 0;
}