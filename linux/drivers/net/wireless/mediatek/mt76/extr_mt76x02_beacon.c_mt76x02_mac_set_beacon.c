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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct mt76x02_dev {int beacon_data_mask; struct sk_buff** beacons; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sk_buff**) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  MT_MAC_BSSID_DW1 ; 
 int /*<<< orphan*/  MT_MAC_BSSID_DW1_MBEACON_N ; 
 int /*<<< orphan*/  __mt76x02_mac_set_beacon (struct mt76x02_dev*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mt76x02_mac_set_beacon(struct mt76x02_dev *dev, u8 vif_idx,
			   struct sk_buff *skb)
{
	bool force_update = false;
	int bcn_idx = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(dev->beacons); i++) {
		if (vif_idx == i) {
			force_update = !!dev->beacons[i] ^ !!skb;

			if (dev->beacons[i])
				dev_kfree_skb(dev->beacons[i]);

			dev->beacons[i] = skb;
			__mt76x02_mac_set_beacon(dev, bcn_idx, skb);
		} else if (force_update && dev->beacons[i]) {
			__mt76x02_mac_set_beacon(dev, bcn_idx,
						 dev->beacons[i]);
		}

		bcn_idx += !!dev->beacons[i];
	}

	for (i = bcn_idx; i < ARRAY_SIZE(dev->beacons); i++) {
		if (!(dev->beacon_data_mask & BIT(i)))
			break;

		__mt76x02_mac_set_beacon(dev, i, NULL);
	}

	mt76_rmw_field(dev, MT_MAC_BSSID_DW1, MT_MAC_BSSID_DW1_MBEACON_N,
		       bcn_idx - 1);
	return 0;
}