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
struct sk_buff {scalar_t__ protocol; scalar_t__ data; } ;
struct qeth_qdio_out_q {unsigned int max_elements; } ;
struct qeth_hdr {int dummy; } ;
struct qeth_card {int dummy; } ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int E2BIG ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct qeth_hdr* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct qeth_hdr*) ; 
 int /*<<< orphan*/  qeth_core_header_cache ; 
 scalar_t__ qeth_count_elements (struct sk_buff*,unsigned int) ; 
 int qeth_do_send_packet (struct qeth_card*,struct qeth_qdio_out_q*,struct sk_buff*,struct qeth_hdr*,unsigned int,unsigned int,unsigned int) ; 
 int qeth_get_elements_for_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,char*,unsigned int) ; 

__attribute__((used)) static int qeth_l2_xmit_osn(struct qeth_card *card, struct sk_buff *skb,
			    struct qeth_qdio_out_q *queue)
{
	struct qeth_hdr *hdr = (struct qeth_hdr *)skb->data;
	addr_t end = (addr_t)(skb->data + sizeof(*hdr));
	addr_t start = (addr_t)skb->data;
	unsigned int elements = 0;
	unsigned int hd_len = 0;
	int rc;

	if (skb->protocol == htons(ETH_P_IPV6))
		return -EPROTONOSUPPORT;

	if (qeth_get_elements_for_range(start, end) > 1) {
		/* Misaligned HW header, move it to its own buffer element. */
		hdr = kmem_cache_alloc(qeth_core_header_cache, GFP_ATOMIC);
		if (!hdr)
			return -ENOMEM;
		hd_len = sizeof(*hdr);
		skb_copy_from_linear_data(skb, (char *)hdr, hd_len);
		elements++;
	}

	elements += qeth_count_elements(skb, hd_len);
	if (elements > queue->max_elements) {
		rc = -E2BIG;
		goto out;
	}

	rc = qeth_do_send_packet(card, queue, skb, hdr, hd_len, hd_len,
				 elements);
out:
	if (rc && hd_len)
		kmem_cache_free(qeth_core_header_cache, hdr);
	return rc;
}