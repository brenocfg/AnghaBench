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
struct TYPE_2__ {scalar_t__ PreSTAConnectState; scalar_t__ CurSTAConnectState; scalar_t__ rssi_val; scalar_t__ rssi_high_power_highthresh; scalar_t__ curpd_thstate; scalar_t__ rssi_low_thresh; scalar_t__ rssi_high_thresh; scalar_t__ rssi_high_power_lowthresh; scalar_t__ prepd_thstate; scalar_t__ dig_algorithm_switch; } ;

/* Variables and functions */
 scalar_t__ DIG_PD_AT_HIGH_POWER ; 
 scalar_t__ DIG_PD_AT_LOW_POWER ; 
 scalar_t__ DIG_PD_AT_NORMAL_POWER ; 
 scalar_t__ DIG_STA_CONNECT ; 
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 TYPE_1__ dm_digtable ; 
 scalar_t__ rOFDM0_RxDetector1 ; 
 scalar_t__ rOFDM0_XATxAFE ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,scalar_t__,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_pd_th(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	static u8 initialized, force_write;
	static u32 reset_cnt;

	if (dm_digtable.dig_algorithm_switch) {
		initialized = 0;
		reset_cnt = 0;
	}

	if (dm_digtable.PreSTAConnectState == dm_digtable.CurSTAConnectState) {
		if (dm_digtable.CurSTAConnectState == DIG_STA_CONNECT) {
			if (dm_digtable.rssi_val >=
			    dm_digtable.rssi_high_power_highthresh)
				dm_digtable.curpd_thstate =
							DIG_PD_AT_HIGH_POWER;
			else if (dm_digtable.rssi_val <=
				 dm_digtable.rssi_low_thresh)
				dm_digtable.curpd_thstate =
							DIG_PD_AT_LOW_POWER;
			else if ((dm_digtable.rssi_val >=
				  dm_digtable.rssi_high_thresh) &&
				 (dm_digtable.rssi_val <
				  dm_digtable.rssi_high_power_lowthresh))
				dm_digtable.curpd_thstate =
							DIG_PD_AT_NORMAL_POWER;
			else
				dm_digtable.curpd_thstate =
						dm_digtable.prepd_thstate;
		} else {
			dm_digtable.curpd_thstate = DIG_PD_AT_LOW_POWER;
		}
	} else {
		dm_digtable.curpd_thstate = DIG_PD_AT_LOW_POWER;
	}

	if (priv->reset_count != reset_cnt) {
		force_write = 1;
		reset_cnt = priv->reset_count;
	}

	if ((dm_digtable.prepd_thstate != dm_digtable.curpd_thstate) ||
	    (initialized <= 3) || force_write) {
		if (dm_digtable.curpd_thstate == DIG_PD_AT_LOW_POWER) {
			if (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
				rtl92e_writeb(dev, (rOFDM0_XATxAFE+3), 0x00);
			else
				rtl92e_writeb(dev, rOFDM0_RxDetector1, 0x42);
		} else if (dm_digtable.curpd_thstate ==
			   DIG_PD_AT_NORMAL_POWER) {
			if (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
				rtl92e_writeb(dev, (rOFDM0_XATxAFE+3), 0x20);
			else
				rtl92e_writeb(dev, rOFDM0_RxDetector1, 0x44);
		} else if (dm_digtable.curpd_thstate == DIG_PD_AT_HIGH_POWER) {
			if (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
				rtl92e_writeb(dev, (rOFDM0_XATxAFE+3), 0x10);
			else
				rtl92e_writeb(dev, rOFDM0_RxDetector1, 0x43);
		}
		dm_digtable.prepd_thstate = dm_digtable.curpd_thstate;
		if (initialized <= 3)
			initialized++;
		force_write = 0;
	}
}