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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct pkt_gl {scalar_t__ tot_len; scalar_t__ va; } ;
struct cpl_rx_pkt {int dummy; } ;
struct cpl_pass_accept_req {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,scalar_t__) ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,int,scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *copy_gl_to_skb_pkt(const struct pkt_gl *gl,
					  const __be64 *rsp,
					  u32 pktshift)
{
	struct sk_buff *skb;

	/* Allocate space for cpl_pass_accpet_req which will be synthesized by
	 * driver. Once driver synthesizes cpl_pass_accpet_req the skb will go
	 * through the regular cpl_pass_accept_req processing in TOM.
	 */
	skb = alloc_skb(gl->tot_len + sizeof(struct cpl_pass_accept_req)
			- pktshift, GFP_ATOMIC);
	if (unlikely(!skb))
		return NULL;
	__skb_put(skb, gl->tot_len + sizeof(struct cpl_pass_accept_req)
		   - pktshift);
	/* For now we will copy  cpl_rx_pkt in the skb */
	skb_copy_to_linear_data(skb, rsp, sizeof(struct cpl_rx_pkt));
	skb_copy_to_linear_data_offset(skb, sizeof(struct cpl_pass_accept_req)
				       , gl->va + pktshift,
				       gl->tot_len - pktshift);

	return skb;
}