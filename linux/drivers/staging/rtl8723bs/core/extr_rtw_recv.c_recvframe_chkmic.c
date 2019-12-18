#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {scalar_t__ encrypt; size_t key_index; int hdrlen; int iv_len; int icv_len; int bdecrypted; int /*<<< orphan*/ * ra; scalar_t__ priority; int /*<<< orphan*/ * ta; } ;
struct TYPE_7__ {int len; scalar_t__* rx_data; struct rx_pkt_attrib attrib; } ;
struct TYPE_8__ {TYPE_3__ hdr; } ;
union recv_frame {TYPE_4__ u; } ;
typedef  scalar_t__ uint ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_6__ {scalar_t__* skey; } ;
struct sta_info {TYPE_2__ dot11tkiprxmickey; } ;
struct security_priv {int binstallGrpkey; int bcheck_grpkey; TYPE_1__* dot118021XGrprxmickey; } ;
struct mlme_ext_info {size_t key_index; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct adapter {int /*<<< orphan*/  stapriv; struct mlme_ext_priv mlmeextpriv; struct security_priv securitypriv; } ;
typedef  int sint ;
struct TYPE_5__ {scalar_t__* skey; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 int IS_MCAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FAIL ; 
 int _SUCCESS ; 
 scalar_t__ _TKIP_ ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int /*<<< orphan*/  recvframe_pull_tail (union recv_frame*,int) ; 
 struct sta_info* rtw_get_stainfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_handle_tkip_mic_err (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_seccalctkipmic (scalar_t__*,scalar_t__*,scalar_t__*,int,scalar_t__*,unsigned char) ; 

sint recvframe_chkmic(struct adapter *adapter,  union recv_frame *precvframe)
{

	sint	i, res = _SUCCESS;
	u32 datalen;
	u8 miccode[8];
	u8 bmic_err = false, brpt_micerror = true;
	u8 *pframe, *payload, *pframemic;
	u8 *mickey;
	/* u8 *iv, rxdata_key_idx = 0; */
	struct	sta_info 	*stainfo;
	struct	rx_pkt_attrib	*prxattrib = &precvframe->u.hdr.attrib;
	struct	security_priv *psecuritypriv = &adapter->securitypriv;

	struct mlme_ext_priv *pmlmeext = &adapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	stainfo = rtw_get_stainfo(&adapter->stapriv, &prxattrib->ta[0]);

	if (prxattrib->encrypt == _TKIP_) {
		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("\n recvframe_chkmic:prxattrib->encrypt == _TKIP_\n"));
		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("\n recvframe_chkmic:da = 0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x\n",
			prxattrib->ra[0], prxattrib->ra[1], prxattrib->ra[2], prxattrib->ra[3], prxattrib->ra[4], prxattrib->ra[5]));

		/* calculate mic code */
		if (stainfo) {
			if (IS_MCAST(prxattrib->ra)) {
				/* mickey =&psecuritypriv->dot118021XGrprxmickey.skey[0]; */
				/* iv = precvframe->u.hdr.rx_data+prxattrib->hdrlen; */
				/* rxdata_key_idx =(((iv[3])>>6)&0x3) ; */
				mickey = &psecuritypriv->dot118021XGrprxmickey[prxattrib->key_index].skey[0];

				RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("\n recvframe_chkmic: bcmc key\n"));
				/* DBG_871X("\n recvframe_chkmic: bcmc key psecuritypriv->dot118021XGrpKeyid(%d), pmlmeinfo->key_index(%d) , recv key_id(%d)\n", */
				/* 								psecuritypriv->dot118021XGrpKeyid, pmlmeinfo->key_index, rxdata_key_idx); */

				if (psecuritypriv->binstallGrpkey == false) {
					res = _FAIL;
					RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("\n recvframe_chkmic:didn't install group key!!!!!!!!!!\n"));
					DBG_871X("\n recvframe_chkmic:didn't install group key!!!!!!!!!!\n");
					goto exit;
				}
			} else {
				mickey = &stainfo->dot11tkiprxmickey.skey[0];
				RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("\n recvframe_chkmic: unicast key\n"));
			}

