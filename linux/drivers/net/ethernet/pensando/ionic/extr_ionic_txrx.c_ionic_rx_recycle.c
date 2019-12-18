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
struct sk_buff {int dummy; } ;
struct ionic_rxq_desc {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct ionic_queue {TYPE_1__* head; } ;
struct ionic_desc_info {struct ionic_rxq_desc* desc; } ;
struct TYPE_2__ {struct ionic_rxq_desc* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ionic_rx_clean ; 
 int /*<<< orphan*/  ionic_rxq_post (struct ionic_queue*,int,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static void ionic_rx_recycle(struct ionic_queue *q, struct ionic_desc_info *desc_info,
			     struct sk_buff *skb)
{
	struct ionic_rxq_desc *old = desc_info->desc;
	struct ionic_rxq_desc *new = q->head->desc;

	new->addr = old->addr;
	new->len = old->len;

	ionic_rxq_post(q, true, ionic_rx_clean, skb);
}