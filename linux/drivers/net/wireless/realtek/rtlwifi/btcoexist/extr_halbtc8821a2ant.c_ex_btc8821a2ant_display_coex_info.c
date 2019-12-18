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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct seq_file {int dummy; } ;
struct btc_stack_info {int /*<<< orphan*/  a2dp_exist; int /*<<< orphan*/  pan_exist; int /*<<< orphan*/  hid_exist; int /*<<< orphan*/  sco_exist; scalar_t__ profile_notified; int /*<<< orphan*/  hci_version; } ;
struct btc_board_info {int /*<<< orphan*/  btdm_ant_num; int /*<<< orphan*/  pg_ant_num; } ;
struct btc_coexist {int (* btc_read_1byte ) (struct btc_coexist*,int) ;scalar_t__ (* btc_read_4byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_disp_dbg_msg ) (struct btc_coexist*,int /*<<< orphan*/ ,struct seq_file*) ;scalar_t__ manual_control; int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ;struct btc_stack_info stack_info; struct btc_board_info board_info; } ;
struct TYPE_4__ {int wifi_chnl_info; int cur_ps_tdma; int bt_rf0x1e_backup; int /*<<< orphan*/  cur_ignore_wlan_act; int /*<<< orphan*/  cur_dec_bt_pwr_lvl; int /*<<< orphan*/  ps_tdma_para; int /*<<< orphan*/  cur_dac_swing_lvl; int /*<<< orphan*/  cur_dac_swing_on; int /*<<< orphan*/  cur_adc_back_off; int /*<<< orphan*/  cur_agc_table_en; } ;
struct TYPE_3__ {int bt_info_ext; int* bt_info_c2h_cnt; int /*<<< orphan*/  low_priority_tx; int /*<<< orphan*/  low_priority_rx; int /*<<< orphan*/  high_priority_tx; int /*<<< orphan*/  high_priority_rx; scalar_t__ under_lps; scalar_t__ under_ips; int /*<<< orphan*/ * bt_info_c2h; } ;

