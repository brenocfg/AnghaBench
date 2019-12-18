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
typedef  int u16 ;
struct brcmf_if {int /*<<< orphan*/  ndev; } ;
struct brcmf_event_msg {int flags; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum nl80211_key_type { ____Placeholder_nl80211_key_type } nl80211_key_type ;

/* Variables and functions */
 int BRCMF_EVENT_MSG_GROUP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NL80211_KEYTYPE_GROUP ; 
 int NL80211_KEYTYPE_PAIRWISE ; 
 int /*<<< orphan*/  cfg80211_michael_mic_failure (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32
brcmf_notify_mic_status(struct brcmf_if *ifp,
			const struct brcmf_event_msg *e, void *data)
{
	u16 flags = e->flags;
	enum nl80211_key_type key_type;

	if (flags & BRCMF_EVENT_MSG_GROUP)
		key_type = NL80211_KEYTYPE_GROUP;
	else
		key_type = NL80211_KEYTYPE_PAIRWISE;

	cfg80211_michael_mic_failure(ifp->ndev, (u8 *)&e->addr, key_type, -1,
				     NULL, GFP_KERNEL);

	return 0;
}