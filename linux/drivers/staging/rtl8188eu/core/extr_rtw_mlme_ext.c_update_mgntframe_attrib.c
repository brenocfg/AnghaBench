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
struct pkt_attrib {int hdrlen; int nr_frags; int priority; int qsel; int raid; int bswenc; int qos_en; int ht_en; int sgi; int retry_ctrl; int /*<<< orphan*/  seqnum; int /*<<< orphan*/  ch_offset; int /*<<< orphan*/  bwmode; int /*<<< orphan*/  encrypt; scalar_t__ pktlen; scalar_t__ mac_id; } ;
struct mlme_ext_priv {int cur_wireless_mode; int /*<<< orphan*/  mgnt_seq; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 int /*<<< orphan*/  HT_CHANNEL_WIDTH_20 ; 
 int WIRELESS_11B ; 
 int /*<<< orphan*/  _NO_PRIVACY_ ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void update_mgntframe_attrib(struct adapter *padapter, struct pkt_attrib *pattrib)
{
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	memset((u8 *)(pattrib), 0, sizeof(struct pkt_attrib));

	pattrib->hdrlen = 24;
	pattrib->nr_frags = 1;
	pattrib->priority = 7;
	pattrib->mac_id = 0;
	pattrib->qsel = 0x12;

	pattrib->pktlen = 0;

	if (pmlmeext->cur_wireless_mode & WIRELESS_11B)
		pattrib->raid = 6;/* b mode */
	else
		pattrib->raid = 5;/* a/g mode */

	pattrib->encrypt = _NO_PRIVACY_;
	pattrib->bswenc = false;

	pattrib->qos_en = false;
	pattrib->ht_en = false;
	pattrib->bwmode = HT_CHANNEL_WIDTH_20;
	pattrib->ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	pattrib->sgi = false;

	pattrib->seqnum = pmlmeext->mgnt_seq;

	pattrib->retry_ctrl = true;
}