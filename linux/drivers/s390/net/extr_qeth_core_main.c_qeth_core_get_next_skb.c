#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct qeth_qdio_buffer {struct sk_buff* rx_skb; struct qdio_buffer* buffer; } ;
struct TYPE_9__ {int pdu_length; } ;
struct TYPE_8__ {int length; } ;
struct TYPE_7__ {int id; int pkt_length; } ;
struct TYPE_10__ {TYPE_3__ osn; TYPE_2__ l3; TYPE_1__ l2; } ;
struct qeth_hdr {TYPE_4__ hdr; } ;
struct TYPE_11__ {int rx_sg_cb; scalar_t__ cq; } ;
struct qeth_card {int /*<<< orphan*/  napi; TYPE_5__ options; int /*<<< orphan*/  force_alloc_skb; } ;
struct qdio_buffer_element {int length; struct qeth_hdr* addr; } ;
struct qdio_buffer {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int ETH_HLEN ; 
 int /*<<< orphan*/  IS_OSN (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_HEX (struct qeth_card*,int,struct qdio_buffer*,int) ; 
 int /*<<< orphan*/  QETH_CARD_STAT_ADD (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_CARD_STAT_INC (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 scalar_t__ QETH_CQ_ENABLED ; 
#define  QETH_HEADER_TYPE_LAYER2 130 
#define  QETH_HEADER_TYPE_LAYER3 129 
#define  QETH_HEADER_TYPE_OSN 128 
 int QETH_RX_PULL_LEN ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int min (int,int) ; 
 struct sk_buff* napi_alloc_skb (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  qeth_create_skb_frag (struct qdio_buffer_element*,struct sk_buff*,int,int) ; 
 scalar_t__ qeth_is_last_sbale (struct qdio_buffer_element*) ; 
 int /*<<< orphan*/  rx_dropped ; 
 int /*<<< orphan*/  rx_errors ; 
 int /*<<< orphan*/  rx_sg_frags ; 
 int /*<<< orphan*/  rx_sg_skbs ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,void*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 TYPE_6__* skb_shinfo (struct sk_buff*) ; 

struct sk_buff *qeth_core_get_next_skb(struct qeth_card *card,
		struct qeth_qdio_buffer *qethbuffer,
		struct qdio_buffer_element **__element, int *__offset,
		struct qeth_hdr **hdr)
{
	struct qdio_buffer_element *element = *__element;
	struct qdio_buffer *buffer = qethbuffer->buffer;
	int offset = *__offset;
	struct sk_buff *skb;
	int skb_len = 0;
	void *data_ptr;
	int data_len;
	int headroom = 0;
	int use_rx_sg = 0;

	/* qeth_hdr must not cross element boundaries */
	while (element->length < offset + sizeof(struct qeth_hdr)) {
		if (qeth_is_last_sbale(element))
			return NULL;
		element++;
		offset = 0;
	}
	*hdr = element->addr + offset;

	offset += sizeof(struct qeth_hdr);
	switch ((*hdr)->hdr.l2.id) {
	case QETH_HEADER_TYPE_LAYER2:
		skb_len = (*hdr)->hdr.l2.pkt_length;
		break;
	case QETH_HEADER_TYPE_LAYER3:
		skb_len = (*hdr)->hdr.l3.length;
		headroom = ETH_HLEN;
		break;
	case QETH_HEADER_TYPE_OSN:
		skb_len = (*hdr)->hdr.osn.pdu_length;
		headroom = sizeof(struct qeth_hdr);
		break;
	default:
		break;
	}

	if (!skb_len)
		return NULL;

	if (((skb_len >= card->options.rx_sg_cb) &&
	     !IS_OSN(card) &&
	     (!atomic_read(&card->force_alloc_skb))) ||
	    (card->options.cq == QETH_CQ_ENABLED))
		use_rx_sg = 1;

	if (use_rx_sg && qethbuffer->rx_skb) {
		/* QETH_CQ_ENABLED only: */
		skb = qethbuffer->rx_skb;
		qethbuffer->rx_skb = NULL;
	} else {
		unsigned int linear = (use_rx_sg) ? QETH_RX_PULL_LEN : skb_len;

		skb = napi_alloc_skb(&card->napi, linear + headroom);
	}
	if (!skb)
		goto no_mem;
	if (headroom)
		skb_reserve(skb, headroom);

	data_ptr = element->addr + offset;
	while (skb_len) {
		data_len = min(skb_len, (int)(element->length - offset));
		if (data_len) {
			if (use_rx_sg)
				qeth_create_skb_frag(element, skb, offset,
						     data_len);
			else
				skb_put_data(skb, data_ptr, data_len);
		}
		skb_len -= data_len;
		if (skb_len) {
			if (qeth_is_last_sbale(element)) {
				QETH_CARD_TEXT(card, 4, "unexeob");
				QETH_CARD_HEX(card, 2, buffer, sizeof(void *));
				dev_kfree_skb_any(skb);
				QETH_CARD_STAT_INC(card, rx_errors);
				return NULL;
			}
			element++;
			offset = 0;
			data_ptr = element->addr;
		} else {
			offset += data_len;
		}
	}
	*__element = element;
	*__offset = offset;
	if (use_rx_sg) {
		QETH_CARD_STAT_INC(card, rx_sg_skbs);
		QETH_CARD_STAT_ADD(card, rx_sg_frags,
				   skb_shinfo(skb)->nr_frags);
	}
	return skb;
no_mem:
	if (net_ratelimit()) {
		QETH_CARD_TEXT(card, 2, "noskbmem");
	}
	QETH_CARD_STAT_INC(card, rx_dropped);
	return NULL;
}