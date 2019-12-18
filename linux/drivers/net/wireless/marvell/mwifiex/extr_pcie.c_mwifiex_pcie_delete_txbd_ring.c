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
struct pcie_service_card {int txbd_rdptr; scalar_t__ txbd_ring_pbase; int /*<<< orphan*/ * txbd_ring_vbase; scalar_t__ txbd_wrptr; scalar_t__ txbd_ring_size; int /*<<< orphan*/  dev; TYPE_1__ pcie; } ;
struct mwifiex_pcie_card_reg {int tx_rollover_ind; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwifiex_cleanup_txq_ring (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int mwifiex_pcie_delete_txbd_ring(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;

	mwifiex_cleanup_txq_ring(adapter);

	if (card->txbd_ring_vbase)
		pci_free_consistent(card->dev, card->txbd_ring_size,
				    card->txbd_ring_vbase,
				    card->txbd_ring_pbase);
	card->txbd_ring_size = 0;
	card->txbd_wrptr = 0;
	card->txbd_rdptr = 0 | reg->tx_rollover_ind;
	card->txbd_ring_vbase = NULL;
	card->txbd_ring_pbase = 0;

	return 0;
}