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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INT_MAX ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_ANY_ID ; 
 int /*<<< orphan*/  kfree (struct pci_dev**) ; 
 struct pci_dev** kmalloc (int,int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_has_p2pmem (struct pci_dev*) ; 
 int pci_p2pdma_distance_many (struct pci_dev*,struct device**,int,int) ; 
 size_t prandom_u32_max (int) ; 

struct pci_dev *pci_p2pmem_find_many(struct device **clients, int num_clients)
{
	struct pci_dev *pdev = NULL;
	int distance;
	int closest_distance = INT_MAX;
	struct pci_dev **closest_pdevs;
	int dev_cnt = 0;
	const int max_devs = PAGE_SIZE / sizeof(*closest_pdevs);
	int i;

	closest_pdevs = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!closest_pdevs)
		return NULL;

	while ((pdev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, pdev))) {
		if (!pci_has_p2pmem(pdev))
			continue;

		distance = pci_p2pdma_distance_many(pdev, clients,
						    num_clients, false);
		if (distance < 0 || distance > closest_distance)
			continue;

		if (distance == closest_distance && dev_cnt >= max_devs)
			continue;

		if (distance < closest_distance) {
			for (i = 0; i < dev_cnt; i++)
				pci_dev_put(closest_pdevs[i]);

			dev_cnt = 0;
			closest_distance = distance;
		}

		closest_pdevs[dev_cnt++] = pci_dev_get(pdev);
	}

	if (dev_cnt)
		pdev = pci_dev_get(closest_pdevs[prandom_u32_max(dev_cnt)]);

	for (i = 0; i < dev_cnt; i++)
		pci_dev_put(closest_pdevs[i]);

	kfree(closest_pdevs);
	return pdev;
}