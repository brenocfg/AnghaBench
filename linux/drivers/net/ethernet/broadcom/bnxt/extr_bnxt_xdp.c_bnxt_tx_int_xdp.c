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
typedef  size_t u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bnxt_tx_ring_info {size_t tx_cons; struct bnxt_sw_tx_bd* tx_buf_ring; } ;
struct bnxt_sw_tx_bd {scalar_t__ action; int /*<<< orphan*/  rx_prod; int /*<<< orphan*/ * xdpf; } ;
struct bnxt_rx_ring_info {int /*<<< orphan*/  rx_db; } ;
struct bnxt_napi {struct bnxt_rx_ring_info* rx_ring; struct bnxt_tx_ring_info* tx_ring; } ;
struct bnxt {struct pci_dev* pdev; } ;

/* Variables and functions */
 size_t NEXT_TX (size_t) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ XDP_REDIRECT ; 
 scalar_t__ XDP_TX ; 
 int /*<<< orphan*/  bnxt_db_write (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct bnxt_sw_tx_bd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct bnxt_sw_tx_bd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  xdp_return_frame (int /*<<< orphan*/ *) ; 

void bnxt_tx_int_xdp(struct bnxt *bp, struct bnxt_napi *bnapi, int nr_pkts)
{
	struct bnxt_tx_ring_info *txr = bnapi->tx_ring;
	struct bnxt_rx_ring_info *rxr = bnapi->rx_ring;
	bool rx_doorbell_needed = false;
	struct bnxt_sw_tx_bd *tx_buf;
	u16 tx_cons = txr->tx_cons;
	u16 last_tx_cons = tx_cons;
	int i;

	for (i = 0; i < nr_pkts; i++) {
		tx_buf = &txr->tx_buf_ring[tx_cons];

		if (tx_buf->action == XDP_REDIRECT) {
			struct pci_dev *pdev = bp->pdev;

			dma_unmap_single(&pdev->dev,
					 dma_unmap_addr(tx_buf, mapping),
					 dma_unmap_len(tx_buf, len),
					 PCI_DMA_TODEVICE);
			xdp_return_frame(tx_buf->xdpf);
			tx_buf->action = 0;
			tx_buf->xdpf = NULL;
		} else if (tx_buf->action == XDP_TX) {
			rx_doorbell_needed = true;
			last_tx_cons = tx_cons;
		}
		tx_cons = NEXT_TX(tx_cons);
	}
	txr->tx_cons = tx_cons;
	if (rx_doorbell_needed) {
		tx_buf = &txr->tx_buf_ring[last_tx_cons];
		bnxt_db_write(bp, &rxr->rx_db, tx_buf->rx_prod);
	}
}