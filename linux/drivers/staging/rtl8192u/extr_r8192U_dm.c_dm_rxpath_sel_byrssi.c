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
typedef  size_t u8 ;
struct TYPE_5__ {size_t* rx_rssi_percentage; } ;
struct r8192_priv {scalar_t__ rf_type; scalar_t__* brfpath_rxenable; TYPE_2__ stats; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int cck_rx_path; int disabled_rf; scalar_t__ cck_method; size_t* rf_rssi; long* cck_pwdb_sta; size_t* rf_enable_rssi_th; } ;
struct TYPE_4__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ CCK_RX_VERSION_1 ; 
 scalar_t__ CCK_RX_VERSION_2 ; 
 TYPE_3__ DM_RxPathSelTable ; 
 size_t RF90_PATH_MAX ; 
 scalar_t__ RF_2T4R ; 
 size_t RX_PATH_SELECTION_DIFF_TH ; 
 size_t RX_PATH_SELECTION_SS_TH_LOW ; 
 scalar_t__ WIRELESS_MODE_B ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rCCK0_AFESetting ; 
 int /*<<< orphan*/  rOFDM0_TRxPathEnable ; 
 int /*<<< orphan*/  rOFDM1_TRxPathEnable ; 
 int /*<<< orphan*/  read_nic_byte (struct net_device*,int,int*) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void dm_rxpath_sel_byrssi(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u8				i, max_rssi_index = 0, min_rssi_index = 0, sec_rssi_index = 0, rf_num = 0;
	u8				tmp_max_rssi = 0, tmp_min_rssi = 0, tmp_sec_rssi = 0;
	u8				cck_default_Rx = 0x2;  /* RF-C */
	u8				cck_optional_Rx = 0x3; /* RF-D */
	long				tmp_cck_max_pwdb = 0, tmp_cck_min_pwdb = 0, tmp_cck_sec_pwdb = 0;
	u8				cck_rx_ver2_max_index = 0, cck_rx_ver2_min_index = 0, cck_rx_ver2_sec_index = 0;
	u8				cur_rf_rssi;
	long				cur_cck_pwdb;
	static u8			disabled_rf_cnt, cck_Rx_Path_initialized;
	u8				update_cck_rx_path;

	if (priv->rf_type != RF_2T4R)
		return;

	if (!cck_Rx_Path_initialized) {
		read_nic_byte(dev, 0xa07, &DM_RxPathSelTable.cck_rx_path);
		DM_RxPathSelTable.cck_rx_path &= 0xf;
		cck_Rx_Path_initialized = 1;
	}

	read_nic_byte(dev, 0xc04, &DM_RxPathSelTable.disabled_rf);
	DM_RxPathSelTable.disabled_rf = ~DM_RxPathSelTable.disabled_rf & 0xf;

	if (priv->ieee80211->mode == WIRELESS_MODE_B) {
		DM_RxPathSelTable.cck_method = CCK_RX_VERSION_2;	/* pure B mode, fixed cck version2 */
		/*DbgPrint("Pure B mode, use cck rx version2\n");*/
	}

	/* decide max/sec/min rssi index */
	for (i = 0; i < RF90_PATH_MAX; i++) {
		DM_RxPathSelTable.rf_rssi[i] = priv->stats.rx_rssi_percentage[i];

		if (priv->brfpath_rxenable[i]) {
			rf_num++;
			cur_rf_rssi = DM_RxPathSelTable.rf_rssi[i];

			if (rf_num == 1) { /* find first enabled rf path and the rssi values */
				/* initialize, set all rssi index to the same one */
				max_rssi_index = min_rssi_index = sec_rssi_index = i;
				tmp_max_rssi = tmp_min_rssi = tmp_sec_rssi = cur_rf_rssi;
			} else if (rf_num == 2) { /* we pick up the max index first, and let sec and min to be the same one */
				if (cur_rf_rssi >= tmp_max_rssi) {
					tmp_max_rssi = cur_rf_rssi;
					max_rssi_index = i;
				} else {
					tmp_sec_rssi = tmp_min_rssi = cur_rf_rssi;
					sec_rssi_index = min_rssi_index = i;
				}
			} else {
				if (cur_rf_rssi > tmp_max_rssi) {
					tmp_sec_rssi = tmp_max_rssi;
					sec_rssi_index = max_rssi_index;
					tmp_max_rssi = cur_rf_rssi;
					max_rssi_index = i;
				} else if (cur_rf_rssi == tmp_max_rssi) {	/* let sec and min point to the different index */
					tmp_sec_rssi = cur_rf_rssi;
					sec_rssi_index = i;
				} else if ((cur_rf_rssi < tmp_max_rssi) && (cur_rf_rssi > tmp_sec_rssi)) {
					tmp_sec_rssi = cur_rf_rssi;
					sec_rssi_index = i;
				} else if (cur_rf_rssi == tmp_sec_rssi) {
					if (tmp_sec_rssi == tmp_min_rssi) {
						/* let sec and min point to the different index */
						tmp_sec_rssi = cur_rf_rssi;
						sec_rssi_index = i;
					} else {
						/* This case we don't need to set any index */
					}
				} else if ((cur_rf_rssi < tmp_sec_rssi) && (cur_rf_rssi > tmp_min_rssi)) {
					/* This case we don't need to set any index */
				} else if (cur_rf_rssi == tmp_min_rssi) {
					if (tmp_sec_rssi == tmp_min_rssi) {
						/* let sec and min point to the different index */
						tmp_min_rssi = cur_rf_rssi;
						min_rssi_index = i;
					} else {
						/* This case we don't need to set any index */
					}
				} else if (cur_rf_rssi < tmp_min_rssi) {
					tmp_min_rssi = cur_rf_rssi;
					min_rssi_index = i;
				}
			}
		}
	}

	rf_num = 0;
	/* decide max/sec/min cck pwdb index */
	if (DM_RxPathSelTable.cck_method == CCK_RX_VERSION_2) {
		for (i = 0; i < RF90_PATH_MAX; i++) {
			if (priv->brfpath_rxenable[i]) {
				rf_num++;
				cur_cck_pwdb =  DM_RxPathSelTable.cck_pwdb_sta[i];

				if (rf_num == 1) {	/* find first enabled rf path and the rssi values */
					/* initialize, set all rssi index to the same one */
					cck_rx_ver2_max_index = cck_rx_ver2_min_index = cck_rx_ver2_sec_index = i;
					tmp_cck_max_pwdb = tmp_cck_min_pwdb = tmp_cck_sec_pwdb = cur_cck_pwdb;
				} else if (rf_num == 2) {	/* we pick up the max index first, and let sec and min to be the same one */
					if (cur_cck_pwdb >= tmp_cck_max_pwdb) {
						tmp_cck_max_pwdb = cur_cck_pwdb;
						cck_rx_ver2_max_index = i;
					} else {
						tmp_cck_sec_pwdb = tmp_cck_min_pwdb = cur_cck_pwdb;
						cck_rx_ver2_sec_index = cck_rx_ver2_min_index = i;
					}
				} else {
					if (cur_cck_pwdb > tmp_cck_max_pwdb) {
						tmp_cck_sec_pwdb = tmp_cck_max_pwdb;
						cck_rx_ver2_sec_index = cck_rx_ver2_max_index;
						tmp_cck_max_pwdb = cur_cck_pwdb;
						cck_rx_ver2_max_index = i;
					} else if (cur_cck_pwdb == tmp_cck_max_pwdb) {
						/* let sec and min point to the different index */
						tmp_cck_sec_pwdb = cur_cck_pwdb;
						cck_rx_ver2_sec_index = i;
					} else if ((cur_cck_pwdb < tmp_cck_max_pwdb) && (cur_cck_pwdb > tmp_cck_sec_pwdb)) {
						tmp_cck_sec_pwdb = cur_cck_pwdb;
						cck_rx_ver2_sec_index = i;
					} else if (cur_cck_pwdb == tmp_cck_sec_pwdb && tmp_cck_sec_pwdb == tmp_cck_min_pwdb) {
						/* let sec and min point to the different index */
						tmp_cck_sec_pwdb = cur_cck_pwdb;
						cck_rx_ver2_sec_index = i;
						/* otherwise we don't need to set any index */
					} else if ((cur_cck_pwdb < tmp_cck_sec_pwdb) && (cur_cck_pwdb > tmp_cck_min_pwdb)) {
						/*  This case we don't need to set any index */
					} else if (cur_cck_pwdb == tmp_cck_min_pwdb && tmp_cck_sec_pwdb == tmp_cck_min_pwdb) {
						/*  let sec and min point to the different index */
						tmp_cck_min_pwdb = cur_cck_pwdb;
						cck_rx_ver2_min_index = i;
						/* otherwise we don't need to set any index */
					} else if (cur_cck_pwdb < tmp_cck_min_pwdb) {
						tmp_cck_min_pwdb = cur_cck_pwdb;
						cck_rx_ver2_min_index = i;
					}
				}

			}
		}
	}

	/* Set CCK Rx path
	 * reg0xA07[3:2]=cck default rx path, reg0xa07[1:0]=cck optional rx path.
	 */
	update_cck_rx_path = 0;
	if (DM_RxPathSelTable.cck_method == CCK_RX_VERSION_2) {
		cck_default_Rx = cck_rx_ver2_max_index;
		cck_optional_Rx = cck_rx_ver2_sec_index;
		if (tmp_cck_max_pwdb != -64)
			update_cck_rx_path = 1;
	}

	if (tmp_min_rssi < RX_PATH_SELECTION_SS_TH_LOW && disabled_rf_cnt < 2) {
		if ((tmp_max_rssi - tmp_min_rssi) >= RX_PATH_SELECTION_DIFF_TH) {
			/* record the enabled rssi threshold */
			DM_RxPathSelTable.rf_enable_rssi_th[min_rssi_index] = tmp_max_rssi+5;
			/* disable the BB Rx path, OFDM */
			rtl8192_setBBreg(dev, rOFDM0_TRxPathEnable, 0x1<<min_rssi_index, 0x0);	/* 0xc04[3:0] */
			rtl8192_setBBreg(dev, rOFDM1_TRxPathEnable, 0x1<<min_rssi_index, 0x0);	/* 0xd04[3:0] */
			disabled_rf_cnt++;
		}
		if (DM_RxPathSelTable.cck_method == CCK_RX_VERSION_1) {
			cck_default_Rx = max_rssi_index;
			cck_optional_Rx = sec_rssi_index;
			if (tmp_max_rssi)
				update_cck_rx_path = 1;
		}
	}

	if (update_cck_rx_path) {
		DM_RxPathSelTable.cck_rx_path = (cck_default_Rx<<2)|(cck_optional_Rx);
		rtl8192_setBBreg(dev, rCCK0_AFESetting, 0x0f000000, DM_RxPathSelTable.cck_rx_path);
	}

	if (DM_RxPathSelTable.disabled_rf) {
		for (i = 0; i < 4; i++) {
			if ((DM_RxPathSelTable.disabled_rf >> i) & 0x1) {	/* disabled rf */
				if (tmp_max_rssi >= DM_RxPathSelTable.rf_enable_rssi_th[i]) {
					/* enable the BB Rx path */
					/*DbgPrint("RF-%d is enabled.\n", 0x1<<i);*/
					rtl8192_setBBreg(dev, rOFDM0_TRxPathEnable, 0x1<<i, 0x1);	/* 0xc04[3:0] */
					rtl8192_setBBreg(dev, rOFDM1_TRxPathEnable, 0x1<<i, 0x1);	/* 0xd04[3:0] */
					DM_RxPathSelTable.rf_enable_rssi_th[i] = 100;
					disabled_rf_cnt--;
				}
			}
		}
	}
}