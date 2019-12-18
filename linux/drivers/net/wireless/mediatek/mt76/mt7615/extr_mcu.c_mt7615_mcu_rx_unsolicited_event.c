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
struct sk_buff {scalar_t__ data; } ;
struct mt7615_mcu_rxd {int eid; } ;
struct mt7615_dev {int dummy; } ;

/* Variables and functions */
#define  MCU_EVENT_EXT 128 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mt7615_mcu_rx_ext_event (struct mt7615_dev*,struct sk_buff*) ; 

__attribute__((used)) static void
mt7615_mcu_rx_unsolicited_event(struct mt7615_dev *dev, struct sk_buff *skb)
{
	struct mt7615_mcu_rxd *rxd = (struct mt7615_mcu_rxd *)skb->data;

	switch (rxd->eid) {
	case MCU_EVENT_EXT:
		mt7615_mcu_rx_ext_event(dev, skb);
		break;
	default:
		break;
	}
	dev_kfree_skb(skb);
}