#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned int len; int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; } ;
struct TYPE_9__ {int id; } ;
struct TYPE_10__ {TYPE_4__ l3; } ;
struct qeth_hdr {TYPE_5__ hdr; } ;
struct TYPE_8__ {size_t b_index; int /*<<< orphan*/  e_offset; int /*<<< orphan*/  b_element; } ;
struct TYPE_7__ {TYPE_1__* in_q; } ;
struct qeth_card {int /*<<< orphan*/  napi; TYPE_3__ rx; TYPE_2__ qdio; } ;
struct TYPE_6__ {int /*<<< orphan*/ * bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  QETH_CARD_STAT_ADD (struct qeth_card*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  QETH_CARD_STAT_INC (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,struct qeth_hdr*,int) ; 
#define  QETH_HEADER_TYPE_LAYER2 129 
#define  QETH_HEADER_TYPE_LAYER3 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* qeth_core_get_next_skb (struct qeth_card*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct qeth_hdr**) ; 
 int /*<<< orphan*/  qeth_l3_rebuild_skb (struct qeth_card*,struct sk_buff*,struct qeth_hdr*) ; 
 int /*<<< orphan*/  rx_bytes ; 
 int /*<<< orphan*/  rx_packets ; 

__attribute__((used)) static int qeth_l3_process_inbound_buffer(struct qeth_card *card,
				int budget, int *done)
{
	int work_done = 0;
	struct sk_buff *skb;
	struct qeth_hdr *hdr;
	unsigned int len;

	*done = 0;
	WARN_ON_ONCE(!budget);
	while (budget) {
		skb = qeth_core_get_next_skb(card,
			&card->qdio.in_q->bufs[card->rx.b_index],
			&card->rx.b_element, &card->rx.e_offset, &hdr);
		if (!skb) {
			*done = 1;
			break;
		}
		switch (hdr->hdr.l3.id) {
		case QETH_HEADER_TYPE_LAYER3:
			qeth_l3_rebuild_skb(card, skb, hdr);
			/* fall through */
		case QETH_HEADER_TYPE_LAYER2: /* for HiperSockets sniffer */
			skb->protocol = eth_type_trans(skb, skb->dev);
			len = skb->len;
			napi_gro_receive(&card->napi, skb);
			break;
		default:
			dev_kfree_skb_any(skb);
			QETH_CARD_TEXT(card, 3, "inbunkno");
			QETH_DBF_HEX(CTRL, 3, hdr, sizeof(*hdr));
			continue;
		}
		work_done++;
		budget--;
		QETH_CARD_STAT_INC(card, rx_packets);
		QETH_CARD_STAT_ADD(card, rx_bytes, len);
	}
	return work_done;
}