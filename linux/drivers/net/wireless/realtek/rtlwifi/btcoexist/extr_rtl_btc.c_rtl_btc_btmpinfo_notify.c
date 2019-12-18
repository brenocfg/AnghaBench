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
typedef  int u8 ;
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct TYPE_2__ {int bt_real_fw_ver; int bt_fw_ver; int bt_supported_feature; int bt_supported_version; int bt_ant_det_val; int bt_ble_scan_para; int bt_ble_scan_type; void* bt_forb_slot_val; void* bt_device_info; int /*<<< orphan*/  afh_map_h; void* afh_map_m; void* afh_map_l; } ;
struct btc_coexist {int /*<<< orphan*/  bt_mp_comp; TYPE_1__ bt_info; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
#define  BT_OP_GET_BT_FORBIDDEN_SLOT_VAL 138 
#define  BT_SEQ_GET_AFH_MAP_H 137 
#define  BT_SEQ_GET_AFH_MAP_L 136 
#define  BT_SEQ_GET_AFH_MAP_M 135 
#define  BT_SEQ_GET_BT_ANT_DET_VAL 134 
#define  BT_SEQ_GET_BT_BLE_SCAN_PARA 133 
#define  BT_SEQ_GET_BT_BLE_SCAN_TYPE 132 
#define  BT_SEQ_GET_BT_COEX_SUPPORTED_FEATURE 131 
#define  BT_SEQ_GET_BT_COEX_SUPPORTED_VERSION 130 
#define  BT_SEQ_GET_BT_DEVICE_INFO 129 
#define  BT_SEQ_GET_BT_VERSION 128 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct btc_coexist* rtl_btc_coexist (struct rtl_priv*) ; 

void rtl_btc_btmpinfo_notify(struct rtl_priv *rtlpriv, u8 *tmp_buf, u8 length)
{
	struct btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);
	u8 extid, seq;
	u16 bt_real_fw_ver;
	u8 bt_fw_ver;
	u8 *data;

	if (!btcoexist)
		return;

	if ((length < 4) || (!tmp_buf))
		return;

	extid = tmp_buf[0];
	/* not response from BT FW then exit*/
	if (extid != 1) /* C2H_TRIG_BY_BT_FW = 1 */
		return;

	seq = tmp_buf[2] >> 4;
	data = &tmp_buf[3];

	/* BT Firmware version response */
	switch (seq) {
	case BT_SEQ_GET_BT_VERSION:
		bt_real_fw_ver = tmp_buf[3] | (tmp_buf[4] << 8);
		bt_fw_ver = tmp_buf[5];

		btcoexist->bt_info.bt_real_fw_ver = bt_real_fw_ver;
		btcoexist->bt_info.bt_fw_ver = bt_fw_ver;
		break;
	case BT_SEQ_GET_AFH_MAP_L:
		btcoexist->bt_info.afh_map_l = le32_to_cpu(*(__le32 *)data);
		break;
	case BT_SEQ_GET_AFH_MAP_M:
		btcoexist->bt_info.afh_map_m = le32_to_cpu(*(__le32 *)data);
		break;
	case BT_SEQ_GET_AFH_MAP_H:
		btcoexist->bt_info.afh_map_h = le16_to_cpu(*(__le16 *)data);
		break;
	case BT_SEQ_GET_BT_COEX_SUPPORTED_FEATURE:
		btcoexist->bt_info.bt_supported_feature = tmp_buf[3] |
							  (tmp_buf[4] << 8);
		break;
	case BT_SEQ_GET_BT_COEX_SUPPORTED_VERSION:
		btcoexist->bt_info.bt_supported_version = tmp_buf[3] |
							  (tmp_buf[4] << 8);
		break;
	case BT_SEQ_GET_BT_ANT_DET_VAL:
		btcoexist->bt_info.bt_ant_det_val = tmp_buf[3];
		break;
	case BT_SEQ_GET_BT_BLE_SCAN_PARA:
		btcoexist->bt_info.bt_ble_scan_para = tmp_buf[3] |
						      (tmp_buf[4] << 8) |
						      (tmp_buf[5] << 16) |
						      (tmp_buf[6] << 24);
		break;
	case BT_SEQ_GET_BT_BLE_SCAN_TYPE:
		btcoexist->bt_info.bt_ble_scan_type = tmp_buf[3];
		break;
	case BT_SEQ_GET_BT_DEVICE_INFO:
		btcoexist->bt_info.bt_device_info =
						le32_to_cpu(*(__le32 *)data);
		break;
	case BT_OP_GET_BT_FORBIDDEN_SLOT_VAL:
		btcoexist->bt_info.bt_forb_slot_val =
						le32_to_cpu(*(__le32 *)data);
		break;
	}

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "btmpinfo complete req_num=%d\n", seq);

	complete(&btcoexist->bt_mp_comp);
}