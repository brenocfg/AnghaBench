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
typedef  scalar_t__ u32 ;
struct r8192_priv {scalar_t__ reset_count; scalar_t__ CurrentChannelBW; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ pre_connect_state; scalar_t__ cur_connect_state; scalar_t__ rssi_val; scalar_t__ rssi_high_power_highthresh; scalar_t__ curpd_thstate; scalar_t__ rssi_low_thresh; scalar_t__ rssi_high_thresh; scalar_t__ rssi_high_power_lowthresh; scalar_t__ prepd_thstate; scalar_t__ dig_algorithm_switch; } ;

/* Variables and functions */
 scalar_t__ DIG_CONNECT ; 
 scalar_t__ DIG_PD_AT_HIGH_POWER ; 
 scalar_t__ DIG_PD_AT_LOW_POWER ; 
 scalar_t__ DIG_PD_AT_NORMAL_POWER ; 
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 TYPE_1__ dm_digtable ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 scalar_t__ rOFDM0_RxDetector1 ; 
 scalar_t__ rOFDM0_XATxAFE ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,scalar_t__,int) ; 

__attribute__((used)) static void dm_pd_th(
	struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	static u8				initialized, force_write;
	static u32			reset_cnt;

	if (dm_digtable.dig_algorithm_switch) {
		initialized = 0;
		reset_cnt = 0;
	}

	if (dm_digtable.pre_connect_state == dm_digtable.cur_connect_state) {
		if (dm_digtable.cur_connect_state == DIG_CONNECT) {
			if (dm_digtable.rssi_val >= dm_digtable.rssi_high_power_highthresh)
				dm_digtable.curpd_thstate = DIG_PD_AT_HIGH_POWER;
			else if (dm_digtable.rssi_val <= dm_digtable.rssi_low_thresh)
				dm_digtable.curpd_thstate = DIG_PD_AT_LOW_POWER;
			else if ((dm_digtable.rssi_val >= dm_digtable.rssi_high_thresh) &&
					(dm_digtable.rssi_val < dm_digtable.rssi_high_power_lowthresh))
				dm_digtable.curpd_thstate = DIG_PD_AT_NORMAL_POWER;
			else
				dm_digtable.curpd_thstate = dm_digtable.prepd_thstate;
		} else {
			dm_digtable.curpd_thstate = DIG_PD_AT_LOW_POWER;
		}
	} else { /* disconnected -> connected or connected -> disconnected */
		dm_digtable.curpd_thstate = DIG_PD_AT_LOW_POWER;
	}

	/*  if silent reset happened, we should rewrite the values back */
	if (priv->reset_count != reset_cnt) {
		force_write = 1;
		reset_cnt = priv->reset_count;
	}

	{
		if ((dm_digtable.prepd_thstate != dm_digtable.curpd_thstate) ||
		    (initialized <= 3) || force_write) {
			/*DbgPrint("Write PD_TH state = %d\n", DM_DigTable.CurPD_THState);*/
			if (dm_digtable.curpd_thstate == DIG_PD_AT_LOW_POWER) {
				/*  Lower PD_TH for OFDM. */
				if (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) {
					/* 2008/01/11 MH 40MHZ 90/92 register are not the same.
					 * 2008/02/05 MH SD3-Jerry 92U/92E PD_TH are the same.
					 */
					write_nic_byte(dev, (rOFDM0_XATxAFE+3), 0x00);
					/*else if (priv->card_8192 == HARDWARE_TYPE_RTL8190P)
						write_nic_byte(dev, rOFDM0_RxDetector1, 0x40);
					*/
				} else
					write_nic_byte(dev, rOFDM0_RxDetector1, 0x42);
			} else if (dm_digtable.curpd_thstate == DIG_PD_AT_NORMAL_POWER) {
				/* Higher PD_TH for OFDM. */
				if (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) {
					/* 2008/01/11 MH 40MHZ 90/92 register are not the same.
					 * 2008/02/05 MH SD3-Jerry 92U/92E PD_TH are the same.
					 */
					write_nic_byte(dev, (rOFDM0_XATxAFE+3), 0x20);
					/*else if (priv->card_8192 == HARDWARE_TYPE_RTL8190P)
						write_nic_byte(dev, rOFDM0_RxDetector1, 0x42);
					*/
				} else
					write_nic_byte(dev, rOFDM0_RxDetector1, 0x44);
			} else if (dm_digtable.curpd_thstate == DIG_PD_AT_HIGH_POWER) {
				/* Higher PD_TH for OFDM for high power state. */
				if (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) {
					write_nic_byte(dev, (rOFDM0_XATxAFE+3), 0x10);
					/*else if (priv->card_8192 == HARDWARE_TYPE_RTL8190P)
						write_nic_byte(dev, rOFDM0_RxDetector1, 0x41);
					*/
				} else
					write_nic_byte(dev, rOFDM0_RxDetector1, 0x43);
			}
			dm_digtable.prepd_thstate = dm_digtable.curpd_thstate;
			if (initialized <= 3)
				initialized++;
			force_write = 0;
		}
	}
}