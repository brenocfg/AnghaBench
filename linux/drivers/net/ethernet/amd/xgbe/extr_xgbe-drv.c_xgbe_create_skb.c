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
struct TYPE_4__ {int pages_offset; int /*<<< orphan*/  pages; } ;
struct TYPE_5__ {TYPE_1__ pa; int /*<<< orphan*/  dma_len; int /*<<< orphan*/  dma_off; int /*<<< orphan*/  dma_base; } ;
struct TYPE_6__ {TYPE_2__ hdr; } ;
struct xgbe_ring_data {TYPE_3__ rx; } ;
struct xgbe_prv_data {int /*<<< orphan*/  dev; } ;
struct sk_buff {int dummy; } ;
struct napi_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_sync_single_range_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* napi_alloc_skb (struct napi_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static struct sk_buff *xgbe_create_skb(struct xgbe_prv_data *pdata,
				       struct napi_struct *napi,
				       struct xgbe_ring_data *rdata,
				       unsigned int len)
{
	struct sk_buff *skb;
	u8 *packet;

	skb = napi_alloc_skb(napi, rdata->rx.hdr.dma_len);
	if (!skb)
		return NULL;

	/* Pull in the header buffer which may contain just the header
	 * or the header plus data
	 */
	dma_sync_single_range_for_cpu(pdata->dev, rdata->rx.hdr.dma_base,
				      rdata->rx.hdr.dma_off,
				      rdata->rx.hdr.dma_len, DMA_FROM_DEVICE);

	packet = page_address(rdata->rx.hdr.pa.pages) +
		 rdata->rx.hdr.pa.pages_offset;
	skb_copy_to_linear_data(skb, packet, len);
	skb_put(skb, len);

	return skb;
}