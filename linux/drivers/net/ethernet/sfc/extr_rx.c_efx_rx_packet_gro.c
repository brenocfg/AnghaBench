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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int csum_level; unsigned int truesize; int /*<<< orphan*/  len; int /*<<< orphan*/  data_len; int /*<<< orphan*/  ip_summed; } ;
struct napi_struct {int dummy; } ;
struct efx_rx_queue {int dummy; } ;
struct efx_rx_buffer {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/ * page; int /*<<< orphan*/  page_offset; } ;
struct efx_nic {unsigned int rx_buffer_truesize; TYPE_1__* net_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  core_index; } ;
struct efx_channel {TYPE_3__ rx_queue; struct efx_nic* efx; struct napi_struct napi_str; } ;
struct TYPE_5__ {unsigned int nr_frags; } ;
struct TYPE_4__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int EFX_RX_PKT_CSUMMED ; 
 int EFX_RX_PKT_CSUM_LEVEL ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L3 ; 
 struct efx_rx_queue* efx_channel_get_rx_queue (struct efx_channel*) ; 
 int /*<<< orphan*/  efx_free_rx_buffers (struct efx_rx_queue*,struct efx_rx_buffer*,unsigned int) ; 
 int /*<<< orphan*/  efx_rx_buf_hash (struct efx_nic*,int /*<<< orphan*/ *) ; 
 struct efx_rx_buffer* efx_rx_buf_next (TYPE_3__*,struct efx_rx_buffer*) ; 
 struct sk_buff* napi_get_frags (struct napi_struct*) ; 
 int /*<<< orphan*/  napi_gro_frags (struct napi_struct*) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
efx_rx_packet_gro(struct efx_channel *channel, struct efx_rx_buffer *rx_buf,
		  unsigned int n_frags, u8 *eh)
{
	struct napi_struct *napi = &channel->napi_str;
	struct efx_nic *efx = channel->efx;
	struct sk_buff *skb;

	skb = napi_get_frags(napi);
	if (unlikely(!skb)) {
		struct efx_rx_queue *rx_queue;

		rx_queue = efx_channel_get_rx_queue(channel);
		efx_free_rx_buffers(rx_queue, rx_buf, n_frags);
		return;
	}

	if (efx->net_dev->features & NETIF_F_RXHASH)
		skb_set_hash(skb, efx_rx_buf_hash(efx, eh),
			     PKT_HASH_TYPE_L3);
	skb->ip_summed = ((rx_buf->flags & EFX_RX_PKT_CSUMMED) ?
			  CHECKSUM_UNNECESSARY : CHECKSUM_NONE);
	skb->csum_level = !!(rx_buf->flags & EFX_RX_PKT_CSUM_LEVEL);

	for (;;) {
		skb_fill_page_desc(skb, skb_shinfo(skb)->nr_frags,
				   rx_buf->page, rx_buf->page_offset,
				   rx_buf->len);
		rx_buf->page = NULL;
		skb->len += rx_buf->len;
		if (skb_shinfo(skb)->nr_frags == n_frags)
			break;

		rx_buf = efx_rx_buf_next(&channel->rx_queue, rx_buf);
	}

	skb->data_len = skb->len;
	skb->truesize += n_frags * efx->rx_buffer_truesize;

	skb_record_rx_queue(skb, channel->rx_queue.core_index);

	napi_gro_frags(napi);
}