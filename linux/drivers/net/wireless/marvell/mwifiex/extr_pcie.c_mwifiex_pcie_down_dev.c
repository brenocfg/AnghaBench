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
struct TYPE_2__ {struct mwifiex_pcie_card_reg* reg; } ;
struct pcie_service_card {struct pci_dev* dev; TYPE_1__ pcie; } ;
struct pci_dev {int dummy; } ;
struct mwifiex_pcie_card_reg {int /*<<< orphan*/  drv_rdy; } ;
struct mwifiex_adapter {scalar_t__ seq_num; struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_pcie_free_buffers (struct mwifiex_adapter*) ; 
 scalar_t__ mwifiex_write_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 

__attribute__((used)) static void mwifiex_pcie_down_dev(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;
	struct pci_dev *pdev = card->dev;

	if (mwifiex_write_reg(adapter, reg->drv_rdy, 0x00000000))
		mwifiex_dbg(adapter, ERROR, "Failed to write driver not-ready signature\n");

	pci_clear_master(pdev);

	adapter->seq_num = 0;

	mwifiex_pcie_free_buffers(adapter);
}