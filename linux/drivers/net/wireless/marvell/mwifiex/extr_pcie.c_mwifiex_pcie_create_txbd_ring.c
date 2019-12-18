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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct mwifiex_pcie_card_reg* reg; } ;
struct pcie_service_card {int txbd_ring_size; scalar_t__ txbd_ring_pbase; int /*<<< orphan*/  txbd_ring_vbase; int /*<<< orphan*/  dev; int /*<<< orphan*/  txbd_rdptr; scalar_t__ txbd_wrptr; TYPE_1__ pcie; } ;
struct mwifiex_pfu_buf_desc {int dummy; } ;
struct mwifiex_pcie_card_reg {scalar_t__ pfu_enabled; int /*<<< orphan*/  tx_rollover_ind; } ;
struct mwifiex_pcie_buf_desc {int dummy; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INFO ; 
 int MWIFIEX_MAX_TXRX_BD ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,int,...) ; 
 int mwifiex_init_txq_ring (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  pci_alloc_consistent (int /*<<< orphan*/ ,int,scalar_t__*) ; 

__attribute__((used)) static int mwifiex_pcie_create_txbd_ring(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;

	/*
	 * driver maintaines the write pointer and firmware maintaines the read
	 * pointer. The write pointer starts at 0 (zero) while the read pointer
	 * starts at zero with rollover bit set
	 */
	card->txbd_wrptr = 0;

	if (reg->pfu_enabled)
		card->txbd_rdptr = 0;
	else
		card->txbd_rdptr |= reg->tx_rollover_ind;

	/* allocate shared memory for the BD ring and divide the same in to
	   several descriptors */
	if (reg->pfu_enabled)
		card->txbd_ring_size = sizeof(struct mwifiex_pfu_buf_desc) *
				       MWIFIEX_MAX_TXRX_BD;
	else
		card->txbd_ring_size = sizeof(struct mwifiex_pcie_buf_desc) *
				       MWIFIEX_MAX_TXRX_BD;

	mwifiex_dbg(adapter, INFO,
		    "info: txbd_ring: Allocating %d bytes\n",
		    card->txbd_ring_size);
	card->txbd_ring_vbase = pci_alloc_consistent(card->dev,
						     card->txbd_ring_size,
						     &card->txbd_ring_pbase);
	if (!card->txbd_ring_vbase) {
		mwifiex_dbg(adapter, ERROR,
			    "allocate consistent memory (%d bytes) failed!\n",
			    card->txbd_ring_size);
		return -ENOMEM;
	}
	mwifiex_dbg(adapter, DATA,
		    "info: txbd_ring - base: %p, pbase: %#x:%x, len: %x\n",
		    card->txbd_ring_vbase, (unsigned int)card->txbd_ring_pbase,
		    (u32)((u64)card->txbd_ring_pbase >> 32),
		    card->txbd_ring_size);

	return mwifiex_init_txq_ring(adapter);
}