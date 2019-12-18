#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct seq_file {int dummy; } ;
struct btc_stack_info {int hci_version; int /*<<< orphan*/  a2dp_exist; int /*<<< orphan*/  pan_exist; int /*<<< orphan*/  hid_exist; int /*<<< orphan*/  sco_exist; scalar_t__ profile_notified; } ;
struct TYPE_4__ {int /*<<< orphan*/  ra_mask; scalar_t__ bt_disabled; } ;
struct btc_board_info {scalar_t__ pg_ant_num; int btdm_ant_num; } ;
struct btc_coexist {scalar_t__ (* btc_read_4byte ) (struct btc_coexist*,int) ;int (* btc_read_1byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_disp_dbg_msg ) (struct btc_coexist*,int /*<<< orphan*/ ,struct seq_file*) ;scalar_t__ auto_report_2ant; int /*<<< orphan*/  (* btc_read_2byte ) (struct btc_coexist*,int) ;TYPE_1__ bt_info; int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ;scalar_t__ manual_control; struct btc_stack_info stack_info; struct btc_board_info board_info; } ;
struct TYPE_6__ {scalar_t__ bt_status; int cur_ps_tdma; scalar_t__ cur_dec_bt_pwr; int cur_ignore_wlan_act; int /*<<< orphan*/  backup_ampdu_maxtime; int /*<<< orphan*/  backup_retry_limit; int /*<<< orphan*/  backup_arfr_cnt2; int /*<<< orphan*/  backup_arfr_cnt1; int /*<<< orphan*/  bt_rf0x1e_backup; int /*<<< orphan*/  auto_tdma_adjust; int /*<<< orphan*/  ps_tdma_para; int /*<<< orphan*/  cur_dac_swing_lvl; int /*<<< orphan*/  cur_dac_swing_on; int /*<<< orphan*/  cur_adc_back_off; int /*<<< orphan*/  cur_agc_table_en; int /*<<< orphan*/  limited_dig; int /*<<< orphan*/  cur_low_penalty_ra; int /*<<< orphan*/  cur_rf_rx_lpf_shrink; int /*<<< orphan*/  cur_ss_type; int /*<<< orphan*/  wifi_chnl_info; } ;
struct TYPE_5__ {int bt_info_ext; int* bt_info_c2h_cnt; scalar_t__* bt_info_c2h; scalar_t__ high_priority_rx; int high_priority_tx; scalar_t__ low_priority_rx; int low_priority_tx; scalar_t__ under_lps; scalar_t__ under_ips; int /*<<< orphan*/  bt_retry_cnt; int /*<<< orphan*/  bt_rssi; scalar_t__ c2h_bt_inquiry_page; } ;

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
 scalar_t__ BT_8192E_2ANT_BT_STATUS_CONNECTED_IDLE ; 
 scalar_t__ BT_8192E_2ANT_BT_STATUS_NON_CONNECTED_IDLE ; 
 int BT_INFO_SRC_8192E_2ANT_MAX ; 
 int /*<<< orphan*/  btc8192e2ant_monitor_bt_ctr (struct btc_coexist*) ; 
 TYPE_3__* coex_dm ; 
 TYPE_2__* coex_sta ; 
 char** glbt_info_src_8192e_2ant ; 
 int /*<<< orphan*/  glcoex_ver_8192e_2ant ; 
 int /*<<< orphan*/  glcoex_ver_date_8192e_2ant ; 
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
 scalar_t__ stub17 (struct btc_coexist*,int) ; 
 scalar_t__ stub18 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub19 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int stub20 (struct btc_coexist*,int) ; 
 scalar_t__ stub21 (struct btc_coexist*,int) ; 
 scalar_t__ stub22 (struct btc_coexist*,int) ; 
 scalar_t__ stub23 (struct btc_coexist*,int) ; 
 int stub24 (struct btc_coexist*,int) ; 
 int stub25 (struct btc_coexist*,int) ; 
 scalar_t__ stub26 (struct btc_coexist*,int) ; 
 int stub27 (struct btc_coexist*,int) ; 
 int stub28 (struct btc_coexist*,int) ; 
 scalar_t__ stub29 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int stub30 (struct btc_coexist*,int) ; 
 scalar_t__ stub31 (struct btc_coexist*,int) ; 
 scalar_t__ stub32 (struct btc_coexist*,int) ; 
 scalar_t__ stub33 (struct btc_coexist*,int) ; 
 scalar_t__ stub34 (struct btc_coexist*,int) ; 
 int stub35 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub36 (struct btc_coexist*,int /*<<< orphan*/ ,struct seq_file*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

void ex_btc8192e2ant_display_coex_info(struct btc_coexist *btcoexist,
				       struct seq_file *m)
{
	struct btc_board_info *board_info = &btcoexist->board_info;
	struct btc_stack_info *stack_info = &btcoexist->stack_info;
	u8 u8tmp[4], i, bt_info_ext, ps_tdma_case = 0;
	u16 u16tmp[4];
	u32 u32tmp[4];
	bool roam = false, scan = false, link = false, wifi_under_5g = false;
	bool bt_hs_on = false, wifi_busy = false;
	int wifi_rssi = 0, bt_hs_rssi = 0;
	u32 wifi_bw, wifi_traffic_dir;
	u8 wifi_dot11_chnl, wifi_hs_chnl;
	u32 fw_ver = 0, bt_patch_ver = 0;

	seq_puts(m, "\n ============[BT Coexist info]============");

	if (btcoexist->manual_control) {
		seq_puts(m, "\n ===========[Under Manual Control]===========");
		seq_puts(m, "\n ==========================================");
	}

	seq_printf(m, "\n %-35s = %d/ %d ", "Ant PG number/ Ant mechanism:",
		   board_info->pg_ant_num, board_info->btdm_ant_num);

	seq_printf(m, "\n %-35s = %s / %d", "BT stack/ hci ext ver",
		   ((stack_info->profile_notified) ? "Yes" : "No"),
		   stack_info->hci_version);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_BT_PATCH_VER, &bt_patch_ver);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);
	seq_printf(m, "\n %-35s = %d_%d/ 0x%x/ 0x%x(%d)",
		   "CoexVer/ FwVer/ PatchVer",
		   glcoex_ver_date_8192e_2ant, glcoex_ver_8192e_2ant,
		   fw_ver, bt_patch_ver, bt_patch_ver);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_DOT11_CHNL,
			   &wifi_dot11_chnl);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_HS_CHNL, &wifi_hs_chnl);
	seq_printf(m, "\n %-35s = %d / %d(%d)",
		   "Dot11 channel / HsMode(HsChnl)",
		   wifi_dot11_chnl, bt_hs_on, wifi_hs_chnl);

	seq_printf(m, "\n %-35s = %3ph ",
		   "H2C Wifi inform bt chnl Info", coex_dm->wifi_chnl_info);

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wifi_rssi);
	btcoexist->btc_get(btcoexist, BTC_GET_S4_HS_RSSI, &bt_hs_rssi);
	seq_printf(m, "\n %-35s = %d/ %d",
		   "Wifi rssi/ HS rssi", wifi_rssi, bt_hs_rssi);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);
	seq_printf(m, "\n %-35s = %d/ %d/ %d ",
		   "Wifi link/ roam/ scan", link, roam, scan);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wifi_bw);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_TRAFFIC_DIRECTION,
			   &wifi_traffic_dir);
	seq_printf(m, "\n %-35s = %s / %s/ %s ",
		   "Wifi status", (wifi_under_5g ? "5G" : "2.4G"),
		   ((BTC_WIFI_BW_LEGACY == wifi_bw) ? "Legacy" :
			(((BTC_WIFI_BW_HT40 == wifi_bw) ? "HT40" : "HT20"))),
		   ((!wifi_busy) ? "idle" :
			((BTC_WIFI_TRAFFIC_TX == wifi_traffic_dir) ?
				"uplink" : "downlink")));

	seq_printf(m, "\n %-35s = [%s/ %d/ %d] ",
		   "BT [status/ rssi/ retryCnt]",
		   ((btcoexist->bt_info.bt_disabled) ? ("disabled") :
		    ((coex_sta->c2h_bt_inquiry_page) ?
		     ("inquiry/page scan") :
		      ((BT_8192E_2ANT_BT_STATUS_NON_CONNECTED_IDLE ==
			coex_dm->bt_status) ? "non-connected idle" :
			 ((BT_8192E_2ANT_BT_STATUS_CONNECTED_IDLE ==
			   coex_dm->bt_status) ? "connected-idle" : "busy")))),
		   coex_sta->bt_rssi, coex_sta->bt_retry_cnt);

	seq_printf(m, "\n %-35s = %d / %d / %d / %d",
		   "SCO/HID/PAN/A2DP", stack_info->sco_exist,
		   stack_info->hid_exist, stack_info->pan_exist,
		   stack_info->a2dp_exist);
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_BT_LINK_INFO, m);

	bt_info_ext = coex_sta->bt_info_ext;
	seq_printf(m, "\n %-35s = %s",
		   "BT Info A2DP rate",
		   (bt_info_ext&BIT0) ? "Basic rate" : "EDR rate");

	for (i = 0; i < BT_INFO_SRC_8192E_2ANT_MAX; i++) {
		if (coex_sta->bt_info_c2h_cnt[i]) {
			seq_printf(m, "\n %-35s = %7ph(%d)",
				   glbt_info_src_8192e_2ant[i],
				   coex_sta->bt_info_c2h[i],
				   coex_sta->bt_info_c2h_cnt[i]);
		}
	}

	seq_printf(m, "\n %-35s = %s/%s",
		   "PS state, IPS/LPS",
		   ((coex_sta->under_ips ? "IPS ON" : "IPS OFF")),
		   ((coex_sta->under_lps ? "LPS ON" : "LPS OFF")));
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_FW_PWR_MODE_CMD, m);

	seq_printf(m, "\n %-35s = 0x%x ", "SS Type",
		   coex_dm->cur_ss_type);

	/* Sw mechanism	*/
	seq_printf(m, "\n %-35s",
		   "============[Sw mechanism]============");
	seq_printf(m, "\n %-35s = %d/ %d/ %d ",
		   "SM1[ShRf/ LpRA/ LimDig]", coex_dm->cur_rf_rx_lpf_shrink,
		   coex_dm->cur_low_penalty_ra, coex_dm->limited_dig);
	seq_printf(m, "\n %-35s = %d/ %d/ %d(0x%x) ",
		   "SM2[AgcT/ AdcB/ SwDacSwing(lvl)]",
		   coex_dm->cur_agc_table_en, coex_dm->cur_adc_back_off,
		   coex_dm->cur_dac_swing_on, coex_dm->cur_dac_swing_lvl);

	seq_printf(m, "\n %-35s = 0x%x ", "Rate Mask",
		   btcoexist->bt_info.ra_mask);

	/* Fw mechanism	*/
	seq_printf(m, "\n %-35s",
		   "============[Fw mechanism]============");

	ps_tdma_case = coex_dm->cur_ps_tdma;
	seq_printf(m,
		   "\n %-35s = %5ph case-%d (auto:%d)",
		   "PS TDMA", coex_dm->ps_tdma_para,
		   ps_tdma_case, coex_dm->auto_tdma_adjust);

	seq_printf(m, "\n %-35s = %d/ %d ",
		   "DecBtPwr/ IgnWlanAct",
		   coex_dm->cur_dec_bt_pwr, coex_dm->cur_ignore_wlan_act);

	/* Hw setting */
	seq_printf(m, "\n %-35s",
		   "============[Hw setting]============");

	seq_printf(m, "\n %-35s = 0x%x",
		   "RF-A, 0x1e initVal", coex_dm->bt_rf0x1e_backup);

	seq_printf(m, "\n %-35s = 0x%x/0x%x/0x%x/0x%x",
		   "backup ARFR1/ARFR2/RL/AMaxTime", coex_dm->backup_arfr_cnt1,
		   coex_dm->backup_arfr_cnt2, coex_dm->backup_retry_limit,
		   coex_dm->backup_ampdu_maxtime);

	u32tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0x430);
	u32tmp[1] = btcoexist->btc_read_4byte(btcoexist, 0x434);
	u16tmp[0] = btcoexist->btc_read_2byte(btcoexist, 0x42a);
	u8tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0x456);
	seq_printf(m, "\n %-35s = 0x%x/0x%x/0x%x/0x%x",
		   "0x430/0x434/0x42a/0x456",
		   u32tmp[0], u32tmp[1], u16tmp[0], u8tmp[0]);

	u32tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0xc04);
	u32tmp[1] = btcoexist->btc_read_4byte(btcoexist, 0xd04);
	u32tmp[2] = btcoexist->btc_read_4byte(btcoexist, 0x90c);
	seq_printf(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x",
		   "0xc04/ 0xd04/ 0x90c", u32tmp[0], u32tmp[1], u32tmp[2]);

	u8tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0x778);
	seq_printf(m, "\n %-35s = 0x%x", "0x778", u8tmp[0]);

	u8tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0x92c);
	u32tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0x930);
	seq_printf(m, "\n %-35s = 0x%x/ 0x%x",
		   "0x92c/ 0x930", (u8tmp[0]), u32tmp[0]);

	u8tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0x40);
	u8tmp[1] = btcoexist->btc_read_1byte(btcoexist, 0x4f);
	seq_printf(m, "\n %-35s = 0x%x/ 0x%x",
		   "0x40/ 0x4f", u8tmp[0], u8tmp[1]);

	u32tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0x550);
	u8tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0x522);
	seq_printf(m, "\n %-35s = 0x%x/ 0x%x",
		   "0x550(bcn ctrl)/0x522", u32tmp[0], u8tmp[0]);

	u32tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0xc50);
	seq_printf(m, "\n %-35s = 0x%x", "0xc50(dig)",
		   u32tmp[0]);

	u32tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0x6c0);
	u32tmp[1] = btcoexist->btc_read_4byte(btcoexist, 0x6c4);
	u32tmp[2] = btcoexist->btc_read_4byte(btcoexist, 0x6c8);
	u8tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0x6cc);
	seq_printf(m,
		   "\n %-35s = 0x%x/ 0x%x/ 0x%x/ 0x%x",
		   "0x6c0/0x6c4/0x6c8/0x6cc(coexTable)",
		   u32tmp[0], u32tmp[1], u32tmp[2], u8tmp[0]);

	seq_printf(m, "\n %-35s = %d/ %d",
		   "0x770(hp rx[31:16]/tx[15:0])",
		   coex_sta->high_priority_rx, coex_sta->high_priority_tx);
	seq_printf(m, "\n %-35s = %d/ %d",
		   "0x774(lp rx[31:16]/tx[15:0])",
		   coex_sta->low_priority_rx, coex_sta->low_priority_tx);
	if (btcoexist->auto_report_2ant)
		btc8192e2ant_monitor_bt_ctr(btcoexist);
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_COEX_STATISTICS, m);
}