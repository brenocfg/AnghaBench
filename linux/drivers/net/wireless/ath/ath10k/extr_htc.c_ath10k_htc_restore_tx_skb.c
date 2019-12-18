#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; } ;
struct ath10k_skb_cb {int /*<<< orphan*/  paddr; } ;
struct ath10k_htc_hdr {int dummy; } ;
struct ath10k_htc {TYPE_2__* ar; } ;
struct TYPE_3__ {scalar_t__ dev_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__ bus_param; } ;

/* Variables and functions */
 scalar_t__ ATH10K_DEV_TYPE_HL ; 
 struct ath10k_skb_cb* ATH10K_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static inline void ath10k_htc_restore_tx_skb(struct ath10k_htc *htc,
					     struct sk_buff *skb)
{
	struct ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(skb);

	if (htc->ar->bus_param.dev_type != ATH10K_DEV_TYPE_HL)
		dma_unmap_single(htc->ar->dev, skb_cb->paddr, skb->len, DMA_TO_DEVICE);
	skb_pull(skb, sizeof(struct ath10k_htc_hdr));
}