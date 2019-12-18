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
struct pcie_service_card {int txbd_wrptr; int rxbd_rdptr; TYPE_1__ pcie; } ;
struct mwifiex_pcie_card_reg {int tx_wrap_mask; int /*<<< orphan*/  rx_rdptr; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mwifiex_write_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mwifiex_pcie_init_fw_port(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;
	int tx_wrap = card->txbd_wrptr & reg->tx_wrap_mask;

	/* Write the RX ring read pointer in to reg->rx_rdptr */
	if (mwifiex_write_reg(adapter, reg->rx_rdptr, card->rxbd_rdptr |
			      tx_wrap)) {
		mwifiex_dbg(adapter, ERROR,
			    "RECV DATA: failed to write reg->rx_rdptr\n");
		return -1;
	}
	return 0;
}