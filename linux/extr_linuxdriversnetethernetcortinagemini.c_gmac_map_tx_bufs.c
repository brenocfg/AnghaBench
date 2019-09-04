#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct skb_shared_info {int nr_frags; TYPE_6__* frags; } ;
struct sk_buff {scalar_t__ protocol; unsigned int len; scalar_t__ ip_summed; void* data; } ;
struct net_device {unsigned short mtu; } ;
struct gmac_txq {struct gmac_txdesc* ring; struct sk_buff** skb; } ;
struct TYPE_13__ {int /*<<< orphan*/  buffer_size; } ;
struct TYPE_14__ {unsigned int bits32; TYPE_4__ bits; } ;
struct TYPE_12__ {int /*<<< orphan*/  buf_adr; } ;
struct TYPE_11__ {unsigned int bits32; } ;
struct TYPE_10__ {unsigned int bits32; } ;
struct gmac_txdesc {TYPE_5__ word0; TYPE_3__ word2; TYPE_2__ word3; TYPE_1__ word1; } ;
struct gemini_ethernet_port {int txq_order; struct gemini_ethernet* geth; } ;
struct gemini_ethernet {int /*<<< orphan*/  dev; } ;
struct TYPE_15__ {int page_offset; unsigned int size; } ;
typedef  TYPE_6__ skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_17__ {scalar_t__ protocol; } ;
struct TYPE_16__ {scalar_t__ nexthdr; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_NONE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 unsigned int EOF_BIT ; 
 unsigned short ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ IPPROTO_TCP ; 
 unsigned int MTU_SIZE_BIT_MASK ; 
 unsigned int SOF_BIT ; 
 unsigned int TSS_IPV6_ENABLE_BIT ; 
 unsigned int TSS_IP_CHKSUM_BIT ; 
 unsigned int TSS_MTU_ENABLE_BIT ; 
 unsigned int TSS_TCP_CHKSUM_BIT ; 
 unsigned int TSS_UDP_CHKSUM_BIT ; 
 scalar_t__ VLAN_HLEN ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_9__* ip_hdr (struct sk_buff*) ; 
 TYPE_8__* ipv6_hdr (struct sk_buff*) ; 
 struct gemini_ethernet_port* netdev_priv (struct net_device*) ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_page (TYPE_6__*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int gmac_map_tx_bufs(struct net_device *netdev, struct sk_buff *skb,
			    struct gmac_txq *txq, unsigned short *desc)
{
	struct gemini_ethernet_port *port = netdev_priv(netdev);
	struct skb_shared_info *skb_si =  skb_shinfo(skb);
	unsigned short m = (1 << port->txq_order) - 1;
	short frag, last_frag = skb_si->nr_frags - 1;
	struct gemini_ethernet *geth = port->geth;
	unsigned int word1, word3, buflen;
	unsigned short w = *desc;
	struct gmac_txdesc *txd;
	skb_frag_t *skb_frag;
	dma_addr_t mapping;
	unsigned short mtu;
	void *buffer;

	mtu  = ETH_HLEN;
	mtu += netdev->mtu;
	if (skb->protocol == htons(ETH_P_8021Q))
		mtu += VLAN_HLEN;

	word1 = skb->len;
	word3 = SOF_BIT;

	if (word1 > mtu) {
		word1 |= TSS_MTU_ENABLE_BIT;
		word3 |= mtu;
	}

	if (skb->ip_summed != CHECKSUM_NONE) {
		int tcp = 0;

		if (skb->protocol == htons(ETH_P_IP)) {
			word1 |= TSS_IP_CHKSUM_BIT;
			tcp = ip_hdr(skb)->protocol == IPPROTO_TCP;
		} else { /* IPv6 */
			word1 |= TSS_IPV6_ENABLE_BIT;
			tcp = ipv6_hdr(skb)->nexthdr == IPPROTO_TCP;
		}

		word1 |= tcp ? TSS_TCP_CHKSUM_BIT : TSS_UDP_CHKSUM_BIT;
	}

	frag = -1;
	while (frag <= last_frag) {
		if (frag == -1) {
			buffer = skb->data;
			buflen = skb_headlen(skb);
		} else {
			skb_frag = skb_si->frags + frag;
			buffer = page_address(skb_frag_page(skb_frag)) +
				 skb_frag->page_offset;
			buflen = skb_frag->size;
		}

		if (frag == last_frag) {
			word3 |= EOF_BIT;
			txq->skb[w] = skb;
		}

		mapping = dma_map_single(geth->dev, buffer, buflen,
					 DMA_TO_DEVICE);
		if (dma_mapping_error(geth->dev, mapping))
			goto map_error;

		txd = txq->ring + w;
		txd->word0.bits32 = buflen;
		txd->word1.bits32 = word1;
		txd->word2.buf_adr = mapping;
		txd->word3.bits32 = word3;

		word3 &= MTU_SIZE_BIT_MASK;
		w++;
		w &= m;
		frag++;
	}

	*desc = w;
	return 0;

map_error:
	while (w != *desc) {
		w--;
		w &= m;

		dma_unmap_page(geth->dev, txq->ring[w].word2.buf_adr,
			       txq->ring[w].word0.bits.buffer_size,
			       DMA_TO_DEVICE);
	}
	return -ENOMEM;
}