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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {scalar_t__ qlen; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* flowctrl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct ser_device {TYPE_2__ head; int /*<<< orphan*/  dev; TYPE_1__ common; int /*<<< orphan*/  state; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAIF_FLOW_OFF_SENT ; 
 int /*<<< orphan*/  OFF ; 
 scalar_t__ SEND_QUEUE_HIGH ; 
 int handle_tx (struct ser_device*) ; 
 struct ser_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_tail (TYPE_2__*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int caif_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ser_device *ser;

	BUG_ON(dev == NULL);
	ser = netdev_priv(dev);

	/* Send flow off once, on high water mark */
	if (ser->head.qlen > SEND_QUEUE_HIGH &&
		!test_and_set_bit(CAIF_FLOW_OFF_SENT, &ser->state) &&
		ser->common.flowctrl != NULL)

		ser->common.flowctrl(ser->dev, OFF);

	skb_queue_tail(&ser->head, skb);
	return handle_tx(ser);
}