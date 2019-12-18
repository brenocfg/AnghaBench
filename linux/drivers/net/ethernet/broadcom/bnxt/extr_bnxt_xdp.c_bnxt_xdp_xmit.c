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
typedef  int u32 ;
struct xdp_frame {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct bpf_prog {int dummy; } ;
struct bnxt_tx_ring_info {int /*<<< orphan*/  tx_prod; int /*<<< orphan*/  tx_db; } ;
struct bnxt {int tx_nr_rings_xdp; TYPE_1__** bnapi; struct bnxt_tx_ring_info* tx_ring; int /*<<< orphan*/  state; struct pci_dev* pdev; int /*<<< orphan*/  xdp_prog; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int BNXT_NAPI_FLAG_XDP ; 
 int /*<<< orphan*/  BNXT_STATE_OPEN ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 struct bpf_prog* READ_ONCE (int /*<<< orphan*/ ) ; 
 int XDP_XMIT_FLUSH ; 
 int /*<<< orphan*/  __bnxt_xmit_xdp_redirect (struct bnxt*,struct bnxt_tx_ring_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xdp_frame*) ; 
 int /*<<< orphan*/  bnxt_db_write (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_tx_avail (struct bnxt*,struct bnxt_tx_ring_info*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  xdp_return_frame_rx_napi (struct xdp_frame*) ; 

int bnxt_xdp_xmit(struct net_device *dev, int num_frames,
		  struct xdp_frame **frames, u32 flags)
{
	struct bnxt *bp = netdev_priv(dev);
	struct bpf_prog *xdp_prog = READ_ONCE(bp->xdp_prog);
	struct pci_dev *pdev = bp->pdev;
	struct bnxt_tx_ring_info *txr;
	dma_addr_t mapping;
	int drops = 0;
	int ring;
	int i;

	if (!test_bit(BNXT_STATE_OPEN, &bp->state) ||
	    !bp->tx_nr_rings_xdp ||
	    !xdp_prog)
		return -EINVAL;

	ring = smp_processor_id() % bp->tx_nr_rings_xdp;
	txr = &bp->tx_ring[ring];

	for (i = 0; i < num_frames; i++) {
		struct xdp_frame *xdp = frames[i];

		if (!txr || !bnxt_tx_avail(bp, txr) ||
		    !(bp->bnapi[ring]->flags & BNXT_NAPI_FLAG_XDP)) {
			xdp_return_frame_rx_napi(xdp);
			drops++;
			continue;
		}

		mapping = dma_map_single(&pdev->dev, xdp->data, xdp->len,
					 DMA_TO_DEVICE);

		if (dma_mapping_error(&pdev->dev, mapping)) {
			xdp_return_frame_rx_napi(xdp);
			drops++;
			continue;
		}
		__bnxt_xmit_xdp_redirect(bp, txr, mapping, xdp->len, xdp);
	}

	if (flags & XDP_XMIT_FLUSH) {
		/* Sync BD data before updating doorbell */
		wmb();
		bnxt_db_write(bp, &txr->tx_db, txr->tx_prod);
	}

	return num_frames - drops;
}