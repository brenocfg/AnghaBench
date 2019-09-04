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
struct intel_uncore_box {int /*<<< orphan*/  hrtimer_duration; int /*<<< orphan*/  io_addr; struct pci_dev* pci_dev; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int SNB_UNCORE_PCI_IMC_BAR_OFFSET ; 
 int /*<<< orphan*/  SNB_UNCORE_PCI_IMC_MAP_SIZE ; 
 int /*<<< orphan*/  UNCORE_SNB_IMC_HRTIMER_INTERVAL ; 
 int /*<<< orphan*/  ioremap (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 

__attribute__((used)) static void snb_uncore_imc_init_box(struct intel_uncore_box *box)
{
	struct pci_dev *pdev = box->pci_dev;
	int where = SNB_UNCORE_PCI_IMC_BAR_OFFSET;
	resource_size_t addr;
	u32 pci_dword;

	pci_read_config_dword(pdev, where, &pci_dword);
	addr = pci_dword;

#ifdef CONFIG_PHYS_ADDR_T_64BIT
	pci_read_config_dword(pdev, where + 4, &pci_dword);
	addr |= ((resource_size_t)pci_dword << 32);
#endif

	addr &= ~(PAGE_SIZE - 1);

	box->io_addr = ioremap(addr, SNB_UNCORE_PCI_IMC_MAP_SIZE);
	box->hrtimer_duration = UNCORE_SNB_IMC_HRTIMER_INTERVAL;
}