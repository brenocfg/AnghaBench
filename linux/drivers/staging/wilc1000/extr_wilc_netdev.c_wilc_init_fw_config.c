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
typedef  int u32 ;
typedef  int u16 ;
struct wilc_priv {scalar_t__ hif_drv; } ;
struct wilc_vif {int iftype; struct wilc_priv priv; } ;
struct net_device {int dummy; } ;
struct host_if_drv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WID_11G_OPERATING_MODE ; 
 int /*<<< orphan*/  WID_11I_MODE ; 
 int /*<<< orphan*/  WID_11N_CURRENT_TX_MCS ; 
 int /*<<< orphan*/  WID_11N_ENABLE ; 
 int /*<<< orphan*/  WID_11N_ERP_PROT_TYPE ; 
 int /*<<< orphan*/  WID_11N_HT_PROT_TYPE ; 
 int /*<<< orphan*/  WID_11N_IMMEDIATE_BA_ENABLED ; 
 int /*<<< orphan*/  WID_11N_OBSS_NONHT_DETECTION ; 
 int /*<<< orphan*/  WID_11N_OPERATING_MODE ; 
 int /*<<< orphan*/  WID_11N_PROT_MECH ; 
 int /*<<< orphan*/  WID_11N_RIFS_PROT_ENABLE ; 
 int /*<<< orphan*/  WID_11N_TXOP_PROT_DISABLE ; 
 int /*<<< orphan*/  WID_ACK_POLICY ; 
 int /*<<< orphan*/  WID_AUTH_TYPE ; 
 int /*<<< orphan*/  WID_BCAST_SSID ; 
 int /*<<< orphan*/  WID_BEACON_INTERVAL ; 
 int /*<<< orphan*/  WID_BSS_TYPE ; 
 int /*<<< orphan*/  WID_CURRENT_TX_RATE ; 
 int /*<<< orphan*/  WID_DTIM_PERIOD ; 
 int /*<<< orphan*/  WID_FRAG_THRESHOLD ; 
 int /*<<< orphan*/  WID_LISTEN_INTERVAL ; 
 int /*<<< orphan*/  WID_POWER_MANAGEMENT ; 
 int /*<<< orphan*/  WID_PREAMBLE ; 
 int /*<<< orphan*/  WID_QOS_ENABLE ; 
 int /*<<< orphan*/  WID_REKEY_PACKET_COUNT ; 
 int /*<<< orphan*/  WID_REKEY_PERIOD ; 
 int /*<<< orphan*/  WID_REKEY_POLICY ; 
 int /*<<< orphan*/  WID_RTS_THRESHOLD ; 
 int /*<<< orphan*/  WID_SCAN_TYPE ; 
 int /*<<< orphan*/  WID_SET_OPERATION_MODE ; 
 int /*<<< orphan*/  WID_SHORT_SLOT_ALLOWED ; 
 int /*<<< orphan*/  WID_SITE_SURVEY ; 
 int /*<<< orphan*/  WID_TX_POWER_LEVEL_11A ; 
 int /*<<< orphan*/  WID_TX_POWER_LEVEL_11B ; 
 int /*<<< orphan*/  WID_USER_CONTROL_ON_TX_POWER ; 
 int WILC_FW_11N_OP_MODE_HT_MIXED ; 
 int WILC_FW_11N_PROT_AUTO ; 
 int WILC_FW_ACK_POLICY_NORMAL ; 
 int WILC_FW_ACTIVE_SCAN ; 
 int WILC_FW_AUTH_OPEN_SYSTEM ; 
 int WILC_FW_BSS_TYPE_INFRA ; 
 int WILC_FW_ERP_PROT_SELF_CTS ; 
 int WILC_FW_HT_PROT_RTS_CTS_NONHT ; 
 int WILC_FW_NO_POWERSAVE ; 
 int WILC_FW_OBBS_NONHT_DETECT_PROTECT_REPORT ; 
 int WILC_FW_OPER_MODE_G_MIXED_11B_2 ; 
 int WILC_FW_PREAMBLE_SHORT ; 
 int WILC_FW_REKEY_POLICY_DISABLE ; 
 int WILC_FW_SEC_NO ; 
 int WILC_FW_SITE_SURVEY_OFF ; 
 int WILC_FW_TX_RATE_AUTO ; 
 int /*<<< orphan*/  cpu_to_le16s (int*) ; 
 int /*<<< orphan*/  cpu_to_le32s (int*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  wilc_wlan_cfg_set (struct wilc_vif*,int,int /*<<< orphan*/ ,int*,int,int,int) ; 

__attribute__((used)) static int wilc_init_fw_config(struct net_device *dev, struct wilc_vif *vif)
{
	struct wilc_priv *priv = &vif->priv;
	struct host_if_drv *hif_drv;
	u8 b;
	u16 hw;
	u32 w;

	netdev_dbg(dev, "Start configuring Firmware\n");
	hif_drv = (struct host_if_drv *)priv->hif_drv;
	netdev_dbg(dev, "Host = %p\n", hif_drv);

	w = vif->iftype;
	cpu_to_le32s(&w);
	if (!wilc_wlan_cfg_set(vif, 1, WID_SET_OPERATION_MODE, (u8 *)&w, 4,
			       0, 0))
		goto fail;

	b = WILC_FW_BSS_TYPE_INFRA;
	if (!wilc_wlan_cfg_set(vif, 0, WID_BSS_TYPE, &b, 1, 0, 0))
		goto fail;

	b = WILC_FW_TX_RATE_AUTO;
	if (!wilc_wlan_cfg_set(vif, 0, WID_CURRENT_TX_RATE, &b, 1, 0, 0))
		goto fail;

	b = WILC_FW_OPER_MODE_G_MIXED_11B_2;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11G_OPERATING_MODE, &b, 1, 0, 0))
		goto fail;

	b = WILC_FW_PREAMBLE_SHORT;
	if (!wilc_wlan_cfg_set(vif, 0, WID_PREAMBLE, &b, 1, 0, 0))
		goto fail;

	b = WILC_FW_11N_PROT_AUTO;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_PROT_MECH, &b, 1, 0, 0))
		goto fail;

	b = WILC_FW_ACTIVE_SCAN;
	if (!wilc_wlan_cfg_set(vif, 0, WID_SCAN_TYPE, &b, 1, 0, 0))
		goto fail;

	b = WILC_FW_SITE_SURVEY_OFF;
	if (!wilc_wlan_cfg_set(vif, 0, WID_SITE_SURVEY, &b, 1, 0, 0))
		goto fail;

	hw = 0xffff;
	cpu_to_le16s(&hw);
	if (!wilc_wlan_cfg_set(vif, 0, WID_RTS_THRESHOLD, (u8 *)&hw, 2, 0, 0))
		goto fail;

	hw = 2346;
	cpu_to_le16s(&hw);
	if (!wilc_wlan_cfg_set(vif, 0, WID_FRAG_THRESHOLD, (u8 *)&hw, 2, 0, 0))
		goto fail;

	b = 0;
	if (!wilc_wlan_cfg_set(vif, 0, WID_BCAST_SSID, &b, 1, 0, 0))
		goto fail;

	b = 1;
	if (!wilc_wlan_cfg_set(vif, 0, WID_QOS_ENABLE, &b, 1, 0, 0))
		goto fail;

	b = WILC_FW_NO_POWERSAVE;
	if (!wilc_wlan_cfg_set(vif, 0, WID_POWER_MANAGEMENT, &b, 1, 0, 0))
		goto fail;

	b = WILC_FW_SEC_NO;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11I_MODE, &b, 1, 0, 0))
		goto fail;

	b = WILC_FW_AUTH_OPEN_SYSTEM;
	if (!wilc_wlan_cfg_set(vif, 0, WID_AUTH_TYPE, &b, 1, 0, 0))
		goto fail;

	b = 3;
	if (!wilc_wlan_cfg_set(vif, 0, WID_LISTEN_INTERVAL, &b, 1, 0, 0))
		goto fail;

	b = 3;
	if (!wilc_wlan_cfg_set(vif, 0, WID_DTIM_PERIOD, &b, 1, 0, 0))
		goto fail;

	b = WILC_FW_ACK_POLICY_NORMAL;
	if (!wilc_wlan_cfg_set(vif, 0, WID_ACK_POLICY, &b, 1, 0, 0))
		goto fail;

	b = 0;
	if (!wilc_wlan_cfg_set(vif, 0, WID_USER_CONTROL_ON_TX_POWER, &b, 1,
			       0, 0))
		goto fail;

	b = 48;
	if (!wilc_wlan_cfg_set(vif, 0, WID_TX_POWER_LEVEL_11A, &b, 1, 0, 0))
		goto fail;

	b = 28;
	if (!wilc_wlan_cfg_set(vif, 0, WID_TX_POWER_LEVEL_11B, &b, 1, 0, 0))
		goto fail;

	hw = 100;
	cpu_to_le16s(&hw);
	if (!wilc_wlan_cfg_set(vif, 0, WID_BEACON_INTERVAL, (u8 *)&hw, 2, 0, 0))
		goto fail;

	b = WILC_FW_REKEY_POLICY_DISABLE;
	if (!wilc_wlan_cfg_set(vif, 0, WID_REKEY_POLICY, &b, 1, 0, 0))
		goto fail;

	w = 84600;
	cpu_to_le32s(&w);
	if (!wilc_wlan_cfg_set(vif, 0, WID_REKEY_PERIOD, (u8 *)&w, 4, 0, 0))
		goto fail;

	w = 500;
	cpu_to_le32s(&w);
	if (!wilc_wlan_cfg_set(vif, 0, WID_REKEY_PACKET_COUNT, (u8 *)&w, 4, 0,
			       0))
		goto fail;

	b = 1;
	if (!wilc_wlan_cfg_set(vif, 0, WID_SHORT_SLOT_ALLOWED, &b, 1, 0,
			       0))
		goto fail;

	b = WILC_FW_ERP_PROT_SELF_CTS;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_ERP_PROT_TYPE, &b, 1, 0, 0))
		goto fail;

	b = 1;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_ENABLE, &b, 1, 0, 0))
		goto fail;

	b = WILC_FW_11N_OP_MODE_HT_MIXED;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_OPERATING_MODE, &b, 1, 0, 0))
		goto fail;

	b = 1;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_TXOP_PROT_DISABLE, &b, 1, 0, 0))
		goto fail;

	b = WILC_FW_OBBS_NONHT_DETECT_PROTECT_REPORT;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_OBSS_NONHT_DETECTION, &b, 1,
			       0, 0))
		goto fail;

	b = WILC_FW_HT_PROT_RTS_CTS_NONHT;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_HT_PROT_TYPE, &b, 1, 0, 0))
		goto fail;

	b = 0;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_RIFS_PROT_ENABLE, &b, 1, 0,
			       0))
		goto fail;

	b = 7;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_CURRENT_TX_MCS, &b, 1, 0, 0))
		goto fail;

	b = 1;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_IMMEDIATE_BA_ENABLED, &b, 1,
			       1, 1))
		goto fail;

	return 0;

fail:
	return -1;
}