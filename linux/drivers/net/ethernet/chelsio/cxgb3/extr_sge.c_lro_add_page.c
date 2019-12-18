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
struct sk_buff {int len; int data_len; int truesize; int /*<<< orphan*/  ip_summed; } ;
struct sge_qset {int nomem; int /*<<< orphan*/  napi; int /*<<< orphan*/ * port_stats; struct cpl_rx_pkt* lro_va; TYPE_5__* netdev; } ;
struct TYPE_6__ {scalar_t__ page; } ;
struct sge_fl {size_t cidx; int /*<<< orphan*/  alloc_size; TYPE_1__ pg_chunk; scalar_t__ buf_size; int /*<<< orphan*/  credits; struct rx_sw_desc* sdesc; } ;
struct TYPE_7__ {scalar_t__ page; int offset; struct cpl_rx_pkt* va; int /*<<< orphan*/  mapping; int /*<<< orphan*/ * p_cnt; } ;
struct rx_sw_desc {TYPE_2__ pg_chunk; } ;
struct port_info {size_t first_qset; } ;
struct cpl_rx_pkt {scalar_t__ csum; int /*<<< orphan*/  vlan; scalar_t__ vlan_valid; scalar_t__ csum_valid; } ;
struct TYPE_8__ {struct sge_qset* qs; } ;
struct adapter {TYPE_3__ sge; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_10__ {int features; } ;
struct TYPE_9__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int ETH_P_8021Q ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 scalar_t__ SGE_PG_RSVD ; 
 size_t SGE_PSTAT_RX_CSUM_GOOD ; 
 size_t SGE_PSTAT_VLANEX ; 
 int /*<<< orphan*/  __skb_frag_set_page (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_addr ; 
 int /*<<< orphan*/  dma_unmap_addr (struct rx_sw_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int) ; 
 struct sk_buff* napi_get_frags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_gro_frags (int /*<<< orphan*/ *) ; 
 struct port_info* netdev_priv (TYPE_5__*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (scalar_t__) ; 
 int /*<<< orphan*/  skb_frag_off_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_frag_size_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void lro_add_page(struct adapter *adap, struct sge_qset *qs,
			 struct sge_fl *fl, int len, int complete)
{
	struct rx_sw_desc *sd = &fl->sdesc[fl->cidx];
	struct port_info *pi = netdev_priv(qs->netdev);
	struct sk_buff *skb = NULL;
	struct cpl_rx_pkt *cpl;
	skb_frag_t *rx_frag;
	int nr_frags;
	int offset = 0;

	if (!qs->nomem) {
		skb = napi_get_frags(&qs->napi);
		qs->nomem = !skb;
	}

	fl->credits--;

	pci_dma_sync_single_for_cpu(adap->pdev,
				    dma_unmap_addr(sd, dma_addr),
				    fl->buf_size - SGE_PG_RSVD,
				    PCI_DMA_FROMDEVICE);

	(*sd->pg_chunk.p_cnt)--;
	if (!*sd->pg_chunk.p_cnt && sd->pg_chunk.page != fl->pg_chunk.page)
		pci_unmap_page(adap->pdev,
			       sd->pg_chunk.mapping,
			       fl->alloc_size,
			       PCI_DMA_FROMDEVICE);

	if (!skb) {
		put_page(sd->pg_chunk.page);
		if (complete)
			qs->nomem = 0;
		return;
	}

	rx_frag = skb_shinfo(skb)->frags;
	nr_frags = skb_shinfo(skb)->nr_frags;

	if (!nr_frags) {
		offset = 2 + sizeof(struct cpl_rx_pkt);
		cpl = qs->lro_va = sd->pg_chunk.va + 2;

		if ((qs->netdev->features & NETIF_F_RXCSUM) &&
		     cpl->csum_valid && cpl->csum == htons(0xffff)) {
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			qs->port_stats[SGE_PSTAT_RX_CSUM_GOOD]++;
		} else
			skb->ip_summed = CHECKSUM_NONE;
	} else
		cpl = qs->lro_va;

	len -= offset;

	rx_frag += nr_frags;
	__skb_frag_set_page(rx_frag, sd->pg_chunk.page);
	skb_frag_off_set(rx_frag, sd->pg_chunk.offset + offset);
	skb_frag_size_set(rx_frag, len);

	skb->len += len;
	skb->data_len += len;
	skb->truesize += len;
	skb_shinfo(skb)->nr_frags++;

	if (!complete)
		return;

	skb_record_rx_queue(skb, qs - &adap->sge.qs[pi->first_qset]);

	if (cpl->vlan_valid) {
		qs->port_stats[SGE_PSTAT_VLANEX]++;
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), ntohs(cpl->vlan));
	}
	napi_gro_frags(&qs->napi);
}