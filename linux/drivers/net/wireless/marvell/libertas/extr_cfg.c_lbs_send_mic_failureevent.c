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
typedef  scalar_t__ u32 ;
struct lbs_private {int /*<<< orphan*/  assoc_bss; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MACREG_INT_CODE_MIC_ERR_MULTICAST ; 
 int /*<<< orphan*/  NL80211_KEYTYPE_GROUP ; 
 int /*<<< orphan*/  NL80211_KEYTYPE_PAIRWISE ; 
 int /*<<< orphan*/  cfg80211_michael_mic_failure (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void lbs_send_mic_failureevent(struct lbs_private *priv, u32 event)
{
	cfg80211_michael_mic_failure(priv->dev,
		priv->assoc_bss,
		event == MACREG_INT_CODE_MIC_ERR_MULTICAST ?
			NL80211_KEYTYPE_GROUP :
			NL80211_KEYTYPE_PAIRWISE,
		-1,
		NULL,
		GFP_KERNEL);
}