/* Variables and functions */
 int BIT0 ; 
 int /*<<< orphan*/  BTC_DBG_DISP_BT_LINK_INFO ; 
 int /*<<< orphan*/  BTC_DBG_DISP_COEX_STATISTICS ; 
 int /*<<< orphan*/  BTC_DBG_DISP_FW_PWR_MODE_CMD ; 
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 int /*<<< orphan*/  BTC_GET_S4_HS_RSSI ; 
 int /*<<< orphan*/  BTC_GET_S4_WIFI_RSSI ; 
 int /*<<< orphan*/  BTC_GET_U1_WIFI_DOT11_CHNL ; 
 int /*<<< orphan*/  BTC_GET_U1_WIFI_HS_CHNL ; 
 int /*<<< orphan*/  BTC_GET_U4_BT_PATCH_VER ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_BW ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_FW_VER ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_TRAFFIC_DIRECTION ; 
 scalar_t__ BTC_WIFI_BW_HT40 ; 
 scalar_t__ BTC_WIFI_BW_LEGACY ; 
 scalar_t__ BTC_WIFI_TRAFFIC_TX ; 
 int BT_INFO_SRC_8821A_2ANT_MAX ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/ * glbt_info_src_8821a_2ant ; 
 int /*<<< orphan*/  glcoex_ver_8821a_2ant ; 
 int /*<<< orphan*/  glcoex_ver_date_8821a_2ant ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub10 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub11 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub12 (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub13 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub14 (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub15 (struct btc_coexist*,int /*<<< orphan*/ ,struct seq_file*) ; 
 int /*<<< orphan*/  stub16 (struct btc_coexist*,int /*<<< orphan*/ ,struct seq_file*) ; 
 int stub17 (struct btc_coexist*,int) ; 
 int stub18 (struct btc_coexist*,int) ; 
 int stub19 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int stub20 (struct btc_coexist*,int) ; 
 scalar_t__ stub21 (struct btc_coexist*,int) ; 
 int stub22 (struct btc_coexist*,int) ; 
 scalar_t__ stub23 (struct btc_coexist*,int) ; 
 scalar_t__ stub24 (struct btc_coexist*,int) ; 
 scalar_t__ stub25 (struct btc_coexist*,int) ; 
 int stub26 (struct btc_coexist*,int) ; 
 scalar_t__ stub27 (struct btc_coexist*,int) ; 
 int stub28 (struct btc_coexist*,int) ; 
 scalar_t__ stub29 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int stub30 (struct btc_coexist*,int) ; 
 int stub31 (struct btc_coexist*,int) ; 
 scalar_t__ stub32 (struct btc_coexist*,int) ; 
 scalar_t__ stub33 (struct btc_coexist*,int) ; 
 scalar_t__ stub34 (struct btc_coexist*,int) ; 
 int stub35 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub36 (struct btc_coexist*,int /*<<< orphan*/ ,struct seq_file*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

void ex_btc8821a2ant_display_coex_info(struct btc_coexist *btcoexist,
				       struct seq_file *m)
{
	struct btc_board_info *board_info = &btcoexist->board_info;
	struct btc_stack_info *stack_info = &btcoexist->stack_info;
	u8 u1tmp[4], i, bt_info_ext, ps_tdma_case = 0;
	u32 u4tmp[4];
	bool roam = false, scan = false, link = false, wifi_under_5g = false;
	bool bt_hs_on = false, wifi_busy = false;
	long wifi_rssi = 0, bt_hs_rssi = 0;
	u32 wifi_bw, wifi_traffic_dir;
	u8 wifi_dot_11_chnl, wifi_hs_chnl;
	u32 fw_ver = 0, bt_patch_ver = 0;

	seq_puts(m, "\n ============[BT Coexist info]============");

	seq_printf(m, "\n %-35s = %d/ %d ", "Ant PG number/ Ant mechanism:",
		   board_info->pg_ant_num, board_info->btdm_ant_num);

	if (btcoexist->manual_control) {
		seq_printf(m, "\n %-35s", "[Action Manual control]!!");
	}

	seq_printf(m, "\n %-35s = %s / %d", "BT stack/ hci ext ver",
		   ((stack_info->profile_notified) ? "Yes" : "No"),
		   stack_info->hci_version);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_BT_PATCH_VER, &bt_patch_ver);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);
	seq_printf(m, "\n %-35s = %d_%d/ 0x%x/ 0x%x(%d)",
		   "CoexVer/ FwVer/ PatchVer",
		   glcoex_ver_date_8821a_2ant, glcoex_ver_8821a_2ant,
		   fw_ver, bt_patch_ver, bt_patch_ver);

	btcoexist->btc_get(btcoexist,
		BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist,
		BTC_GET_U1_WIFI_DOT11_CHNL, &wifi_dot_11_chnl);
	btcoexist->btc_get(btcoexist,
		BTC_GET_U1_WIFI_HS_CHNL, &wifi_hs_chnl);
	seq_printf(m, "\n %-35s = %d / %d(%d)",
		   "Dot11 channel / HsMode(HsChnl)",
		   wifi_dot_11_chnl, bt_hs_on, wifi_hs_chnl);

	seq_printf(m, "\n %-35s = %3ph ",
		   "H2C Wifi inform bt chnl Info",
		   coex_dm->wifi_chnl_info);

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wifi_rssi);
	btcoexist->btc_get(btcoexist, BTC_GET_S4_HS_RSSI, &bt_hs_rssi);
	seq_printf(m, "\n %-35s = %ld/ %ld", "Wifi rssi/ HS rssi",
		   wifi_rssi, bt_hs_rssi);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);
	seq_printf(m, "\n %-35s = %d/ %d/ %d ", "Wifi link/ roam/ scan",
		   link, roam, scan);

	btcoexist->btc_get(btcoexist,
		BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);
	btcoexist->btc_get(btcoexist,
		BTC_GET_U4_WIFI_BW, &wifi_bw);
	btcoexist->btc_get(btcoexist,
		BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	btcoexist->btc_get(btcoexist,
		BTC_GET_U4_WIFI_TRAFFIC_DIRECTION, &wifi_traffic_dir);
	seq_printf(m, "\n %-35s = %s / %s/ %s ", "Wifi status",
		   (wifi_under_5g ? "5G" : "2.4G"),
		   ((BTC_WIFI_BW_LEGACY == wifi_bw) ? "Legacy" :
		    (((BTC_WIFI_BW_HT40 == wifi_bw) ? "HT40" : "HT20"))),
		   ((!wifi_busy) ? "idle" :
		    ((BTC_WIFI_TRAFFIC_TX == wifi_traffic_dir) ?
		     "uplink" : "downlink")));

	if (stack_info->profile_notified) {
		seq_printf(m, "\n %-35s = %d / %d / %d / %d",
			   "SCO/HID/PAN/A2DP",
			   stack_info->sco_exist, stack_info->hid_exist,
			   stack_info->pan_exist, stack_info->a2dp_exist);

		btcoexist->btc_disp_dbg_msg(btcoexist,
					    BTC_DBG_DISP_BT_LINK_INFO,
					    m);
	}

	bt_info_ext = coex_sta->bt_info_ext;
	seq_printf(m, "\n %-35s = %s", "BT Info A2DP rate",
		   (bt_info_ext&BIT0) ? "Basic rate" : "EDR rate");

	for (i = 0; i < BT_INFO_SRC_8821A_2ANT_MAX; i++) {
		if (coex_sta->bt_info_c2h_cnt[i]) {
			seq_printf(m, "\n %-35s = %7ph(%d)",
				   glbt_info_src_8821a_2ant[i],
				   coex_sta->bt_info_c2h[i],
				   coex_sta->bt_info_c2h_cnt[i]);
		}
	}

	seq_printf(m, "\n %-35s = %s/%s",
		   "PS state, IPS/LPS",
		   ((coex_sta->under_ips ? "IPS ON" : "IPS OFF")),
		   ((coex_sta->under_lps ? "LPS ON" : "LPS OFF")));
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_FW_PWR_MODE_CMD, m);

	/* Sw mechanism*/
	seq_printf(m, "\n %-35s",
		   "============[Sw mechanism]============");
	seq_printf(m, "\n %-35s = %d/ %d/ %d(0x%x) ",
		   "SM2[AgcT/ AdcB/ SwDacSwing(lvl)]",
		   coex_dm->cur_agc_table_en, coex_dm->cur_adc_back_off,
		   coex_dm->cur_dac_swing_on, coex_dm->cur_dac_swing_lvl);

	/* Fw mechanism*/
	seq_printf(m, "\n %-35s",
		   "============[Fw mechanism]============");

	if (!btcoexist->manual_control) {
		ps_tdma_case = coex_dm->cur_ps_tdma;
		seq_printf(m, "\n %-35s = %5ph case-%d",
			   "PS TDMA",
			   coex_dm->ps_tdma_para, ps_tdma_case);

		seq_printf(m, "\n %-35s = %d/ %d ", "DecBtPwr/ IgnWlanAct",
			   coex_dm->cur_dec_bt_pwr_lvl,
			   coex_dm->cur_ignore_wlan_act);
	}

	/* Hw setting*/
	seq_printf(m, "\n %-35s", "============[Hw setting]============");

	seq_printf(m, "\n %-35s = 0x%x", "RF-A, 0x1e initVal",
		   coex_dm->bt_rf0x1e_backup);

	u1tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0x778);
	u1tmp[1] = btcoexist->btc_read_1byte(btcoexist, 0x6cc);
	seq_printf(m, "\n %-35s = 0x%x/ 0x%x ",
		   "0x778 (W_Act)/ 0x6cc (CoTab Sel)",
		   u1tmp[0], u1tmp[1]);

	u1tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0x8db);
	u1tmp[1] = btcoexist->btc_read_1byte(btcoexist, 0xc5b);
	seq_printf(m, "\n %-35s = 0x%x/ 0x%x",
		   "0x8db(ADC)/0xc5b[29:25](DAC)",
		   ((u1tmp[0] & 0x60) >> 5), ((u1tmp[1] & 0x3e) >> 1));

	u4tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0xcb4);
	seq_printf(m, "\n %-35s = 0x%x/ 0x%x",
		   "0xcb4[7:0](ctrl)/ 0xcb4[29:28](val)",
		   u4tmp[0] & 0xff, ((u4tmp[0] & 0x30000000) >> 28));

	u1tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0x40);
	u4tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0x4c);
	u4tmp[1] = btcoexist->btc_read_4byte(btcoexist, 0x974);
	seq_printf(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x",
		   "0x40/ 0x4c[24:23]/ 0x974",
		   u1tmp[0], ((u4tmp[0] & 0x01800000) >> 23), u4tmp[1]);

	u4tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0x550);
	u1tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0x522);
	seq_printf(m, "\n %-35s = 0x%x/ 0x%x",
		   "0x550(bcn ctrl)/0x522",
		   u4tmp[0], u1tmp[0]);

	u4tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0xc50);
	u1tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0xa0a);
	seq_printf(m, "\n %-35s = 0x%x/ 0x%x",
		   "0xc50(DIG)/0xa0a(CCK-TH)",
		   u4tmp[0], u1tmp[0]);

	u4tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0xf48);
	u1tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0xa5b);
	u1tmp[1] = btcoexist->btc_read_1byte(btcoexist, 0xa5c);
	seq_printf(m, "\n %-35s = 0x%x/ 0x%x",
		   "OFDM-FA/ CCK-FA",
		   u4tmp[0], (u1tmp[0] << 8) + u1tmp[1]);

	u4tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0x6c0);
	u4tmp[1] = btcoexist->btc_read_4byte(btcoexist, 0x6c4);
	u4tmp[2] = btcoexist->btc_read_4byte(btcoexist, 0x6c8);
	seq_printf(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x",
		   "0x6c0/0x6c4/0x6c8",
		   u4tmp[0], u4tmp[1], u4tmp[2]);

	seq_printf(m, "\n %-35s = %d/ %d",
		   "0x770 (hi-pri Rx/Tx)",
		   coex_sta->high_priority_rx, coex_sta->high_priority_tx);
	seq_printf(m, "\n %-35s = %d/ %d",
		   "0x774(low-pri Rx/Tx)",
		   coex_sta->low_priority_rx, coex_sta->low_priority_tx);

	/* Tx mgnt queue hang or not, 0x41b should = 0xf, ex: 0xd ==>hang*/
	u1tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0x41b);
	seq_printf(m, "\n %-35s = 0x%x",
		   "0x41b (mgntQ hang chk == 0xf)",
		   u1tmp[0]);

	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_COEX_STATISTICS, m);
}