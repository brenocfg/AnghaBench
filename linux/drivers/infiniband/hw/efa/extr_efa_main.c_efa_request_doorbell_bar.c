#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  db_bar; } ;
struct efa_dev {struct pci_dev* pdev; int /*<<< orphan*/  db_bar_len; int /*<<< orphan*/  db_bar_addr; TYPE_1__ dev_attr; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRV_MODULE_NAME ; 
 int EFA_BASE_BAR_MASK ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int pci_request_selected_regions (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_select_bars (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efa_request_doorbell_bar(struct efa_dev *dev)
{
	u8 db_bar_idx = dev->dev_attr.db_bar;
	struct pci_dev *pdev = dev->pdev;
	int bars;
	int err;

	if (!(BIT(db_bar_idx) & EFA_BASE_BAR_MASK)) {
		bars = pci_select_bars(pdev, IORESOURCE_MEM) & BIT(db_bar_idx);

		err = pci_request_selected_regions(pdev, bars, DRV_MODULE_NAME);
		if (err) {
			dev_err(&dev->pdev->dev,
				"pci_request_selected_regions for bar %d failed %d\n",
				db_bar_idx, err);
			return err;
		}
	}

	dev->db_bar_addr = pci_resource_start(dev->pdev, db_bar_idx);
	dev->db_bar_len = pci_resource_len(dev->pdev, db_bar_idx);

	return 0;
}