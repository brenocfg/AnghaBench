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
struct mlme_ext_info {scalar_t__ assoc_AP_vendor; int /*<<< orphan*/  HT_enable; } ;
struct mlme_ext_priv {int cur_bwmode; struct mlme_ext_info mlmext_info; } ;
struct ieee80211_ht_cap {int /*<<< orphan*/  cap_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int HT_CHANNEL_WIDTH_40 ; 
 scalar_t__ HT_IOT_PEER_RALINK ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 

int support_short_GI(struct adapter *padapter, struct ieee80211_ht_cap *pHT_caps)
{
	unsigned char bit_offset;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	if (!(pmlmeinfo->HT_enable))
		return _FAIL;

	if (pmlmeinfo->assoc_AP_vendor == HT_IOT_PEER_RALINK)
		return _FAIL;

	bit_offset = (pmlmeext->cur_bwmode & HT_CHANNEL_WIDTH_40) ? 6 : 5;

	if (__le16_to_cpu(pHT_caps->cap_info) & (0x1 << bit_offset))
		return _SUCCESS;
	else
		return _FAIL;
}