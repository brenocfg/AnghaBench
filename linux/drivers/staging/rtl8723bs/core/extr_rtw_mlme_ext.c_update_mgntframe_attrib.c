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
struct pkt_attrib {int hdrlen; int nr_frags; int priority; int qsel; scalar_t__ rate; int bswenc; int qos_en; int ht_en; int sgi; int retry_ctrl; scalar_t__ mbssid; int /*<<< orphan*/  seqnum; int /*<<< orphan*/  ch_offset; int /*<<< orphan*/  bwmode; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  raid; scalar_t__ pktlen; scalar_t__ mac_id; } ;
struct mlme_ext_priv {scalar_t__ tx_rate; int /*<<< orphan*/  mgnt_seq; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_WIDTH_20 ; 
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 scalar_t__ IEEE80211_CCK_RATE_1MB ; 
 int /*<<< orphan*/  WIRELESS_11B ; 
 int /*<<< orphan*/  WIRELESS_11G ; 
 int /*<<< orphan*/  _NO_PRIVACY_ ; 
 int /*<<< orphan*/  rtw_get_mgntframe_raid (struct adapter*,int /*<<< orphan*/ ) ; 

void update_mgntframe_attrib(struct adapter *padapter, struct pkt_attrib *pattrib)
{
	u8 wireless_mode;
	struct mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);

	/* memset((u8 *)(pattrib), 0, sizeof(struct pkt_attrib)); */

	pattrib->hdrlen = 24;
	pattrib->nr_frags = 1;
	pattrib->priority = 7;
	pattrib->mac_id = 0;
	pattrib->qsel = 0x12;

	pattrib->pktlen = 0;

	if (pmlmeext->tx_rate == IEEE80211_CCK_RATE_1MB)
		wireless_mode = WIRELESS_11B;
	else
		wireless_mode = WIRELESS_11G;
	pattrib->raid =  rtw_get_mgntframe_raid(padapter, wireless_mode);
	pattrib->rate = pmlmeext->tx_rate;

	pattrib->encrypt = _NO_PRIVACY_;
	pattrib->bswenc = false;

	pattrib->qos_en = false;
	pattrib->ht_en = false;
	pattrib->bwmode = CHANNEL_WIDTH_20;
	pattrib->ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	pattrib->sgi = false;

	pattrib->seqnum = pmlmeext->mgnt_seq;

	pattrib->retry_ctrl = true;

	pattrib->mbssid = 0;

}