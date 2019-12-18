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
struct ionic_dev_bar {unsigned int res_index; int /*<<< orphan*/  bus_addr; int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  len; } ;
struct ionic {scalar_t__ num_bars; struct ionic_dev_bar* bars; struct device* dev; struct pci_dev* pdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int IONIC_BARS_MAX ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/ * pci_iomap (struct pci_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,unsigned int) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,unsigned int) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,unsigned int) ; 

__attribute__((used)) static int ionic_map_bars(struct ionic *ionic)
{
	struct pci_dev *pdev = ionic->pdev;
	struct device *dev = ionic->dev;
	struct ionic_dev_bar *bars;
	unsigned int i, j;

	bars = ionic->bars;
	ionic->num_bars = 0;

	for (i = 0, j = 0; i < IONIC_BARS_MAX; i++) {
		if (!(pci_resource_flags(pdev, i) & IORESOURCE_MEM))
			continue;
		bars[j].len = pci_resource_len(pdev, i);

		/* only map the whole bar 0 */
		if (j > 0) {
			bars[j].vaddr = NULL;
		} else {
			bars[j].vaddr = pci_iomap(pdev, i, bars[j].len);
			if (!bars[j].vaddr) {
				dev_err(dev,
					"Cannot memory-map BAR %d, aborting\n",
					i);
				return -ENODEV;
			}
		}

		bars[j].bus_addr = pci_resource_start(pdev, i);
		bars[j].res_index = i;
		ionic->num_bars++;
		j++;
	}

	return 0;
}