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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  HINIC_CSR_FUNC_ATTR1_ADDR ; 
 int /*<<< orphan*/  HINIC_FA1_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hinic_hwif_read_reg (struct hinic_hwif*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hwif_ready(struct hinic_hwif *hwif)
{
	struct pci_dev *pdev = hwif->pdev;
	u32 addr, attr1;

	addr   = HINIC_CSR_FUNC_ATTR1_ADDR;
	attr1  = hinic_hwif_read_reg(hwif, addr);

	if (!HINIC_FA1_GET(attr1, INIT_STATUS)) {
		dev_err(&pdev->dev, "hwif status is not ready\n");
		return -EFAULT;
	}

	return 0;
}