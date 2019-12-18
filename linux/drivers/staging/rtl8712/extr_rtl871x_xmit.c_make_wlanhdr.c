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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned short u16 ;
struct TYPE_2__ {int* txseq_tid; } ;
struct sta_info {TYPE_1__ sta_xmitpriv; } ;
struct qos_priv {scalar_t__ qos_option; } ;
struct pkt_attrib {int subtype; int hdrlen; size_t priority; int seqnum; int /*<<< orphan*/  ra; struct sta_info* psta; int /*<<< orphan*/  ack_policy; scalar_t__ encrypt; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct mlme_priv {struct qos_priv qospriv; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_ctl; } ;
struct _adapter {int /*<<< orphan*/  stapriv; struct mlme_priv mlmepriv; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  SetAckpolicy (unsigned short*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetFrDs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetFrameSubType (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetPriority (unsigned short*,size_t) ; 
 int /*<<< orphan*/  SetPrivacy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetSeqNum (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetToDs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int WIFI_DATA_TYPE ; 
 int /*<<< orphan*/  WIFI_MP_STATE ; 
 int /*<<< orphan*/  WIFI_STATION_STATE ; 
 int /*<<< orphan*/  WLANHDR_OFFSET ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bssid (struct mlme_priv*) ; 
 int is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sta_info* r8712_get_bcmc_stainfo (struct _adapter*) ; 
 struct sta_info* r8712_get_stainfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int make_wlanhdr(struct _adapter *padapter, u8 *hdr,
			struct pkt_attrib *pattrib)
{
	u16 *qc;

	struct ieee80211_hdr *pwlanhdr = (struct ieee80211_hdr *)hdr;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct qos_priv *pqospriv = &pmlmepriv->qospriv;
	__le16 *fctrl = &pwlanhdr->frame_ctl;

	memset(hdr, 0, WLANHDR_OFFSET);
	SetFrameSubType(fctrl, pattrib->subtype);
	if (pattrib->subtype & WIFI_DATA_TYPE) {
		if (check_fwstate(pmlmepriv,  WIFI_STATION_STATE)) {
			/* to_ds = 1, fr_ds = 0; */
			SetToDs(fctrl);
			memcpy(pwlanhdr->addr1, get_bssid(pmlmepriv),
				ETH_ALEN);
			memcpy(pwlanhdr->addr2, pattrib->src, ETH_ALEN);
			memcpy(pwlanhdr->addr3, pattrib->dst, ETH_ALEN);
		} else if (check_fwstate(pmlmepriv, WIFI_AP_STATE)) {
			/* to_ds = 0, fr_ds = 1; */
			SetFrDs(fctrl);
			memcpy(pwlanhdr->addr1, pattrib->dst, ETH_ALEN);
			memcpy(pwlanhdr->addr2, get_bssid(pmlmepriv),
				ETH_ALEN);
			memcpy(pwlanhdr->addr3, pattrib->src, ETH_ALEN);
		} else if (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) ||
			   check_fwstate(pmlmepriv,
					 WIFI_ADHOC_MASTER_STATE)) {
			memcpy(pwlanhdr->addr1, pattrib->dst, ETH_ALEN);
			memcpy(pwlanhdr->addr2, pattrib->src, ETH_ALEN);
			memcpy(pwlanhdr->addr3, get_bssid(pmlmepriv),
				ETH_ALEN);
		} else if (check_fwstate(pmlmepriv, WIFI_MP_STATE)) {
			memcpy(pwlanhdr->addr1, pattrib->dst, ETH_ALEN);
			memcpy(pwlanhdr->addr2, pattrib->src, ETH_ALEN);
			memcpy(pwlanhdr->addr3, get_bssid(pmlmepriv),
				ETH_ALEN);
		} else {
			return -EINVAL;
		}

		if (pattrib->encrypt)
			SetPrivacy(fctrl);
		if (pqospriv->qos_option) {
			qc = (unsigned short *)(hdr + pattrib->hdrlen - 2);
			if (pattrib->priority)
				SetPriority(qc, pattrib->priority);
			SetAckpolicy(qc, pattrib->ack_policy);
		}
		/* TODO: fill HT Control Field */
		/* Update Seq Num will be handled by f/w */
		{
			struct sta_info *psta;
			bool bmcst = is_multicast_ether_addr(pattrib->ra);

			if (pattrib->psta) {
				psta = pattrib->psta;
			} else {
				if (bmcst)
					psta = r8712_get_bcmc_stainfo(padapter);
				else
					psta =
					 r8712_get_stainfo(&padapter->stapriv,
					 pattrib->ra);
			}
			if (psta) {
				psta->sta_xmitpriv.txseq_tid
						  [pattrib->priority]++;
				psta->sta_xmitpriv.txseq_tid[pattrib->priority]
						   &= 0xFFF;
				pattrib->seqnum = psta->sta_xmitpriv.
						  txseq_tid[pattrib->priority];
				SetSeqNum(hdr, pattrib->seqnum);
			}
		}
	}
	return 0;
}