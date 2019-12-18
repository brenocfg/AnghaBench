#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct qtnf_vif {int /*<<< orphan*/  high_pri_tx_work; TYPE_2__* mac; int /*<<< orphan*/  high_pri_tx_queue; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  hprio_workqueue; } ;

/* Variables and functions */
 struct qtnf_vif* qtnf_netdev_get_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

void qtnf_packet_send_hi_pri(struct sk_buff *skb)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(skb->dev);

	skb_queue_tail(&vif->high_pri_tx_queue, skb);
	queue_work(vif->mac->bus->hprio_workqueue, &vif->high_pri_tx_work);
}