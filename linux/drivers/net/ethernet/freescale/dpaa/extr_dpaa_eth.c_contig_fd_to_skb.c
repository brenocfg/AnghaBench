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
struct skb_shared_info {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct qm_fd {int /*<<< orphan*/  bpid; } ;
struct dpaa_priv {scalar_t__ rx_headroom; } ;
struct dpaa_bp {scalar_t__ size; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ SKB_DATA_ALIGN (int) ; 
 int /*<<< orphan*/  SMP_CACHE_BYTES ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ WARN_ONCE (int,char*) ; 
 struct sk_buff* build_skb (void*,scalar_t__) ; 
 struct dpaa_bp* dpaa_bpid2pool (int /*<<< orphan*/ ) ; 
 void* phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_fd_addr (struct qm_fd const*) ; 
 int /*<<< orphan*/  qm_fd_get_length (struct qm_fd const*) ; 
 scalar_t__ qm_fd_get_offset (struct qm_fd const*) ; 
 int /*<<< orphan*/  rx_csum_offload (struct dpaa_priv const*,struct qm_fd const*) ; 
 int /*<<< orphan*/  skb_free_frag (void*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *contig_fd_to_skb(const struct dpaa_priv *priv,
					const struct qm_fd *fd)
{
	ssize_t fd_off = qm_fd_get_offset(fd);
	dma_addr_t addr = qm_fd_addr(fd);
	struct dpaa_bp *dpaa_bp;
	struct sk_buff *skb;
	void *vaddr;

	vaddr = phys_to_virt(addr);
	WARN_ON(!IS_ALIGNED((unsigned long)vaddr, SMP_CACHE_BYTES));

	dpaa_bp = dpaa_bpid2pool(fd->bpid);
	if (!dpaa_bp)
		goto free_buffer;

	skb = build_skb(vaddr, dpaa_bp->size +
			SKB_DATA_ALIGN(sizeof(struct skb_shared_info)));
	if (WARN_ONCE(!skb, "Build skb failure on Rx\n"))
		goto free_buffer;
	WARN_ON(fd_off != priv->rx_headroom);
	skb_reserve(skb, fd_off);
	skb_put(skb, qm_fd_get_length(fd));

	skb->ip_summed = rx_csum_offload(priv, fd);

	return skb;

free_buffer:
	skb_free_frag(vaddr);
	return NULL;
}