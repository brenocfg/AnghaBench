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
struct ena_com_dev {int dummy; } ;

/* Variables and functions */
 int ENA_BAR_MASK ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  pci_release_selected_regions (struct pci_dev*,int) ; 
 int pci_select_bars (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ena_release_bars(struct ena_com_dev *ena_dev, struct pci_dev *pdev)
{
	int release_bars = pci_select_bars(pdev, IORESOURCE_MEM) & ENA_BAR_MASK;

	pci_release_selected_regions(pdev, release_bars);
}