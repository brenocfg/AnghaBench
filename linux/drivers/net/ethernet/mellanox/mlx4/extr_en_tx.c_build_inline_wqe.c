#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct skb_shared_info {int /*<<< orphan*/ * frags; scalar_t__ nr_frags; } ;
struct sk_buff {int len; } ;
struct mlx4_wqe_inline_seg {void* byte_count; } ;
struct mlx4_en_tx_desc {struct mlx4_wqe_inline_seg inl; } ;

/* Variables and functions */
 int CTRL_SIZE ; 
 int MIN_PKT_LEN ; 
 int MLX4_INLINE_ALIGN ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff const*,struct mlx4_wqe_inline_seg*,int) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data_offset (struct sk_buff const*,int,struct mlx4_wqe_inline_seg*,unsigned int) ; 
 int skb_frag_size (int /*<<< orphan*/ *) ; 
 unsigned int skb_headlen (struct sk_buff const*) ; 

__attribute__((used)) static void build_inline_wqe(struct mlx4_en_tx_desc *tx_desc,
			     const struct sk_buff *skb,
			     const struct skb_shared_info *shinfo,
			     void *fragptr)
{
	struct mlx4_wqe_inline_seg *inl = &tx_desc->inl;
	int spc = MLX4_INLINE_ALIGN - CTRL_SIZE - sizeof(*inl);
	unsigned int hlen = skb_headlen(skb);

	if (skb->len <= spc) {
		if (likely(skb->len >= MIN_PKT_LEN)) {
			inl->byte_count = cpu_to_be32(1 << 31 | skb->len);
		} else {
			inl->byte_count = cpu_to_be32(1 << 31 | MIN_PKT_LEN);
			memset(((void *)(inl + 1)) + skb->len, 0,
			       MIN_PKT_LEN - skb->len);
		}
		skb_copy_from_linear_data(skb, inl + 1, hlen);
		if (shinfo->nr_frags)
			memcpy(((void *)(inl + 1)) + hlen, fragptr,
			       skb_frag_size(&shinfo->frags[0]));

	} else {
		inl->byte_count = cpu_to_be32(1 << 31 | spc);
		if (hlen <= spc) {
			skb_copy_from_linear_data(skb, inl + 1, hlen);
			if (hlen < spc) {
				memcpy(((void *)(inl + 1)) + hlen,
				       fragptr, spc - hlen);
				fragptr +=  spc - hlen;
			}
			inl = (void *) (inl + 1) + spc;
			memcpy(((void *)(inl + 1)), fragptr, skb->len - spc);
		} else {
			skb_copy_from_linear_data(skb, inl + 1, spc);
			inl = (void *) (inl + 1) + spc;
			skb_copy_from_linear_data_offset(skb, spc, inl + 1,
							 hlen - spc);
			if (shinfo->nr_frags)
				memcpy(((void *)(inl + 1)) + hlen - spc,
				       fragptr,
				       skb_frag_size(&shinfo->frags[0]));
		}

		dma_wmb();
		inl->byte_count = cpu_to_be32(1 << 31 | (skb->len - spc));
	}
}