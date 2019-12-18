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
struct wtbl_req_hdr {int /*<<< orphan*/  operation; int /*<<< orphan*/  wlan_idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  idx; } ;
struct mt7615_sta {TYPE_1__ wcid; } ;
struct mt7615_dev {int /*<<< orphan*/  mt76; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_EXT_CMD_WTBL_UPDATE ; 
 int /*<<< orphan*/  WTBL_RESET_AND_SET ; 
 int __mt76_mcu_send_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wtbl_req_hdr*,int,int) ; 

int mt7615_mcu_del_wtbl(struct mt7615_dev *dev,
			struct ieee80211_sta *sta)
{
	struct mt7615_sta *msta = (struct mt7615_sta *)sta->drv_priv;
	struct wtbl_req_hdr req = {
		.wlan_idx = msta->wcid.idx,
		.operation = WTBL_RESET_AND_SET,
	};

	return __mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_WTBL_UPDATE,
				   &req, sizeof(req), true);
}