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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_4__ {int agg_enable_bitmap; scalar_t__ ampdu_enable; } ;
struct TYPE_3__ {int* txseq_tid; } ;
struct sta_info {int* BA_starting_seqctrl; TYPE_2__ htpriv; TYPE_1__ sta_xmitpriv; scalar_t__ qos_option; } ;
struct qos_priv {scalar_t__ qos_option; } ;
struct pkt_attrib {int subtype; int hdrlen; int priority; int seqnum; int ampdu_en; scalar_t__ ht_en; int /*<<< orphan*/  ack_policy; int /*<<< orphan*/  eosp; scalar_t__ encrypt; scalar_t__ mdata; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; int /*<<< orphan*/  ra; struct sta_info* psta; } ;
struct mlme_priv {struct qos_priv qospriv; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_control; } ;
struct adapter {int /*<<< orphan*/  stapriv; struct mlme_priv mlmepriv; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int BIT (size_t) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SN_EQUAL (int,int) ; 
 scalar_t__ SN_LESS (int,int) ; 
 int /*<<< orphan*/  SetAckpolicy (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEOSP (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetFrDs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetFrameSubType (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetMData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetPriority (int*,int) ; 
 int /*<<< orphan*/  SetPrivacy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetSeqNum (int*,int) ; 
 int /*<<< orphan*/  SetToDs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int WIFI_DATA_TYPE ; 
 int /*<<< orphan*/  WIFI_STATION_STATE ; 
 int /*<<< orphan*/  WLANHDR_OFFSET ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_xmit_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bssid (struct mlme_priv*) ; 
 int /*<<< orphan*/  get_fwstate (struct mlme_priv*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sta_info* rtw_get_bcmc_stainfo (struct adapter*) ; 
 struct sta_info* rtw_get_stainfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

s32 rtw_make_wlanhdr(struct adapter *padapter, u8 *hdr, struct pkt_attrib *pattrib)
{
	u16 *qc;

	struct ieee80211_hdr *pwlanhdr = (struct ieee80211_hdr *)hdr;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct qos_priv *pqospriv = &pmlmepriv->qospriv;
	u8 qos_option = false;

	int res = _SUCCESS;
	__le16 *fctrl = &pwlanhdr->frame_control;

	struct sta_info *psta;

	if (pattrib->psta) {
		psta = pattrib->psta;
	} else {
		if (is_multicast_ether_addr(pattrib->ra))
			psta = rtw_get_bcmc_stainfo(padapter);
		else
			psta = rtw_get_stainfo(&padapter->stapriv, pattrib->ra);
	}

	memset(hdr, 0, WLANHDR_OFFSET);

	SetFrameSubType(fctrl, pattrib->subtype);

	if (pattrib->subtype & WIFI_DATA_TYPE) {
		if (check_fwstate(pmlmepriv,  WIFI_STATION_STATE)) {
			/* to_ds = 1, fr_ds = 0; */
			/* Data transfer to AP */
			SetToDs(fctrl);
			memcpy(pwlanhdr->addr1, get_bssid(pmlmepriv), ETH_ALEN);
			memcpy(pwlanhdr->addr2, pattrib->src, ETH_ALEN);
			memcpy(pwlanhdr->addr3, pattrib->dst, ETH_ALEN);

			if (pqospriv->qos_option)
				qos_option = true;
		} else if (check_fwstate(pmlmepriv,  WIFI_AP_STATE)) {
			/* to_ds = 0, fr_ds = 1; */
			SetFrDs(fctrl);
			memcpy(pwlanhdr->addr1, pattrib->dst, ETH_ALEN);
			memcpy(pwlanhdr->addr2, get_bssid(pmlmepriv), ETH_ALEN);
			memcpy(pwlanhdr->addr3, pattrib->src, ETH_ALEN);

			if (psta->qos_option)
				qos_option = true;
		} else if (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) ||
			   check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) {
			memcpy(pwlanhdr->addr1, pattrib->dst, ETH_ALEN);
			memcpy(pwlanhdr->addr2, pattrib->src, ETH_ALEN);
			memcpy(pwlanhdr->addr3, get_bssid(pmlmepriv), ETH_ALEN);

			if (psta->qos_option)
				qos_option = true;
		} else {
			RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("fw_state:%x is not allowed to xmit frame\n", get_fwstate(pmlmepriv)));
			res = _FAIL;
			goto exit;
		}

		if (pattrib->mdata)
			SetMData(fctrl);

		if (pattrib->encrypt)
			SetPrivacy(fctrl);

		if (qos_option) {
			qc = (unsigned short *)(hdr + pattrib->hdrlen - 2);

			if (pattrib->priority)
				SetPriority(qc, pattrib->priority);

			SetEOSP(qc, pattrib->eosp);

			SetAckpolicy(qc, pattrib->ack_policy);
		}

		/* TODO: fill HT Control Field */

		/* Update Seq Num will be handled by f/w */
		if (psta) {
			psta->sta_xmitpriv.txseq_tid[pattrib->priority]++;
			psta->sta_xmitpriv.txseq_tid[pattrib->priority] &= 0xFFF;

			pattrib->seqnum = psta->sta_xmitpriv.txseq_tid[pattrib->priority];

			SetSeqNum(hdr, pattrib->seqnum);

			/* check if enable ampdu */
			if (pattrib->ht_en && psta->htpriv.ampdu_enable) {
				if (psta->htpriv.agg_enable_bitmap & BIT(pattrib->priority))
					pattrib->ampdu_en = true;
			}

			/* re-check if enable ampdu by BA_starting_seqctrl */
			if (pattrib->ampdu_en) {
				u16 tx_seq;

				tx_seq = psta->BA_starting_seqctrl[pattrib->priority & 0x0f];

				/* check BA_starting_seqctrl */
				if (SN_LESS(pattrib->seqnum, tx_seq)) {
					pattrib->ampdu_en = false;/* AGG BK */
				} else if (SN_EQUAL(pattrib->seqnum, tx_seq)) {
					psta->BA_starting_seqctrl[pattrib->priority & 0x0f] = (tx_seq + 1) & 0xfff;

					pattrib->ampdu_en = true;/* AGG EN */
				} else {
					psta->BA_starting_seqctrl[pattrib->priority & 0x0f] = (pattrib->seqnum + 1) & 0xfff;
					pattrib->ampdu_en = true;/* AGG EN */
				}
			}
		}
	}
exit:

	return res;
}