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
struct sk_buff {scalar_t__ data; } ;
struct mt7615_mcu_rxd {int ext_eid; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;
struct mt7615_dev {TYPE_1__ mt76; int /*<<< orphan*/  hw_pattern; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
#define  MCU_EXT_EVENT_CSA_NOTIFY 129 
#define  MCU_EXT_EVENT_RDD_REPORT 128 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mt7615_dev*) ; 
 int /*<<< orphan*/  ieee80211_radar_detected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7615_mcu_csa_finish ; 

__attribute__((used)) static void
mt7615_mcu_rx_ext_event(struct mt7615_dev *dev, struct sk_buff *skb)
{
	struct mt7615_mcu_rxd *rxd = (struct mt7615_mcu_rxd *)skb->data;

	switch (rxd->ext_eid) {
	case MCU_EXT_EVENT_RDD_REPORT:
		ieee80211_radar_detected(dev->mt76.hw);
		dev->hw_pattern++;
		break;
	case MCU_EXT_EVENT_CSA_NOTIFY:
		ieee80211_iterate_active_interfaces_atomic(dev->mt76.hw,
				IEEE80211_IFACE_ITER_RESUME_ALL,
				mt7615_mcu_csa_finish, dev);
		break;
	default:
		break;
	}
}