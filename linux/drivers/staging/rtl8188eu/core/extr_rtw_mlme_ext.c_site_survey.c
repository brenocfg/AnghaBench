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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rtw_ieee80211_channel {unsigned char hw_value; int flags; } ;
struct TYPE_3__ {size_t channel_idx; size_t ch_num; int scan_mode; int /*<<< orphan*/  state; scalar_t__ bss_cnt; TYPE_2__* ssid; struct rtw_ieee80211_channel* ch; } ;
struct mlme_ext_info {int state; } ;
struct mlme_ext_priv {int chan_scan_time; unsigned char cur_channel; TYPE_1__ sitesurvey_res; int /*<<< orphan*/  cur_bwmode; int /*<<< orphan*/  cur_ch_offset; struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;
typedef  enum rt_scan_type { ____Placeholder_rt_scan_type } rt_scan_type ;
struct TYPE_4__ {scalar_t__ ssid_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 int /*<<< orphan*/  HT_CHANNEL_WIDTH_20 ; 
 int /*<<< orphan*/  HW_VAR_INITIAL_GAIN ; 
 int /*<<< orphan*/  HW_VAR_MLME_SITESURVEY ; 
 int RTW_IEEE80211_CHAN_PASSIVE_SCAN ; 
 int RTW_SSID_SCAN_AMOUNT ; 
 int /*<<< orphan*/  Restore_DM_Func_Flag (struct adapter*) ; 
 int SCAN_ACTIVE ; 
 int /*<<< orphan*/  SCAN_COMPLETE ; 
 int /*<<< orphan*/  SCAN_DISABLE ; 
 int SCAN_PASSIVE ; 
 int SURVEY_TO ; 
 int /*<<< orphan*/  SelectChannel (struct adapter*,unsigned char) ; 
 int /*<<< orphan*/  Set_MSR (struct adapter*,int) ; 
 scalar_t__ is_client_associated_to_ap (struct adapter*) ; 
 int /*<<< orphan*/  issue_action_BSSCoexistPacket (struct adapter*) ; 
 int /*<<< orphan*/  issue_nulldata (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  issue_probereq (struct adapter*,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  report_surveydone_event (struct adapter*) ; 
 scalar_t__ rtw_hal_antdiv_before_linked (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_channel_bwmode (struct adapter*,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_survey_timer (struct mlme_ext_priv*,int) ; 

__attribute__((used)) static void site_survey(struct adapter *padapter)
{
	unsigned char survey_channel = 0, val8;
	enum rt_scan_type ScanType = SCAN_PASSIVE;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u32 initialgain = 0;
	struct rtw_ieee80211_channel *ch;

	if (pmlmeext->sitesurvey_res.channel_idx < pmlmeext->sitesurvey_res.ch_num) {
		ch = &pmlmeext->sitesurvey_res.ch[pmlmeext->sitesurvey_res.channel_idx];
		survey_channel = ch->hw_value;
		ScanType = (ch->flags & RTW_IEEE80211_CHAN_PASSIVE_SCAN) ? SCAN_PASSIVE : SCAN_ACTIVE;
	}

	if (survey_channel != 0) {
		/* PAUSE 4-AC Queue when site_survey */
		/* rtw_hal_get_hwreg(padapter, HW_VAR_TXPAUSE, (u8 *)(&val8)); */
		/* val8 |= 0x0f; */
		/* rtw_hal_set_hwreg(padapter, HW_VAR_TXPAUSE, (u8 *)(&val8)); */
		if (pmlmeext->sitesurvey_res.channel_idx == 0)
			set_channel_bwmode(padapter, survey_channel, HAL_PRIME_CHNL_OFFSET_DONT_CARE, HT_CHANNEL_WIDTH_20);
		else
			SelectChannel(padapter, survey_channel);

		if (ScanType == SCAN_ACTIVE) { /* obey the channel plan setting... */
			int i;

			for (i = 0; i < RTW_SSID_SCAN_AMOUNT; i++) {
				if (pmlmeext->sitesurvey_res.ssid[i].ssid_length) {
					/* todo: to issue two probe req??? */
					issue_probereq(padapter,
					&(pmlmeext->sitesurvey_res.ssid[i]),
								NULL, false);
					/* msleep(SURVEY_TO>>1); */
					issue_probereq(padapter,
					&(pmlmeext->sitesurvey_res.ssid[i]),
								NULL, false);
				}
			}

			if (pmlmeext->sitesurvey_res.scan_mode == SCAN_ACTIVE) {
				/* todo: to issue two probe req??? */
				issue_probereq(padapter, NULL, NULL, false);
				/* msleep(SURVEY_TO>>1); */
				issue_probereq(padapter, NULL, NULL, false);
			}

			if (pmlmeext->sitesurvey_res.scan_mode == SCAN_ACTIVE) {
				/* todo: to issue two probe req??? */
				issue_probereq(padapter, NULL, NULL, false);
				/* msleep(SURVEY_TO>>1); */
				issue_probereq(padapter, NULL, NULL, false);
			}
		}

		set_survey_timer(pmlmeext, pmlmeext->chan_scan_time);
	} else {
		/*  20100721:Interrupt scan operation here. */
		/*  For SW antenna diversity before link, it needs to switch to another antenna and scan again. */
		/*  It compares the scan result and select better one to do connection. */
		if (rtw_hal_antdiv_before_linked(padapter)) {
			pmlmeext->sitesurvey_res.bss_cnt = 0;
			pmlmeext->sitesurvey_res.channel_idx = -1;
			pmlmeext->chan_scan_time = SURVEY_TO / 2;
			set_survey_timer(pmlmeext, pmlmeext->chan_scan_time);
			return;
		}

		pmlmeext->sitesurvey_res.state = SCAN_COMPLETE;

		/* switch back to the original channel */

		set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);

		/* flush 4-AC Queue after site_survey */
		/* val8 = 0; */
		/* rtw_hal_set_hwreg(padapter, HW_VAR_TXPAUSE, (u8 *)(&val8)); */

		/* config MSR */
		Set_MSR(padapter, (pmlmeinfo->state & 0x3));

		initialgain = 0xff; /* restore RX GAIN */
		rtw_hal_set_hwreg(padapter, HW_VAR_INITIAL_GAIN, (u8 *)(&initialgain));
		/* turn on dynamic functions */
		Restore_DM_Func_Flag(padapter);
		/* Switch_DM_Func(padapter, DYNAMIC_ALL_FUNC_ENABLE, true); */

		if (is_client_associated_to_ap(padapter))
			issue_nulldata(padapter, NULL, 0, 3, 500);

		val8 = 0; /* survey done */
		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_SITESURVEY, (u8 *)(&val8));

		report_surveydone_event(padapter);

		pmlmeext->chan_scan_time = SURVEY_TO;
		pmlmeext->sitesurvey_res.state = SCAN_DISABLE;

		issue_action_BSSCoexistPacket(padapter);
		issue_action_BSSCoexistPacket(padapter);
		issue_action_BSSCoexistPacket(padapter);
	}
}