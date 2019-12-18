#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 struct sk_buff* ieee80211_auth_resp (struct ieee80211_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  softmac_mgmt_xmit (struct sk_buff*,struct ieee80211_device*) ; 

__attribute__((used)) static void ieee80211_resp_to_auth(struct ieee80211_device *ieee, int s,
				   u8 *dest)
{
	struct sk_buff *buf = ieee80211_auth_resp(ieee, s, dest);

	if (buf)
		softmac_mgmt_xmit(buf, ieee);
}