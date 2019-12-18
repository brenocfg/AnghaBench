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
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {scalar_t__ mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_auth_rs_ok; int /*<<< orphan*/  rx_auth_rs_err; } ;
struct rtllib_device {int bHalfWirelessN24GMode; int /*<<< orphan*/  dev; TYPE_3__ current_network; int /*<<< orphan*/  (* SetWirelessMode ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* GetNmodeSupportBySecCfg ) (int /*<<< orphan*/ ) ;TYPE_2__* pHTInfo; TYPE_1__ softmac_stats; int /*<<< orphan*/  state; scalar_t__ open_wep; } ;
struct TYPE_5__ {int IOTAction; } ;

/* Variables and functions */
 int HT_IOT_ACT_PURE_N_MODE ; 
 scalar_t__ IEEE_G ; 
 scalar_t__ IEEE_N_24G ; 
 scalar_t__ IsHTHalfNmodeAPs (struct rtllib_device*) ; 
 int /*<<< orphan*/  RTLLIB_ASSOCIATING_AUTHENTICATED ; 
 scalar_t__ auth_parse (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rtllib_associate_abort (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_associate_step2 (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_auth_challenge (struct rtllib_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rtllib_rx_auth_resp(struct rtllib_device *ieee, struct sk_buff *skb)
{
	u16 errcode;
	u8 *challenge;
	int chlen = 0;
	bool bSupportNmode = true, bHalfSupportNmode = false;

	errcode = auth_parse(ieee->dev, skb, &challenge, &chlen);

	if (errcode) {
		ieee->softmac_stats.rx_auth_rs_err++;
		netdev_info(ieee->dev,
			    "Authentication response status code 0x%x",
			    errcode);
		rtllib_associate_abort(ieee);
		return;
	}

	if (ieee->open_wep || !challenge) {
		ieee->state = RTLLIB_ASSOCIATING_AUTHENTICATED;
		ieee->softmac_stats.rx_auth_rs_ok++;
		if (!(ieee->pHTInfo->IOTAction & HT_IOT_ACT_PURE_N_MODE)) {
			if (!ieee->GetNmodeSupportBySecCfg(ieee->dev)) {
				if (IsHTHalfNmodeAPs(ieee)) {
					bSupportNmode = true;
					bHalfSupportNmode = true;
				} else {
					bSupportNmode = false;
					bHalfSupportNmode = false;
				}
			}
		}
		/* Dummy wirless mode setting to avoid encryption issue */
		if (bSupportNmode) {
			ieee->SetWirelessMode(ieee->dev,
					      ieee->current_network.mode);
		} else {
			/*TODO*/
			ieee->SetWirelessMode(ieee->dev, IEEE_G);
		}

		if ((ieee->current_network.mode == IEEE_N_24G) &&
		    bHalfSupportNmode) {
			netdev_info(ieee->dev, "======>enter half N mode\n");
			ieee->bHalfWirelessN24GMode = true;
		} else {
			ieee->bHalfWirelessN24GMode = false;
		}
		rtllib_associate_step2(ieee);
	} else {
		rtllib_auth_challenge(ieee, challenge,  chlen);
	}
}