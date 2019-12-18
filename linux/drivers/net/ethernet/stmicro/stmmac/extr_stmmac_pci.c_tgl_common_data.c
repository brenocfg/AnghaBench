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
struct plat_stmmacenet_data {int rx_queues_to_use; int tx_queues_to_use; int clk_ptp_rate; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int intel_mgbe_common_data (struct pci_dev*,struct plat_stmmacenet_data*) ; 

__attribute__((used)) static int tgl_common_data(struct pci_dev *pdev,
			   struct plat_stmmacenet_data *plat)
{
	int ret;

	plat->rx_queues_to_use = 6;
	plat->tx_queues_to_use = 4;
	plat->clk_ptp_rate = 200000000;
	ret = intel_mgbe_common_data(pdev, plat);
	if (ret)
		return ret;

	return 0;
}