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
struct sk_buff {int dummy; } ;
struct qeth_qdio_out_q {int dummy; } ;
struct qeth_hdr_tso {int dummy; } ;
struct qeth_hdr {int dummy; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  qeth_l3_fill_header ; 
 int /*<<< orphan*/  qeth_l3_fixup_headers (struct sk_buff*) ; 
 int qeth_xmit (struct qeth_card*,struct sk_buff*,struct qeth_qdio_out_q*,int,int /*<<< orphan*/ ) ; 
 int skb_cow_head (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int qeth_l3_xmit(struct qeth_card *card, struct sk_buff *skb,
			struct qeth_qdio_out_q *queue, int ipv)
{
	unsigned int hw_hdr_len;
	int rc;

	/* re-use the L2 header area for the HW header: */
	hw_hdr_len = skb_is_gso(skb) ? sizeof(struct qeth_hdr_tso) :
				       sizeof(struct qeth_hdr);
	rc = skb_cow_head(skb, hw_hdr_len - ETH_HLEN);
	if (rc)
		return rc;
	skb_pull(skb, ETH_HLEN);

	qeth_l3_fixup_headers(skb);
	return qeth_xmit(card, skb, queue, ipv, qeth_l3_fill_header);
}