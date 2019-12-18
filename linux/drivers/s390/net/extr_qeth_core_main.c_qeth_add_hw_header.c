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
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct qeth_qdio_out_q {unsigned int max_elements; } ;
struct qeth_hdr {int dummy; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int E2BIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ PAGE_ALIGNED (scalar_t__) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,unsigned int const,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int QETH_HDR_CACHE_OBJ_SIZE ; 
 int /*<<< orphan*/  QETH_TXQ_STAT_INC (struct qeth_qdio_out_q*,int /*<<< orphan*/ ) ; 
 struct qeth_hdr* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_core_header_cache ; 
 int qeth_count_elements (struct sk_buff*,unsigned int) ; 
 int qeth_get_elements_for_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,char*,unsigned int) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_nonlinear (struct sk_buff*) ; 
 int skb_linearize (struct sk_buff*) ; 
 struct qeth_hdr* skb_push (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skbs_linearized ; 
 int /*<<< orphan*/  skbs_linearized_fail ; 

__attribute__((used)) static int qeth_add_hw_header(struct qeth_qdio_out_q *queue,
			      struct sk_buff *skb, struct qeth_hdr **hdr,
			      unsigned int hdr_len, unsigned int proto_len,
			      unsigned int *elements)
{
	const unsigned int contiguous = proto_len ? proto_len : 1;
	const unsigned int max_elements = queue->max_elements;
	unsigned int __elements;
	addr_t start, end;
	bool push_ok;
	int rc;

check_layout:
	start = (addr_t)skb->data - hdr_len;
	end = (addr_t)skb->data;

	if (qeth_get_elements_for_range(start, end + contiguous) == 1) {
		/* Push HW header into same page as first protocol header. */
		push_ok = true;
		/* ... but TSO always needs a separate element for headers: */
		if (skb_is_gso(skb))
			__elements = 1 + qeth_count_elements(skb, proto_len);
		else
			__elements = qeth_count_elements(skb, 0);
	} else if (!proto_len && PAGE_ALIGNED(skb->data)) {
		/* Push HW header into preceding page, flush with skb->data. */
		push_ok = true;
		__elements = 1 + qeth_count_elements(skb, 0);
	} else {
		/* Use header cache, copy protocol headers up. */
		push_ok = false;
		__elements = 1 + qeth_count_elements(skb, proto_len);
	}

	/* Compress skb to fit into one IO buffer: */
	if (__elements > max_elements) {
		if (!skb_is_nonlinear(skb)) {
			/* Drop it, no easy way of shrinking it further. */
			QETH_DBF_MESSAGE(2, "Dropped an oversized skb (Max Elements=%u / Actual=%u / Length=%u).\n",
					 max_elements, __elements, skb->len);
			return -E2BIG;
		}

		rc = skb_linearize(skb);
		if (rc) {
			QETH_TXQ_STAT_INC(queue, skbs_linearized_fail);
			return rc;
		}

		QETH_TXQ_STAT_INC(queue, skbs_linearized);
		/* Linearization changed the layout, re-evaluate: */
		goto check_layout;
	}

	*elements = __elements;
	/* Add the header: */
	if (push_ok) {
		*hdr = skb_push(skb, hdr_len);
		return hdr_len;
	}
	/* fall back */
	if (hdr_len + proto_len > QETH_HDR_CACHE_OBJ_SIZE)
		return -E2BIG;
	*hdr = kmem_cache_alloc(qeth_core_header_cache, GFP_ATOMIC);
	if (!*hdr)
		return -ENOMEM;
	/* Copy protocol headers behind HW header: */
	skb_copy_from_linear_data(skb, ((char *)*hdr) + hdr_len, proto_len);
	return 0;
}