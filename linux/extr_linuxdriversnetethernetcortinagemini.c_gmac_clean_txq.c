#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ byte_count; } ;
union gmac_txdesc_1 {int bits32; TYPE_3__ bits; } ;
struct TYPE_9__ {int desc_count; int /*<<< orphan*/  status_tx_ok; int /*<<< orphan*/  buffer_size; } ;
union gmac_txdesc_0 {TYPE_4__ bits; } ;
struct net_device {int dummy; } ;
struct gmac_txq {unsigned int cptr; int /*<<< orphan*/ * skb; struct gmac_txdesc* ring; } ;
struct TYPE_7__ {unsigned int bits32; } ;
struct TYPE_6__ {int /*<<< orphan*/  buf_adr; } ;
struct gmac_txdesc {union gmac_txdesc_1 word1; TYPE_2__ word3; TYPE_1__ word2; union gmac_txdesc_0 word0; } ;
struct TYPE_10__ {unsigned int tx_errors; unsigned int tx_packets; unsigned long tx_bytes; } ;
struct gemini_ethernet_port {int txq_order; unsigned int tx_hw_csummed; int /*<<< orphan*/  ir_stats_syncp; TYPE_5__ stats; int /*<<< orphan*/  tx_stats_syncp; int /*<<< orphan*/ * tx_frag_stats; struct gemini_ethernet* geth; } ;
struct gemini_ethernet {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 unsigned int EOF_BIT ; 
 unsigned int SOF_BIT ; 
 int TSS_CHECKUM_ENABLE ; 
 unsigned short TX_MAX_FRAGS ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gemini_ethernet_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gmac_clean_txq(struct net_device *netdev, struct gmac_txq *txq,
			   unsigned int r)
{
	struct gemini_ethernet_port *port = netdev_priv(netdev);
	unsigned int m = (1 << port->txq_order) - 1;
	struct gemini_ethernet *geth = port->geth;
	unsigned int c = txq->cptr;
	union gmac_txdesc_0 word0;
	union gmac_txdesc_1 word1;
	unsigned int hwchksum = 0;
	unsigned long bytes = 0;
	struct gmac_txdesc *txd;
	unsigned short nfrags;
	unsigned int errs = 0;
	unsigned int pkts = 0;
	unsigned int word3;
	dma_addr_t mapping;

	if (c == r)
		return;

	while (c != r) {
		txd = txq->ring + c;
		word0 = txd->word0;
		word1 = txd->word1;
		mapping = txd->word2.buf_adr;
		word3 = txd->word3.bits32;

		dma_unmap_single(geth->dev, mapping,
				 word0.bits.buffer_size, DMA_TO_DEVICE);

		if (word3 & EOF_BIT)
			dev_kfree_skb(txq->skb[c]);

		c++;
		c &= m;

		if (!(word3 & SOF_BIT))
			continue;

		if (!word0.bits.status_tx_ok) {
			errs++;
			continue;
		}

		pkts++;
		bytes += txd->word1.bits.byte_count;

		if (word1.bits32 & TSS_CHECKUM_ENABLE)
			hwchksum++;

		nfrags = word0.bits.desc_count - 1;
		if (nfrags) {
			if (nfrags >= TX_MAX_FRAGS)
				nfrags = TX_MAX_FRAGS - 1;

			u64_stats_update_begin(&port->tx_stats_syncp);
			port->tx_frag_stats[nfrags]++;
			u64_stats_update_end(&port->tx_stats_syncp);
		}
	}

	u64_stats_update_begin(&port->ir_stats_syncp);
	port->stats.tx_errors += errs;
	port->stats.tx_packets += pkts;
	port->stats.tx_bytes += bytes;
	port->tx_hw_csummed += hwchksum;
	u64_stats_update_end(&port->ir_stats_syncp);

	txq->cptr = c;
}