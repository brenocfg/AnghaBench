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
struct r8192_priv {scalar_t__ rf_type; scalar_t__* brfpath_rxenable; TYPE_2__ stats; TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int cck_Rx_path; int disabledRF; scalar_t__ cck_method; size_t* rf_rssi; long* cck_pwdb_sta; size_t SS_TH_low; size_t diff_TH; size_t* rf_enable_rssi_th; } ;
struct TYPE_4__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ CCK_Rx_Version_1 ; 
 scalar_t__ CCK_Rx_Version_2 ; 
 TYPE_3__ DM_RxPathSelTable ; 
 scalar_t__ PWDB_IN_RANGE ; 
 size_t RF90_PATH_MAX ; 
 scalar_t__ RF_2T4R ; 
 scalar_t__ WIRELESS_MODE_B ; 
 int /*<<< orphan*/  rCCK0_AFESetting ; 
 int /*<<< orphan*/  rOFDM0_TRxPathEnable ; 
 int /*<<< orphan*/  rOFDM1_TRxPathEnable ; 
 int rtl92e_readb (struct net_device*,int) ; 
 int /*<<< orphan*/  rtl92e_set_bb_reg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_rx_path_sel_byrssi(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	u8 i, max_rssi_index = 0, min_rssi_index = 0;
	u8 sec_rssi_index = 0, rf_num = 0;
	u8 tmp_max_rssi = 0, tmp_min_rssi = 0, tmp_sec_rssi = 0;
	u8 cck_default_Rx = 0x2;
	u8 cck_optional_Rx = 0x3;
	long tmp_cck_max_pwdb = 0, tmp_cck_min_pwdb = 0, tmp_cck_sec_pwdb = 0;
	u8 cck_rx_ver2_max_index = 0;
	u8 cck_rx_ver2_sec_index = 0;
	u8 cur_rf_rssi;
	long cur_cck_pwdb;
	static u8 disabled_rf_cnt, cck_Rx_Path_initialized;
	u8 update_cck_rx_path;

	if (priv->rf_type != RF_2T4R)
		return;

	if (!cck_Rx_Path_initialized) {
		DM_RxPathSelTable.cck_Rx_path = (rtl92e_readb(dev, 0xa07)&0xf);
		cck_Rx_Path_initialized = 1;
	}

	DM_RxPathSelTable.disabledRF = 0xf;
	DM_RxPathSelTable.disabledRF &= ~(rtl92e_readb(dev, 0xc04));

	if (priv->rtllib->mode == WIRELESS_MODE_B)
		DM_RxPathSelTable.cck_method = CCK_Rx_Version_2;

	for (i = 0; i < RF90_PATH_MAX; i++) {
		DM_RxPathSelTable.rf_rssi[i] = priv->stats.rx_rssi_percentage[i];

		if (priv->brfpath_rxenable[i]) {
			rf_num++;
			cur_rf_rssi = DM_RxPathSelTable.rf_rssi[i];

			if (rf_num == 1) {
				max_rssi_index = min_rssi_index = sec_rssi_index = i;
				tmp_max_rssi = tmp_min_rssi = tmp_sec_rssi = cur_rf_rssi;
			} else if (rf_num == 2) {
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
				} else if (cur_rf_rssi == tmp_max_rssi) {
					tmp_sec_rssi = cur_rf_rssi;
					sec_rssi_index = i;
				} else if ((cur_rf_rssi < tmp_max_rssi) &&
					   (cur_rf_rssi > tmp_sec_rssi)) {
					tmp_sec_rssi = cur_rf_rssi;
					sec_rssi_index = i;
				} else if (cur_rf_rssi == tmp_sec_rssi) {
					if (tmp_sec_rssi == tmp_min_rssi) {
						tmp_sec_rssi = cur_rf_rssi;
						sec_rssi_index = i;
					}
				} else if ((cur_rf_rssi < tmp_sec_rssi) &&
					   (cur_rf_rssi > tmp_min_rssi)) {
					;
				} else if (cur_rf_rssi == tmp_min_rssi) {
					if (tmp_sec_rssi == tmp_min_rssi) {
						tmp_min_rssi = cur_rf_rssi;
						min_rssi_index = i;
					}
				} else if (cur_rf_rssi < tmp_min_rssi) {
					tmp_min_rssi = cur_rf_rssi;
					min_rssi_index = i;
				}
			}
		}
	}

	rf_num = 0;
	if (DM_RxPathSelTable.cck_method == CCK_Rx_Version_2) {
		for (i = 0; i < RF90_PATH_MAX; i++) {
			if (priv->brfpath_rxenable[i]) {
				rf_num++;
				cur_cck_pwdb =
					 DM_RxPathSelTable.cck_pwdb_sta[i];

				if (rf_num == 1) {
					cck_rx_ver2_max_index = i;
					cck_rx_ver2_sec_index = i;
					tmp_cck_max_pwdb = cur_cck_pwdb;
					tmp_cck_min_pwdb = cur_cck_pwdb;
					tmp_cck_sec_pwdb = cur_cck_pwdb;
				} else if (rf_num == 2) {
					if (cur_cck_pwdb >= tmp_cck_max_pwdb) {
						tmp_cck_max_pwdb = cur_cck_pwdb;
						cck_rx_ver2_max_index = i;
					} else {
						tmp_cck_sec_pwdb = cur_cck_pwdb;
						tmp_cck_min_pwdb = cur_cck_pwdb;
						cck_rx_ver2_sec_index = i;
					}
				} else {
					if (cur_cck_pwdb > tmp_cck_max_pwdb) {
						tmp_cck_sec_pwdb =
							 tmp_cck_max_pwdb;
						cck_rx_ver2_sec_index =
							 cck_rx_ver2_max_index;
						tmp_cck_max_pwdb = cur_cck_pwdb;
						cck_rx_ver2_max_index = i;
					} else if (cur_cck_pwdb ==
						   tmp_cck_max_pwdb) {
						tmp_cck_sec_pwdb = cur_cck_pwdb;
						cck_rx_ver2_sec_index = i;
					} else if (PWDB_IN_RANGE) {
						tmp_cck_sec_pwdb = cur_cck_pwdb;
						cck_rx_ver2_sec_index = i;
					} else if (cur_cck_pwdb ==
						   tmp_cck_sec_pwdb) {
						if (tmp_cck_sec_pwdb ==
						    tmp_cck_min_pwdb) {
							tmp_cck_sec_pwdb =
								 cur_cck_pwdb;
							cck_rx_ver2_sec_index =
								 i;
						}
					} else if ((cur_cck_pwdb < tmp_cck_sec_pwdb) &&
						   (cur_cck_pwdb > tmp_cck_min_pwdb)) {
						;
					} else if (cur_cck_pwdb == tmp_cck_min_pwdb) {
						if (tmp_cck_sec_pwdb == tmp_cck_min_pwdb)
							tmp_cck_min_pwdb = cur_cck_pwdb;
					} else if (cur_cck_pwdb < tmp_cck_min_pwdb) {
						tmp_cck_min_pwdb = cur_cck_pwdb;
					}
				}

			}
		}
	}

	update_cck_rx_path = 0;
	if (DM_RxPathSelTable.cck_method == CCK_Rx_Version_2) {
		cck_default_Rx = cck_rx_ver2_max_index;
		cck_optional_Rx = cck_rx_ver2_sec_index;
		if (tmp_cck_max_pwdb != -64)
			update_cck_rx_path = 1;
	}

	if (tmp_min_rssi < DM_RxPathSelTable.SS_TH_low && disabled_rf_cnt < 2) {
		if ((tmp_max_rssi - tmp_min_rssi) >=
		     DM_RxPathSelTable.diff_TH) {
			DM_RxPathSelTable.rf_enable_rssi_th[min_rssi_index] =
				 tmp_max_rssi+5;
			rtl92e_set_bb_reg(dev, rOFDM0_TRxPathEnable,
					  0x1<<min_rssi_index, 0x0);
			rtl92e_set_bb_reg(dev, rOFDM1_TRxPathEnable,
					  0x1<<min_rssi_index, 0x0);
			disabled_rf_cnt++;
		}
		if (DM_RxPathSelTable.cck_method == CCK_Rx_Version_1) {
			cck_default_Rx = max_rssi_index;
			cck_optional_Rx = sec_rssi_index;
			if (tmp_max_rssi)
				update_cck_rx_path = 1;
		}
	}

	if (update_cck_rx_path) {
		DM_RxPathSelTable.cck_Rx_path = (cck_default_Rx<<2) |
						(cck_optional_Rx);
		rtl92e_set_bb_reg(dev, rCCK0_AFESetting, 0x0f000000,
				  DM_RxPathSelTable.cck_Rx_path);
	}

	if (DM_RxPathSelTable.disabledRF) {
		for (i = 0; i < 4; i++) {
			if ((DM_RxPathSelTable.disabledRF>>i) & 0x1) {
				if (tmp_max_rssi >=
				    DM_RxPathSelTable.rf_enable_rssi_th[i]) {
					rtl92e_set_bb_reg(dev,
							  rOFDM0_TRxPathEnable,
							  0x1 << i, 0x1);
					rtl92e_set_bb_reg(dev,
							  rOFDM1_TRxPathEnable,
							  0x1 << i, 0x1);
					DM_RxPathSelTable.rf_enable_rssi_th[i]
						 = 100;
					disabled_rf_cnt--;
				}
			}
		}
	}
}