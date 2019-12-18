#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int idx; } ;
struct TYPE_6__ {TYPE_1__ wcid; } ;
struct mt7615_vif {scalar_t__ omac_idx; int idx; TYPE_2__ sta; } ;
struct TYPE_8__ {int idx; } ;
struct mt7615_sta {TYPE_4__ wcid; } ;
struct mt7615_dev {int /*<<< orphan*/  mt76; } ;
struct TYPE_7__ {int /*<<< orphan*/  bssid; } ;
struct ieee80211_vif {int type; TYPE_3__ bss_conf; scalar_t__ drv_priv; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct bss_info_omac {int dummy; } ;
struct bss_info_ext_bss {int dummy; } ;
struct bss_info_basic {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int BIT (int) ; 
#define  BSS_INFO_BASIC 133 
#define  BSS_INFO_EXT_BSS 132 
 int BSS_INFO_MAX_NUM ; 
#define  BSS_INFO_OMAC 131 
 int /*<<< orphan*/  CONNECTION_INFRA_AP ; 
 int /*<<< orphan*/  CONNECTION_INFRA_STA ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ EXT_BSSID_START ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MCU_EXT_CMD_BSS_INFO_UPDATE ; 
 int /*<<< orphan*/  NETWORK_INFRA ; 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_MESH_POINT 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __mt76_mcu_send_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int ffs (int) ; 
 struct ieee80211_sta* ieee80211_find_sta (struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7615_mcu_bss_info_basic_header (struct ieee80211_vif*,int*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mt7615_mcu_bss_info_ext_header (struct mt7615_vif*,int*) ; 
 int /*<<< orphan*/  mt7615_mcu_bss_info_omac_header (struct mt7615_vif*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int mt7615_mcu_set_bss_info(struct mt7615_dev *dev,
			    struct ieee80211_vif *vif, int en)
{
	struct mt7615_vif *mvif = (struct mt7615_vif *)vif->drv_priv;
	struct req_hdr {
		u8 bss_idx;
		u8 rsv0;
		__le16 tlv_num;
		u8 is_tlv_append;
		u8 rsv1[3];
	} __packed;
	int len = sizeof(struct req_hdr) + sizeof(struct bss_info_basic);
	int ret, i, features = BIT(BSS_INFO_BASIC), ntlv = 1;
	u32 conn_type = 0, net_type = NETWORK_INFRA;
	u8 *buf, *data, tx_wlan_idx = 0;
	struct req_hdr *hdr;

	if (en) {
		len += sizeof(struct bss_info_omac);
		features |= BIT(BSS_INFO_OMAC);
		if (mvif->omac_idx > EXT_BSSID_START) {
			len += sizeof(struct bss_info_ext_bss);
			features |= BIT(BSS_INFO_EXT_BSS);
			ntlv++;
		}
		ntlv++;
	}

	switch (vif->type) {
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_MESH_POINT:
		tx_wlan_idx = mvif->sta.wcid.idx;
		conn_type = CONNECTION_INFRA_AP;
		break;
	case NL80211_IFTYPE_STATION: {
		/* TODO: enable BSS_INFO_UAPSD & BSS_INFO_PM */
		if (en) {
			struct ieee80211_sta *sta;
			struct mt7615_sta *msta;

			rcu_read_lock();
			sta = ieee80211_find_sta(vif, vif->bss_conf.bssid);
			if (!sta) {
				rcu_read_unlock();
				return -EINVAL;
			}

			msta = (struct mt7615_sta *)sta->drv_priv;
			tx_wlan_idx = msta->wcid.idx;
			rcu_read_unlock();
		}
		conn_type = CONNECTION_INFRA_STA;
		break;
	}
	default:
		WARN_ON(1);
		break;
	}

	buf = kzalloc(len, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	hdr = (struct req_hdr *)buf;
	hdr->bss_idx = mvif->idx;
	hdr->tlv_num = cpu_to_le16(ntlv);
	hdr->is_tlv_append = 1;

	data = buf + sizeof(*hdr);
	for (i = 0; i < BSS_INFO_MAX_NUM; i++) {
		int tag = ffs(features & BIT(i)) - 1;

		switch (tag) {
		case BSS_INFO_OMAC:
			mt7615_mcu_bss_info_omac_header(mvif, data,
							conn_type);
			data += sizeof(struct bss_info_omac);
			break;
		case BSS_INFO_BASIC:
			mt7615_mcu_bss_info_basic_header(vif, data, net_type,
							 tx_wlan_idx, en);
			data += sizeof(struct bss_info_basic);
			break;
		case BSS_INFO_EXT_BSS:
			mt7615_mcu_bss_info_ext_header(mvif, data);
			data += sizeof(struct bss_info_ext_bss);
			break;
		default:
			break;
		}
	}

	ret = __mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_BSS_INFO_UPDATE,
				  buf, len, true);
	kfree(buf);

	return ret;
}