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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {TYPE_1__* msix_entries; struct hinic_hwif* hwif; } ;
struct TYPE_3__ {int entry; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HINIC_HWIF_NUM_AEQS (struct hinic_hwif*) ; 
 int HINIC_HWIF_NUM_CEQS (struct hinic_hwif*) ; 
 int HINIC_HWIF_NUM_IRQS (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_MAX_QPS ; 
 int MAX_IRQS (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* devm_kzalloc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int pci_enable_msix_exact (struct pci_dev*,TYPE_1__*,int) ; 

__attribute__((used)) static int init_msix(struct hinic_hwdev *hwdev)
{
	struct hinic_hwif *hwif = hwdev->hwif;
	struct pci_dev *pdev = hwif->pdev;
	int nr_irqs, num_aeqs, num_ceqs;
	size_t msix_entries_size;
	int i, err;

	num_aeqs = HINIC_HWIF_NUM_AEQS(hwif);
	num_ceqs = HINIC_HWIF_NUM_CEQS(hwif);
	nr_irqs = MAX_IRQS(HINIC_MAX_QPS, num_aeqs, num_ceqs);
	if (nr_irqs > HINIC_HWIF_NUM_IRQS(hwif))
		nr_irqs = HINIC_HWIF_NUM_IRQS(hwif);

	msix_entries_size = nr_irqs * sizeof(*hwdev->msix_entries);
	hwdev->msix_entries = devm_kzalloc(&pdev->dev, msix_entries_size,
					   GFP_KERNEL);
	if (!hwdev->msix_entries)
		return -ENOMEM;

	for (i = 0; i < nr_irqs; i++)
		hwdev->msix_entries[i].entry = i;

	err = pci_enable_msix_exact(pdev, hwdev->msix_entries, nr_irqs);
	if (err) {
		dev_err(&pdev->dev, "Failed to enable pci msix\n");
		return err;
	}

	return 0;
}