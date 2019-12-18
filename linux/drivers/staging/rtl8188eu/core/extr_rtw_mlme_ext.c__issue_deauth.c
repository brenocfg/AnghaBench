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
typedef  unsigned char u8 ;
struct xmit_priv {int dummy; } ;
struct pkt_attrib {int retry_ctrl; int pktlen; int last_txcmdsz; } ;
struct xmit_frame {scalar_t__ buf_addr; struct pkt_attrib attrib; } ;
struct wlan_bssid_ex {unsigned char* MacAddress; } ;
struct mlme_ext_info {struct wlan_bssid_ex network; } ;
struct mlme_ext_priv {int /*<<< orphan*/  mgnt_seq; struct mlme_ext_info mlmext_info; } ;
struct ieee80211_hdr_3addr {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; scalar_t__ frame_control; } ;
struct adapter {int /*<<< orphan*/  eeprompriv; struct mlme_ext_priv mlmeextpriv; struct xmit_priv xmitpriv; } ;
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  SetFrameSubType (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSeqNum (struct ieee80211_hdr*,int /*<<< orphan*/ ) ; 
 int TXDESC_OFFSET ; 
 int /*<<< orphan*/  WIFI_DEAUTH ; 
 int WLANHDR_OFFSET ; 
 int _FAIL ; 
 int /*<<< orphan*/  _RSON_CODE_ ; 
 int _SUCCESS ; 
 struct xmit_frame* alloc_mgtxmitframe (struct xmit_priv*) ; 
 scalar_t__ cpu_to_le16 (unsigned short) ; 
 int /*<<< orphan*/  dump_mgntframe (struct adapter*,struct xmit_frame*) ; 
 int dump_mgntframe_and_wait_ack (struct adapter*,struct xmit_frame*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 unsigned char* myid (int /*<<< orphan*/ *) ; 
 unsigned char* rtw_set_fixed_ie (unsigned char*,int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  update_mgntframe_attrib (struct adapter*,struct pkt_attrib*) ; 

__attribute__((used)) static int _issue_deauth(struct adapter *padapter, unsigned char *da,
			 unsigned short reason, bool wait_ack)
{
	struct xmit_frame *pmgntframe;
	struct pkt_attrib *pattrib;
	unsigned char *pframe;
	struct ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	struct wlan_bssid_ex *pnetwork = &pmlmeinfo->network;
	int ret = _FAIL;
	__le16 le_tmp;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	if (pmgntframe == NULL)
		goto exit;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);
	pattrib->retry_ctrl = false;

	memset(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (struct ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;

	ether_addr_copy(pwlanhdr->addr1, da);
	ether_addr_copy(pwlanhdr->addr2, myid(&padapter->eeprompriv));
	ether_addr_copy(pwlanhdr->addr3, pnetwork->MacAddress);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_DEAUTH);

	pframe += sizeof(struct ieee80211_hdr_3addr);
	pattrib->pktlen = sizeof(struct ieee80211_hdr_3addr);

	le_tmp = cpu_to_le16(reason);
	pframe = rtw_set_fixed_ie(pframe, _RSON_CODE_, &le_tmp,
				  &pattrib->pktlen);

	pattrib->last_txcmdsz = pattrib->pktlen;

	if (wait_ack) {
		ret = dump_mgntframe_and_wait_ack(padapter, pmgntframe);
	} else {
		dump_mgntframe(padapter, pmgntframe);
		ret = _SUCCESS;
	}

exit:
	return ret;
}