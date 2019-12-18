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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct r8192_priv {scalar_t__ undecorated_smoothed_pwdb; int framesync; scalar_t__ reset_count; scalar_t__ framesyncMonitor; TYPE_2__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ state; scalar_t__ bfsync_enable; int fsync_state; TYPE_1__* pHTInfo; int /*<<< orphan*/  fsync_seconddiff_ratethreshold; int /*<<< orphan*/  fsync_firstdiff_ratethreshold; int /*<<< orphan*/  fsync_rate_bitmap; int /*<<< orphan*/  fsync_multiple_timeinterval; int /*<<< orphan*/  fsync_time_interval; int /*<<< orphan*/  fsync_rssi_threshold; } ;
struct TYPE_3__ {scalar_t__ IOTPeer; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_HALDM ; 
#define  Default_Fsync 130 
 scalar_t__ HT_IOT_PEER_BROADCOM ; 
#define  HW_Fsync 129 
 scalar_t__ RTLLIB_LINKED ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RegC38_Default ; 
 scalar_t__ RegC38_Fsync_AP_BCM ; 
 scalar_t__ RegC38_NonFsync_Other_AP ; 
 scalar_t__ RegC38_TH ; 
#define  SW_Fsync 128 
 int /*<<< orphan*/  _rtl92e_dm_end_hw_fsync (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_end_sw_fsync (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_start_hw_fsync (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_start_sw_fsync (struct net_device*) ; 
 int /*<<< orphan*/  rOFDM0_RxDetector3 ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,int /*<<< orphan*/ ,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_check_fsync(struct net_device *dev)
{
#define	RegC38_Default			0
#define	RegC38_NonFsync_Other_AP	1
#define	RegC38_Fsync_AP_BCM		2
	struct r8192_priv *priv = rtllib_priv(dev);
	static u8 reg_c38_State = RegC38_Default;
	static u32 reset_cnt;

	RT_TRACE(COMP_HALDM,
		 "RSSI %d TimeInterval %d MultipleTimeInterval %d\n",
		 priv->rtllib->fsync_rssi_threshold,
		 priv->rtllib->fsync_time_interval,
		 priv->rtllib->fsync_multiple_timeinterval);
	RT_TRACE(COMP_HALDM,
		 "RateBitmap 0x%x FirstDiffRateThreshold %d SecondDiffRateThreshold %d\n",
		 priv->rtllib->fsync_rate_bitmap,
		 priv->rtllib->fsync_firstdiff_ratethreshold,
		 priv->rtllib->fsync_seconddiff_ratethreshold);

	if (priv->rtllib->state == RTLLIB_LINKED &&
	    priv->rtllib->pHTInfo->IOTPeer == HT_IOT_PEER_BROADCOM) {
		if (priv->rtllib->bfsync_enable == 0) {
			switch (priv->rtllib->fsync_state) {
			case Default_Fsync:
				_rtl92e_dm_start_hw_fsync(dev);
				priv->rtllib->fsync_state = HW_Fsync;
				break;
			case SW_Fsync:
				_rtl92e_dm_end_sw_fsync(dev);
				_rtl92e_dm_start_hw_fsync(dev);
				priv->rtllib->fsync_state = HW_Fsync;
				break;
			case HW_Fsync:
			default:
				break;
			}
		} else {
			switch (priv->rtllib->fsync_state) {
			case Default_Fsync:
				_rtl92e_dm_start_sw_fsync(dev);
				priv->rtllib->fsync_state = SW_Fsync;
				break;
			case HW_Fsync:
				_rtl92e_dm_end_hw_fsync(dev);
				_rtl92e_dm_start_sw_fsync(dev);
				priv->rtllib->fsync_state = SW_Fsync;
				break;
			case SW_Fsync:
			default:
				break;

			}
		}
		if (priv->framesyncMonitor) {
			if (reg_c38_State != RegC38_Fsync_AP_BCM) {
				rtl92e_writeb(dev, rOFDM0_RxDetector3, 0x95);

				reg_c38_State = RegC38_Fsync_AP_BCM;
			}
		}
	} else {
		switch (priv->rtllib->fsync_state) {
		case HW_Fsync:
			_rtl92e_dm_end_hw_fsync(dev);
			priv->rtllib->fsync_state = Default_Fsync;
			break;
		case SW_Fsync:
			_rtl92e_dm_end_sw_fsync(dev);
			priv->rtllib->fsync_state = Default_Fsync;
			break;
		case Default_Fsync:
		default:
			break;
		}

		if (priv->framesyncMonitor) {
			if (priv->rtllib->state == RTLLIB_LINKED) {
				if (priv->undecorated_smoothed_pwdb <=
				    RegC38_TH) {
					if (reg_c38_State !=
					    RegC38_NonFsync_Other_AP) {
						rtl92e_writeb(dev,
							      rOFDM0_RxDetector3,
							      0x90);

						reg_c38_State =
						     RegC38_NonFsync_Other_AP;
					}
				} else if (priv->undecorated_smoothed_pwdb >=
					   (RegC38_TH+5)) {
					if (reg_c38_State) {
						rtl92e_writeb(dev,
							rOFDM0_RxDetector3,
							priv->framesync);
						reg_c38_State = RegC38_Default;
					}
				}
			} else {
				if (reg_c38_State) {
					rtl92e_writeb(dev, rOFDM0_RxDetector3,
						      priv->framesync);
					reg_c38_State = RegC38_Default;
				}
			}
		}
	}
	if (priv->framesyncMonitor) {
		if (priv->reset_count != reset_cnt) {
			rtl92e_writeb(dev, rOFDM0_RxDetector3,
				       priv->framesync);
			reg_c38_State = RegC38_Default;
			reset_cnt = priv->reset_count;
		}
	} else {
		if (reg_c38_State) {
			rtl92e_writeb(dev, rOFDM0_RxDetector3,
				       priv->framesync);
			reg_c38_State = RegC38_Default;
		}
	}
}