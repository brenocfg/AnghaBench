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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_auth_rs_err; int /*<<< orphan*/  rx_auth_rs_ok; } ;
struct TYPE_5__ {scalar_t__ mode; } ;
struct ieee80211_device {int bHalfWirelessN24GMode; TYPE_3__ softmac_stats; int /*<<< orphan*/  dev; TYPE_2__ current_network; int /*<<< orphan*/  (* SetWirelessMode ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* GetNmodeSupportBySecCfg ) (int /*<<< orphan*/ ) ;TYPE_1__* pHTInfo; int /*<<< orphan*/  state; scalar_t__ open_wep; } ;
struct TYPE_4__ {int IOTAction; } ;

/* Variables and functions */
 int HT_IOT_ACT_PURE_N_MODE ; 
 int /*<<< orphan*/  IEEE80211_ASSOCIATING_AUTHENTICATED ; 
 int /*<<< orphan*/  IEEE80211_DEBUG_MGMT (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE_G ; 
 scalar_t__ IEEE_N_24G ; 
 scalar_t__ IsHTHalfNmodeAPs (struct ieee80211_device*) ; 
 int /*<<< orphan*/  auth_parse (struct sk_buff*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  ieee80211_associate_abort (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_associate_step2 (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_auth_challenge (struct ieee80211_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ieee80211_check_auth_response(struct ieee80211_device *ieee,
					  struct sk_buff *skb)
{
	/* default support N mode, disable halfNmode */
	bool bSupportNmode = true, bHalfSupportNmode = false;
	u16 errcode;
	u8 *challenge;
	int chlen = 0;
	u32 iotAction;

	errcode = auth_parse(skb, &challenge, &chlen);
	if (!errcode) {
		if (ieee->open_wep || !challenge) {
			ieee->state = IEEE80211_ASSOCIATING_AUTHENTICATED;
			ieee->softmac_stats.rx_auth_rs_ok++;
			iotAction = ieee->pHTInfo->IOTAction;
			if (!(iotAction & HT_IOT_ACT_PURE_N_MODE)) {
				if (!ieee->GetNmodeSupportBySecCfg(ieee->dev)) {
					/* WEP or TKIP encryption */
					if (IsHTHalfNmodeAPs(ieee)) {
						bSupportNmode = true;
						bHalfSupportNmode = true;
					} else {
						bSupportNmode = false;
						bHalfSupportNmode = false;
					}
					netdev_dbg(ieee->dev, "SEC(%d, %d)\n",
							bSupportNmode,
							bHalfSupportNmode);
				}
			}
			/* Dummy wirless mode setting- avoid encryption issue */
			if (bSupportNmode) {
				/* N mode setting */
				ieee->SetWirelessMode(ieee->dev,
						ieee->current_network.mode);
			} else {
				/* b/g mode setting - TODO */
				ieee->SetWirelessMode(ieee->dev, IEEE_G);
			}

			if (ieee->current_network.mode == IEEE_N_24G &&
					bHalfSupportNmode) {
				netdev_dbg(ieee->dev, "enter half N mode\n");
				ieee->bHalfWirelessN24GMode = true;
			} else {
				ieee->bHalfWirelessN24GMode = false;
			}
			ieee80211_associate_step2(ieee);
		} else {
			ieee80211_auth_challenge(ieee, challenge, chlen);
		}
	} else {
		ieee->softmac_stats.rx_auth_rs_err++;
		IEEE80211_DEBUG_MGMT("Auth response status code 0x%x", errcode);
		ieee80211_associate_abort(ieee);
	}
}