#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; int /*<<< orphan*/  dev; } ;
struct gelic_descr {int /*<<< orphan*/  next; scalar_t__ next_descr_addr; scalar_t__ data_status; struct sk_buff* skb; void* buf_size; void* buf_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  head; } ;
struct gelic_card {TYPE_2__ tx_chain; TYPE_1__* vlan; scalar_t__ vlan_required; } ;
typedef  enum gelic_port_type { ____Placeholder_gelic_port_type } gelic_port_type ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int type; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctodev (struct gelic_card*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelic_descr_set_tx_cmdstat (struct gelic_descr*,struct sk_buff*) ; 
 struct sk_buff* gelic_put_vlan_tag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_3__* netdev_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gelic_descr_prepare_tx(struct gelic_card *card,
				  struct gelic_descr *descr,
				  struct sk_buff *skb)
{
	dma_addr_t buf;

	if (card->vlan_required) {
		struct sk_buff *skb_tmp;
		enum gelic_port_type type;

		type = netdev_port(skb->dev)->type;
		skb_tmp = gelic_put_vlan_tag(skb,
					     card->vlan[type].tx);
		if (!skb_tmp)
			return -ENOMEM;
		skb = skb_tmp;
	}

	buf = dma_map_single(ctodev(card), skb->data, skb->len, DMA_TO_DEVICE);

	if (!buf) {
		dev_err(ctodev(card),
			"dma map 2 failed (%p, %i). Dropping packet\n",
			skb->data, skb->len);
		return -ENOMEM;
	}

	descr->buf_addr = cpu_to_be32(buf);
	descr->buf_size = cpu_to_be32(skb->len);
	descr->skb = skb;
	descr->data_status = 0;
	descr->next_descr_addr = 0; /* terminate hw descr */
	gelic_descr_set_tx_cmdstat(descr, skb);

	/* bump free descriptor pointer */
	card->tx_chain.head = descr->next;
	return 0;
}