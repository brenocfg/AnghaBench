#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tso_state {unsigned int ip_off; unsigned int tcp_off; unsigned int header_len; unsigned int in_len; scalar_t__ protocol; unsigned int ip_base_len; unsigned int header_unmap_len; scalar_t__ unmap_len; void* dma_addr; void* header_dma_addr; scalar_t__ out_len; int /*<<< orphan*/  seqnum; scalar_t__ ipv4_id; } ;
struct sk_buff {unsigned int data; scalar_t__ len; } ;
struct efx_tx_queue {int dummy; } ;
struct efx_nic {TYPE_1__* pci_dev; } ;
struct device {int dummy; } ;
typedef  void* dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {unsigned int doff; int /*<<< orphan*/  rst; int /*<<< orphan*/  syn; int /*<<< orphan*/  urg; int /*<<< orphan*/  seq; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  EFX_WARN_ON_ONCE_PARANOID (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 void* dma_map_single (struct device*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (struct device*,void*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_3__* ip_hdr (struct sk_buff const*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 unsigned int skb_headlen (struct sk_buff const*) ; 
 unsigned int skb_network_header (struct sk_buff const*) ; 
 unsigned int skb_transport_header (struct sk_buff const*) ; 
 TYPE_2__* tcp_hdr (struct sk_buff const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tso_start(struct tso_state *st, struct efx_nic *efx,
		     struct efx_tx_queue *tx_queue,
		     const struct sk_buff *skb)
{
	struct device *dma_dev = &efx->pci_dev->dev;
	unsigned int header_len, in_len;
	dma_addr_t dma_addr;

	st->ip_off = skb_network_header(skb) - skb->data;
	st->tcp_off = skb_transport_header(skb) - skb->data;
	header_len = st->tcp_off + (tcp_hdr(skb)->doff << 2u);
	in_len = skb_headlen(skb) - header_len;
	st->header_len = header_len;
	st->in_len = in_len;
	if (st->protocol == htons(ETH_P_IP)) {
		st->ip_base_len = st->header_len - st->ip_off;
		st->ipv4_id = ntohs(ip_hdr(skb)->id);
	} else {
		st->ip_base_len = st->header_len - st->tcp_off;
		st->ipv4_id = 0;
	}
	st->seqnum = ntohl(tcp_hdr(skb)->seq);

	EFX_WARN_ON_ONCE_PARANOID(tcp_hdr(skb)->urg);
	EFX_WARN_ON_ONCE_PARANOID(tcp_hdr(skb)->syn);
	EFX_WARN_ON_ONCE_PARANOID(tcp_hdr(skb)->rst);

	st->out_len = skb->len - header_len;

	dma_addr = dma_map_single(dma_dev, skb->data,
				  skb_headlen(skb), DMA_TO_DEVICE);
	st->header_dma_addr = dma_addr;
	st->header_unmap_len = skb_headlen(skb);
	st->dma_addr = dma_addr + header_len;
	st->unmap_len = 0;

	return unlikely(dma_mapping_error(dma_dev, dma_addr)) ? -ENOMEM : 0;
}