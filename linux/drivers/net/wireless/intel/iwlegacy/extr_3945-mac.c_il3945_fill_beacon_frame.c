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
struct il_priv {TYPE_1__* beacon_skb; } ;
struct ieee80211_hdr {int dummy; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  il_is_associated (struct il_priv*) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_hdr*,int /*<<< orphan*/ ,int) ; 

unsigned int
il3945_fill_beacon_frame(struct il_priv *il, struct ieee80211_hdr *hdr,
			 int left)
{

	if (!il_is_associated(il) || !il->beacon_skb)
		return 0;

	if (il->beacon_skb->len > left)
		return 0;

	memcpy(hdr, il->beacon_skb->data, il->beacon_skb->len);

	return il->beacon_skb->len;
}