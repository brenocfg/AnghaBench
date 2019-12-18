#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {void* data; } ;
struct qeth_qdio_out_buffer {int next_element_to_fill; int* is_header; int /*<<< orphan*/  skb_list; struct qdio_buffer* buffer; } ;
struct qeth_hdr {int dummy; } ;
struct qdio_buffer {TYPE_1__* element; } ;
struct TYPE_2__ {unsigned int length; int /*<<< orphan*/  eflags; struct qeth_hdr* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBAL_EFLAGS_FIRST_FRAG ; 
 unsigned int __qeth_fill_buffer (struct sk_buff*,struct qeth_qdio_out_buffer*,int,unsigned int) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static unsigned int qeth_fill_buffer(struct qeth_qdio_out_buffer *buf,
				     struct sk_buff *skb, struct qeth_hdr *hdr,
				     unsigned int offset, unsigned int hd_len)
{
	struct qdio_buffer *buffer = buf->buffer;
	bool is_first_elem = true;

	__skb_queue_tail(&buf->skb_list, skb);

	/* build dedicated header element */
	if (hd_len) {
		int element = buf->next_element_to_fill;
		is_first_elem = false;

		buffer->element[element].addr = hdr;
		buffer->element[element].length = hd_len;
		buffer->element[element].eflags = SBAL_EFLAGS_FIRST_FRAG;
		/* remember to free cache-allocated qeth_hdr: */
		buf->is_header[element] = ((void *)hdr != skb->data);
		buf->next_element_to_fill++;
	}

	return __qeth_fill_buffer(skb, buf, is_first_elem, offset);
}