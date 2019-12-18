#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int hdrlen; int iv_len; scalar_t__ bdecrypted; int /*<<< orphan*/  privacy; int /*<<< orphan*/ * ta; } ;
struct recv_frame_hdr {struct rx_pkt_attrib attrib; } ;
struct TYPE_6__ {struct recv_frame_hdr hdr; } ;
union recv_frame {TYPE_3__ u; } ;
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sta_priv {int dummy; } ;
struct sta_info {scalar_t__ ieee8021x_blocked; } ;
struct TYPE_5__ {int /*<<< orphan*/  free_recv_queue; } ;
struct TYPE_4__ {int dot11AuthAlgrthm; } ;
struct adapter {TYPE_2__ recvpriv; TYPE_1__ securitypriv; struct sta_priv stapriv; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int LLC_HEADER_SIZE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int /*<<< orphan*/ * get_recvframe_data (union recv_frame*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_free_recvframe (union recv_frame*,int /*<<< orphan*/ *) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ *) ; 

union recv_frame *portctrl(struct adapter *adapter, union recv_frame *precv_frame)
{
	u8 *psta_addr = NULL;
	u8 *ptr;
	uint  auth_alg;
	struct recv_frame_hdr *pfhdr;
	struct sta_info *psta;
	struct sta_priv *pstapriv;
	union recv_frame *prtnframe;
	u16 ether_type = 0;
	u16  eapol_type = 0x888e;/* for Funia BD's WPA issue */
	struct rx_pkt_attrib *pattrib;

	pstapriv = &adapter->stapriv;

	auth_alg = adapter->securitypriv.dot11AuthAlgrthm;

	ptr = get_recvframe_data(precv_frame);
	pfhdr = &precv_frame->u.hdr;
	pattrib = &pfhdr->attrib;
	psta_addr = pattrib->ta;

	prtnframe = NULL;

	psta = rtw_get_stainfo(pstapriv, psta_addr);

	RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("########portctrl:adapter->securitypriv.dot11AuthAlgrthm =%d\n", adapter->securitypriv.dot11AuthAlgrthm));

	if (auth_alg == 2) {
		if ((psta) && (psta->ieee8021x_blocked)) {
			__be16 be_tmp;

			/* blocked */
			/* only accept EAPOL frame */
			RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("########portctrl:psta->ieee8021x_blocked == 1\n"));

			prtnframe = precv_frame;

			/* get ether_type */
			ptr = ptr+pfhdr->attrib.hdrlen+pfhdr->attrib.iv_len+LLC_HEADER_SIZE;
			memcpy(&be_tmp, ptr, 2);
			ether_type = ntohs(be_tmp);

			if (ether_type == eapol_type)
				prtnframe = precv_frame;
			else {
				/* free this frame */
				rtw_free_recvframe(precv_frame, &adapter->recvpriv.free_recv_queue);
				prtnframe = NULL;
			}
		} else {
			/* allowed */
			/* check decryption status, and decrypt the frame if needed */
			RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("########portctrl:psta->ieee8021x_blocked == 0\n"));
			RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("portctrl:precv_frame->hdr.attrib.privacy =%x\n", precv_frame->u.hdr.attrib.privacy));

			if (pattrib->bdecrypted == 0)
				RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("portctrl:prxstat->decrypted =%x\n", pattrib->bdecrypted));

			prtnframe = precv_frame;
			/* check is the EAPOL frame or not (Rekey) */
			/* if (ether_type == eapol_type) { */
			/* 	RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("########portctrl:ether_type == 0x888e\n")); */
				/* check Rekey */

			/* 	prtnframe =precv_frame; */
			/*  */
			/* else { */
			/* 	RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("########portctrl:ether_type = 0x%04x\n", ether_type)); */
			/*  */
		}
	} else
		prtnframe = precv_frame;

	return prtnframe;
}