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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct qeth_card {int dummy; } ;
struct net_device {struct qeth_card* ml_priv; } ;

/* Variables and functions */
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_get_ether_cast_type (struct sk_buff*) ; 
 int /*<<< orphan*/  qeth_get_priority_queue (struct qeth_card*,struct sk_buff*) ; 
 int /*<<< orphan*/  qeth_iqd_select_queue (struct net_device*,struct sk_buff*,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static u16 qeth_l2_select_queue(struct net_device *dev, struct sk_buff *skb,
				struct net_device *sb_dev)
{
	struct qeth_card *card = dev->ml_priv;

	if (IS_IQD(card))
		return qeth_iqd_select_queue(dev, skb,
					     qeth_get_ether_cast_type(skb),
					     sb_dev);
	return qeth_get_priority_queue(card, skb);
}