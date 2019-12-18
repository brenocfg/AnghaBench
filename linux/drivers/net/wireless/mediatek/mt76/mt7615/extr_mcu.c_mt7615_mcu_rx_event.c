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
struct mt7615_mcu_rxd {scalar_t__ ext_eid; int /*<<< orphan*/  seq; } ;
struct mt7615_dev {int /*<<< orphan*/  mt76; } ;

/* Variables and functions */
 scalar_t__ MCU_EXT_EVENT_ASSERT_DUMP ; 
 scalar_t__ MCU_EXT_EVENT_FW_LOG_2_HOST ; 
 scalar_t__ MCU_EXT_EVENT_PS_SYNC ; 
 scalar_t__ MCU_EXT_EVENT_THERMAL_PROTECT ; 
 int /*<<< orphan*/  mt7615_mcu_rx_unsolicited_event (struct mt7615_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  mt76_mcu_rx_event (int /*<<< orphan*/ *,struct sk_buff*) ; 

void mt7615_mcu_rx_event(struct mt7615_dev *dev, struct sk_buff *skb)
{
	struct mt7615_mcu_rxd *rxd = (struct mt7615_mcu_rxd *)skb->data;

	if (rxd->ext_eid == MCU_EXT_EVENT_THERMAL_PROTECT ||
	    rxd->ext_eid == MCU_EXT_EVENT_FW_LOG_2_HOST ||
	    rxd->ext_eid == MCU_EXT_EVENT_ASSERT_DUMP ||
	    rxd->ext_eid == MCU_EXT_EVENT_PS_SYNC ||
	    !rxd->seq)
		mt7615_mcu_rx_unsolicited_event(dev, skb);
	else
		mt76_mcu_rx_event(&dev->mt76, skb);
}