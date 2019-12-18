#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ ip_summed; } ;
struct net_device {int dummy; } ;
struct fec_enet_private {int quirks; unsigned long tx_align; TYPE_1__* pdev; scalar_t__ bufdesc_ex; scalar_t__ hwts_tx_en; } ;
struct TYPE_7__ {struct bufdesc* cur; int /*<<< orphan*/  qid; } ;
struct fec_enet_priv_tx_q {TYPE_3__ bd; void** tx_bounce; } ;
struct bufdesc_ex {void* cbd_esc; scalar_t__ cbd_bdu; } ;
struct bufdesc {void* cbd_datlen; void* cbd_bufaddr; void* cbd_sc; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  unsigned int dma_addr_t ;
struct TYPE_6__ {int nr_frags; int tx_flags; int /*<<< orphan*/ * frags; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int BD_ENET_TX_IINS ; 
 unsigned int BD_ENET_TX_INT ; 
 unsigned short BD_ENET_TX_INTR ; 
 unsigned short BD_ENET_TX_LAST ; 
 unsigned int BD_ENET_TX_PINS ; 
 unsigned short BD_ENET_TX_READY ; 
 unsigned short BD_ENET_TX_STATS ; 
 unsigned short BD_ENET_TX_TC ; 
 unsigned int BD_ENET_TX_TS ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct bufdesc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int FEC_QUIRK_HAS_AVB ; 
 int FEC_QUIRK_SWAP_FRAME ; 
 unsigned int FEC_TX_BD_FTYPE (int /*<<< orphan*/ ) ; 
 int SKBTX_HW_TSTAMP ; 
 void* cpu_to_fec16 (unsigned short) ; 
 void* cpu_to_fec32 (unsigned int) ; 
 unsigned int dma_map_single (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 
 unsigned short fec16_to_cpu (void*) ; 
 int /*<<< orphan*/  fec32_to_cpu (void*) ; 
 unsigned int fec_enet_get_bd_index (struct bufdesc*,TYPE_3__*) ; 
 struct bufdesc* fec_enet_get_nextdesc (struct bufdesc*,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 void* skb_frag_address (int /*<<< orphan*/ *) ; 
 int skb_frag_size (int /*<<< orphan*/ *) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  swap_buffer (void*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static struct bufdesc *
fec_enet_txq_submit_frag_skb(struct fec_enet_priv_tx_q *txq,
			     struct sk_buff *skb,
			     struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct bufdesc *bdp = txq->bd.cur;
	struct bufdesc_ex *ebdp;
	int nr_frags = skb_shinfo(skb)->nr_frags;
	int frag, frag_len;
	unsigned short status;
	unsigned int estatus = 0;
	skb_frag_t *this_frag;
	unsigned int index;
	void *bufaddr;
	dma_addr_t addr;
	int i;

	for (frag = 0; frag < nr_frags; frag++) {
		this_frag = &skb_shinfo(skb)->frags[frag];
		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
		ebdp = (struct bufdesc_ex *)bdp;

		status = fec16_to_cpu(bdp->cbd_sc);
		status &= ~BD_ENET_TX_STATS;
		status |= (BD_ENET_TX_TC | BD_ENET_TX_READY);
		frag_len = skb_frag_size(&skb_shinfo(skb)->frags[frag]);

		/* Handle the last BD specially */
		if (frag == nr_frags - 1) {
			status |= (BD_ENET_TX_INTR | BD_ENET_TX_LAST);
			if (fep->bufdesc_ex) {
				estatus |= BD_ENET_TX_INT;
				if (unlikely(skb_shinfo(skb)->tx_flags &
					SKBTX_HW_TSTAMP && fep->hwts_tx_en))
					estatus |= BD_ENET_TX_TS;
			}
		}

		if (fep->bufdesc_ex) {
			if (fep->quirks & FEC_QUIRK_HAS_AVB)
				estatus |= FEC_TX_BD_FTYPE(txq->bd.qid);
			if (skb->ip_summed == CHECKSUM_PARTIAL)
				estatus |= BD_ENET_TX_PINS | BD_ENET_TX_IINS;
			ebdp->cbd_bdu = 0;
			ebdp->cbd_esc = cpu_to_fec32(estatus);
		}

		bufaddr = skb_frag_address(this_frag);

		index = fec_enet_get_bd_index(bdp, &txq->bd);
		if (((unsigned long) bufaddr) & fep->tx_align ||
			fep->quirks & FEC_QUIRK_SWAP_FRAME) {
			memcpy(txq->tx_bounce[index], bufaddr, frag_len);
			bufaddr = txq->tx_bounce[index];

			if (fep->quirks & FEC_QUIRK_SWAP_FRAME)
				swap_buffer(bufaddr, frag_len);
		}

		addr = dma_map_single(&fep->pdev->dev, bufaddr, frag_len,
				      DMA_TO_DEVICE);
		if (dma_mapping_error(&fep->pdev->dev, addr)) {
			if (net_ratelimit())
				netdev_err(ndev, "Tx DMA memory map failed\n");
			goto dma_mapping_error;
		}

		bdp->cbd_bufaddr = cpu_to_fec32(addr);
		bdp->cbd_datlen = cpu_to_fec16(frag_len);
		/* Make sure the updates to rest of the descriptor are
		 * performed before transferring ownership.
		 */
		wmb();
		bdp->cbd_sc = cpu_to_fec16(status);
	}

	return bdp;
dma_mapping_error:
	bdp = txq->bd.cur;
	for (i = 0; i < frag; i++) {
		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
		dma_unmap_single(&fep->pdev->dev, fec32_to_cpu(bdp->cbd_bufaddr),
				 fec16_to_cpu(bdp->cbd_datlen), DMA_TO_DEVICE);
	}
	return ERR_PTR(-ENOMEM);
}