			datalen = precvframe->u.hdr.len-prxattrib->hdrlen-prxattrib->iv_len-prxattrib->icv_len-8;/* icv_len included the mic code */
			pframe = precvframe->u.hdr.rx_data;
			payload = pframe+prxattrib->hdrlen+prxattrib->iv_len;

			RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("\n prxattrib->iv_len =%d prxattrib->icv_len =%d\n", prxattrib->iv_len, prxattrib->icv_len));


			rtw_seccalctkipmic(mickey, pframe, payload, datalen, &miccode[0], (unsigned char)prxattrib->priority); /* care the length of the data */

			pframemic = payload+datalen;

			bmic_err = false;

			for (i = 0; i < 8; i++) {
				if (miccode[i] != *(pframemic+i)) {
					RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("recvframe_chkmic:miccode[%d](%02x) != *(pframemic+%d)(%02x) ", i, miccode[i], i, *(pframemic+i)));
					bmic_err = true;
				}
			}


			if (bmic_err == true) {

				RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("\n *(pframemic-8)-*(pframemic-1) = 0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x\n",
					*(pframemic-8), *(pframemic-7), *(pframemic-6), *(pframemic-5), *(pframemic-4), *(pframemic-3), *(pframemic-2), *(pframemic-1)));
				RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("\n *(pframemic-16)-*(pframemic-9) = 0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x\n",
					*(pframemic-16), *(pframemic-15), *(pframemic-14), *(pframemic-13), *(pframemic-12), *(pframemic-11), *(pframemic-10), *(pframemic-9)));

				{
					uint i;
					RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("\n ======demp packet (len =%d) ======\n", precvframe->u.hdr.len));
					for (i = 0; i < precvframe->u.hdr.len; i = i+8) {
						RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x",
							*(precvframe->u.hdr.rx_data+i), *(precvframe->u.hdr.rx_data+i+1),
							*(precvframe->u.hdr.rx_data+i+2), *(precvframe->u.hdr.rx_data+i+3),
							*(precvframe->u.hdr.rx_data+i+4), *(precvframe->u.hdr.rx_data+i+5),
							*(precvframe->u.hdr.rx_data+i+6), *(precvframe->u.hdr.rx_data+i+7)));
					}
					RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("\n ======demp packet end [len =%d]======\n", precvframe->u.hdr.len));
					RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("\n hrdlen =%d,\n", prxattrib->hdrlen));
				}

				RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("ra = 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x psecuritypriv->binstallGrpkey =%d ",
					prxattrib->ra[0], prxattrib->ra[1], prxattrib->ra[2],
					prxattrib->ra[3], prxattrib->ra[4], prxattrib->ra[5], psecuritypriv->binstallGrpkey));

				/*  double check key_index for some timing issue , */
				/*  cannot compare with psecuritypriv->dot118021XGrpKeyid also cause timing issue */
				if ((IS_MCAST(prxattrib->ra) == true)  && (prxattrib->key_index != pmlmeinfo->key_index))
					brpt_micerror = false;

				if ((prxattrib->bdecrypted == true) && (brpt_micerror == true)) {
					rtw_handle_tkip_mic_err(adapter, (u8)IS_MCAST(prxattrib->ra));
					RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, (" mic error :prxattrib->bdecrypted =%d ", prxattrib->bdecrypted));
					DBG_871X(" mic error :prxattrib->bdecrypted =%d\n", prxattrib->bdecrypted);
				} else {
					RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, (" mic error :prxattrib->bdecrypted =%d ", prxattrib->bdecrypted));
					DBG_871X(" mic error :prxattrib->bdecrypted =%d\n", prxattrib->bdecrypted);
				}

				res = _FAIL;

			} else {
				/* mic checked ok */
				if ((psecuritypriv->bcheck_grpkey == false) && (IS_MCAST(prxattrib->ra) == true)) {
					psecuritypriv->bcheck_grpkey = true;
					RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("psecuritypriv->bcheck_grpkey =true"));
				}
			}

		} else
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("recvframe_chkmic: rtw_get_stainfo == NULL!!!\n"));

		recvframe_pull_tail(precvframe, 8);

	}

exit:
	return res;

}