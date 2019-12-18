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
struct ulptx_sge_pair {void** addr; void** len; } ;
typedef  struct ulptx_sge_pair u8 ;
typedef  scalar_t__ u64 ;
struct ulptx_sgl {struct ulptx_sge_pair* sge; void* cmd_nsge; void* addr0; void* len0; } ;
struct skb_shared_info {unsigned int nr_frags; int /*<<< orphan*/ * frags; } ;
struct sk_buff {int dummy; } ;
struct sge_txq {struct ulptx_sge_pair* desc; scalar_t__ stat; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int MAX_SKB_FRAGS ; 
 unsigned int ULPTX_CMD_V (int /*<<< orphan*/ ) ; 
 unsigned int ULPTX_NSGE_V (unsigned int) ; 
 int /*<<< orphan*/  ULP_TX_SC_DSGL ; 
 void* cpu_to_be32 (unsigned int) ; 
 void* cpu_to_be64 (scalar_t__ const) ; 
 void* htonl (unsigned int) ; 
 scalar_t__ likely (unsigned int) ; 
 int /*<<< orphan*/  memcpy (struct ulptx_sge_pair*,struct ulptx_sge_pair*,unsigned int) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/ *) ; 
 unsigned int skb_headlen (struct sk_buff const*) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff const*) ; 
 scalar_t__ unlikely (int) ; 

void cxgb4_write_sgl(const struct sk_buff *skb, struct sge_txq *q,
		     struct ulptx_sgl *sgl, u64 *end, unsigned int start,
		     const dma_addr_t *addr)
{
	unsigned int i, len;
	struct ulptx_sge_pair *to;
	const struct skb_shared_info *si = skb_shinfo(skb);
	unsigned int nfrags = si->nr_frags;
	struct ulptx_sge_pair buf[MAX_SKB_FRAGS / 2 + 1];

	len = skb_headlen(skb) - start;
	if (likely(len)) {
		sgl->len0 = htonl(len);
		sgl->addr0 = cpu_to_be64(addr[0] + start);
		nfrags++;
	} else {
		sgl->len0 = htonl(skb_frag_size(&si->frags[0]));
		sgl->addr0 = cpu_to_be64(addr[1]);
	}

	sgl->cmd_nsge = htonl(ULPTX_CMD_V(ULP_TX_SC_DSGL) |
			      ULPTX_NSGE_V(nfrags));
	if (likely(--nfrags == 0))
		return;
	/*
	 * Most of the complexity below deals with the possibility we hit the
	 * end of the queue in the middle of writing the SGL.  For this case
	 * only we create the SGL in a temporary buffer and then copy it.
	 */
	to = (u8 *)end > (u8 *)q->stat ? buf : sgl->sge;

	for (i = (nfrags != si->nr_frags); nfrags >= 2; nfrags -= 2, to++) {
		to->len[0] = cpu_to_be32(skb_frag_size(&si->frags[i]));
		to->len[1] = cpu_to_be32(skb_frag_size(&si->frags[++i]));
		to->addr[0] = cpu_to_be64(addr[i]);
		to->addr[1] = cpu_to_be64(addr[++i]);
	}
	if (nfrags) {
		to->len[0] = cpu_to_be32(skb_frag_size(&si->frags[i]));
		to->len[1] = cpu_to_be32(0);
		to->addr[0] = cpu_to_be64(addr[i + 1]);
	}
	if (unlikely((u8 *)end > (u8 *)q->stat)) {
		unsigned int part0 = (u8 *)q->stat - (u8 *)sgl->sge, part1;

		if (likely(part0))
			memcpy(sgl->sge, buf, part0);
		part1 = (u8 *)end - (u8 *)q->stat;
		memcpy(q->desc, (u8 *)buf + part0, part1);
		end = (void *)q->desc + part1;
	}
	if ((uintptr_t)end & 8)           /* 0-pad to multiple of 16 */
		*end = 0;
}