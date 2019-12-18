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
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct ath10k_snoc_pipe {int /*<<< orphan*/  buf_sz; struct ath10k* hif_ce_state; struct ath10k_ce_pipe* ce_hdl; } ;
struct ath10k_ce_pipe {TYPE_1__* ops; } ;
struct ath10k_ce {int /*<<< orphan*/  ce_lock; } ;
struct ath10k {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  paddr; } ;
struct TYPE_3__ {int (* ce_rx_post_buf ) (struct ath10k_ce_pipe*,struct sk_buff*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__* ATH10K_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WARN_ONCE (unsigned long,char*) ; 
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct ath10k_ce_pipe*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ath10k_snoc_rx_post_buf(struct ath10k_snoc_pipe *pipe)
{
	struct ath10k_ce_pipe *ce_pipe = pipe->ce_hdl;
	struct ath10k *ar = pipe->hif_ce_state;
	struct ath10k_ce *ce = ath10k_ce_priv(ar);
	struct sk_buff *skb;
	dma_addr_t paddr;
	int ret;

	skb = dev_alloc_skb(pipe->buf_sz);
	if (!skb)
		return -ENOMEM;

	WARN_ONCE((unsigned long)skb->data & 3, "unaligned skb");

	paddr = dma_map_single(ar->dev, skb->data,
			       skb->len + skb_tailroom(skb),
			       DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(ar->dev, paddr))) {
		ath10k_warn(ar, "failed to dma map snoc rx buf\n");
		dev_kfree_skb_any(skb);
		return -EIO;
	}

	ATH10K_SKB_RXCB(skb)->paddr = paddr;

	spin_lock_bh(&ce->ce_lock);
	ret = ce_pipe->ops->ce_rx_post_buf(ce_pipe, skb, paddr);
	spin_unlock_bh(&ce->ce_lock);
	if (ret) {
		dma_unmap_single(ar->dev, paddr, skb->len + skb_tailroom(skb),
				 DMA_FROM_DEVICE);
		dev_kfree_skb_any(skb);
		return ret;
	}

	return 0;
}