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
struct noise_info {int bPauseDIG; int IGIValue; int max_time; int /*<<< orphan*/  chan; } ;
struct net_device {int dummy; } ;
struct mlme_ext_priv {int /*<<< orphan*/  cur_channel; } ;
struct TYPE_4__ {int qual; int level; int noise; int updated; } ;
struct iw_statistics {TYPE_2__ qual; } ;
struct hal_com_data {int /*<<< orphan*/  odmpriv; } ;
struct TYPE_3__ {int signal_strength; int signal_qual; int noise; int /*<<< orphan*/  rssi; } ;
struct adapter {struct iw_statistics iwstats; TYPE_1__ recvpriv; struct mlme_ext_priv mlmeextpriv; int /*<<< orphan*/  mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int,int,...) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  HAL_ODM_NOISE_MONITOR ; 
 int IW_QUAL_ALL_UPDATED ; 
 int IW_QUAL_DBM ; 
 int /*<<< orphan*/  LeaveAllPowerSaveModeDirect (struct adapter*) ; 
 int /*<<< orphan*/  PS_DENY_IOCTL ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int check_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ odm_SignalScaleMapping (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtw_hal_get_odm_var (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  rtw_hal_set_odm_var (struct adapter*,int /*<<< orphan*/ ,struct noise_info*,int) ; 
 scalar_t__ rtw_linked_check (struct adapter*) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtw_ps_deny (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_ps_deny_cancel (struct adapter*,int /*<<< orphan*/ ) ; 
 int translate_percentage_to_dbm (int) ; 

__attribute__((used)) static struct iw_statistics *rtw_get_wireless_stats(struct net_device *dev)
{
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(dev);
	struct iw_statistics *piwstats =&padapter->iwstats;
	int tmp_level = 0;
	int tmp_qual = 0;
	int tmp_noise = 0;

	if (check_fwstate(&padapter->mlmepriv, _FW_LINKED) != true) {
		piwstats->qual.qual = 0;
		piwstats->qual.level = 0;
		piwstats->qual.noise = 0;
		/* DBG_871X("No link  level:%d, qual:%d, noise:%d\n", tmp_level, tmp_qual, tmp_noise); */
	} else {
		#ifdef CONFIG_SIGNAL_DISPLAY_DBM
		tmp_level = translate_percentage_to_dbm(padapter->recvpriv.signal_strength);
		#else
		#ifdef CONFIG_SKIP_SIGNAL_SCALE_MAPPING
		{
			/* Do signal scale mapping when using percentage as the unit of signal strength, since the scale mapping is skipped in odm */

			struct hal_com_data *pHal = GET_HAL_DATA(padapter);

			tmp_level = (u8)odm_SignalScaleMapping(&pHal->odmpriv, padapter->recvpriv.signal_strength);
		}
		#else
		tmp_level = padapter->recvpriv.signal_strength;
		#endif
		#endif

		tmp_qual = padapter->recvpriv.signal_qual;
#if defined(CONFIG_SIGNAL_DISPLAY_DBM) && defined(CONFIG_BACKGROUND_NOISE_MONITOR)
		if (rtw_linked_check(padapter)) {
			struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
			struct noise_info info;
			info.bPauseDIG = true;
			info.IGIValue = 0x1e;
			info.max_time = 100;/* ms */
			info.chan = pmlmeext->cur_channel ;/* rtw_get_oper_ch(padapter); */
			rtw_ps_deny(padapter, PS_DENY_IOCTL);
			LeaveAllPowerSaveModeDirect(padapter);

			rtw_hal_set_odm_var(padapter, HAL_ODM_NOISE_MONITOR,&info, false);
			/* ODM_InbandNoise_Monitor(podmpriv, true, 0x20, 100); */
			rtw_ps_deny_cancel(padapter, PS_DENY_IOCTL);
			rtw_hal_get_odm_var(padapter, HAL_ODM_NOISE_MONITOR,&(info.chan), &(padapter->recvpriv.noise));
			DBG_871X("chan:%d, noise_level:%d\n", info.chan, padapter->recvpriv.noise);
		}
#endif
		tmp_noise = padapter->recvpriv.noise;
		DBG_871X("level:%d, qual:%d, noise:%d, rssi (%d)\n", tmp_level, tmp_qual, tmp_noise, padapter->recvpriv.rssi);

		piwstats->qual.level = tmp_level;
		piwstats->qual.qual = tmp_qual;
		piwstats->qual.noise = tmp_noise;
	}
	piwstats->qual.updated = IW_QUAL_ALL_UPDATED ;/* IW_QUAL_DBM; */

	#ifdef CONFIG_SIGNAL_DISPLAY_DBM
	piwstats->qual.updated = piwstats->qual.updated | IW_QUAL_DBM;
	#endif

	return &padapter->iwstats;
}