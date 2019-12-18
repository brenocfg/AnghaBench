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
struct xmit_priv {scalar_t__ frag_len; } ;
struct TYPE_4__ {int /*<<< orphan*/ * skey; } ;
struct pkt_attrib {scalar_t__ encrypt; scalar_t__ nr_frags; int hdrlen; int iv_len; scalar_t__ last_txcmdsz; scalar_t__ icv_len; scalar_t__ bswenc; scalar_t__ priority; scalar_t__ qos_en; TYPE_2__ dot11tkiptxmickey; int /*<<< orphan*/  ra; } ;
struct xmit_frame {int* buf_addr; struct pkt_attrib attrib; } ;
struct security_priv {size_t dot118021XGrpKeyid; TYPE_1__* dot118021XGrptxmickey; } ;
struct mic_data {int dummy; } ;
struct adapter {struct xmit_priv xmitpriv; struct security_priv securitypriv; } ;
typedef  scalar_t__ sint ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_3__ {int /*<<< orphan*/ * skey; } ;
typedef  int /*<<< orphan*/  SIZE_PTR ;

/* Variables and functions */
 scalar_t__ IS_MCAST (int /*<<< orphan*/ ) ; 
 scalar_t__ RND4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int TXDESC_OFFSET ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 scalar_t__ _TKIP_ ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_xmit_c_ ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  rtw_secgetmic (struct mic_data*,int*) ; 
 int /*<<< orphan*/  rtw_secmicappend (struct mic_data*,int*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_secmicsetkey (struct mic_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 xmitframe_addmic(struct adapter *padapter, struct xmit_frame *pxmitframe)
{
	sint			curfragnum, length;
	u8 *pframe, *payload, mic[8];
	struct	mic_data		micdata;
	/* struct	sta_info 	*stainfo; */
	struct	pkt_attrib	 *pattrib = &pxmitframe->attrib;
	struct	security_priv *psecuritypriv = &padapter->securitypriv;
	struct	xmit_priv 	*pxmitpriv = &padapter->xmitpriv;
	u8 priority[4] = {0x0, 0x0, 0x0, 0x0};
	u8 hw_hdr_offset = 0;
	sint bmcst = IS_MCAST(pattrib->ra);

/*
	if (pattrib->psta)
	{
		stainfo = pattrib->psta;
	}
	else
	{
		DBG_871X("%s, call rtw_get_stainfo()\n", __func__);
		stainfo =rtw_get_stainfo(&padapter->stapriv ,&pattrib->ra[0]);
	}

	if (stainfo == NULL)
	{
		DBG_871X("%s, psta ==NUL\n", __func__);
		return _FAIL;
	}

	if (!(stainfo->state &_FW_LINKED))
	{
		DBG_871X("%s, psta->state(0x%x) != _FW_LINKED\n", __func__, stainfo->state);
		return _FAIL;
	}
*/

	hw_hdr_offset = TXDESC_OFFSET;

	if (pattrib->encrypt == _TKIP_) { /* if (psecuritypriv->dot11PrivacyAlgrthm == _TKIP_PRIVACY_) */
		/* encode mic code */
		/* if (stainfo!= NULL) */
		{
			u8 null_key[16] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

			pframe = pxmitframe->buf_addr + hw_hdr_offset;

			if (bmcst) {
				if (!memcmp(psecuritypriv->dot118021XGrptxmickey[psecuritypriv->dot118021XGrpKeyid].skey, null_key, 16)) {
					/* DbgPrint("\nxmitframe_addmic:stainfo->dot11tkiptxmickey == 0\n"); */
					/* msleep(10); */
					return _FAIL;
				}
				/* start to calculate the mic code */
				rtw_secmicsetkey(&micdata, psecuritypriv->dot118021XGrptxmickey[psecuritypriv->dot118021XGrpKeyid].skey);
			} else {
				if (!memcmp(&pattrib->dot11tkiptxmickey.skey[0], null_key, 16)) {
					/* DbgPrint("\nxmitframe_addmic:stainfo->dot11tkiptxmickey == 0\n"); */
					/* msleep(10); */
					return _FAIL;
				}
				/* start to calculate the mic code */
				rtw_secmicsetkey(&micdata, &pattrib->dot11tkiptxmickey.skey[0]);
			}

			if (pframe[1]&1) {   /* ToDS == 1 */
				rtw_secmicappend(&micdata, &pframe[16], 6);  /* DA */
				if (pframe[1]&2)  /* From Ds == 1 */
					rtw_secmicappend(&micdata, &pframe[24], 6);
				else
				rtw_secmicappend(&micdata, &pframe[10], 6);
			} else {	/* ToDS == 0 */
				rtw_secmicappend(&micdata, &pframe[4], 6);   /* DA */
				if (pframe[1]&2)  /* From Ds == 1 */
					rtw_secmicappend(&micdata, &pframe[16], 6);
				else
					rtw_secmicappend(&micdata, &pframe[10], 6);

			}

			/* if (pqospriv->qos_option == 1) */
			if (pattrib->qos_en)
				priority[0] = (u8)pxmitframe->attrib.priority;


			rtw_secmicappend(&micdata, &priority[0], 4);

			payload = pframe;

			for (curfragnum = 0; curfragnum < pattrib->nr_frags; curfragnum++) {
				payload = (u8 *)RND4((SIZE_PTR)(payload));
				RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("===curfragnum =%d, pframe = 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x,!!!\n",
					curfragnum, *payload, *(payload+1), *(payload+2), *(payload+3), *(payload+4), *(payload+5), *(payload+6), *(payload+7)));

				payload = payload+pattrib->hdrlen+pattrib->iv_len;
				RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("curfragnum =%d pattrib->hdrlen =%d pattrib->iv_len =%d", curfragnum, pattrib->hdrlen, pattrib->iv_len));
				if ((curfragnum+1) == pattrib->nr_frags) {
					length = pattrib->last_txcmdsz-pattrib->hdrlen-pattrib->iv_len-((pattrib->bswenc) ? pattrib->icv_len : 0);
					rtw_secmicappend(&micdata, payload, length);
					payload = payload+length;
				} else {
					length = pxmitpriv->frag_len-pattrib->hdrlen-pattrib->iv_len-((pattrib->bswenc) ? pattrib->icv_len : 0);
					rtw_secmicappend(&micdata, payload, length);
					payload = payload+length+pattrib->icv_len;
					RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("curfragnum =%d length =%d pattrib->icv_len =%d", curfragnum, length, pattrib->icv_len));
				}
			}
			rtw_secgetmic(&micdata, &(mic[0]));
			RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("xmitframe_addmic: before add mic code!!!\n"));
			RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("xmitframe_addmic: pattrib->last_txcmdsz =%d!!!\n", pattrib->last_txcmdsz));
			RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("xmitframe_addmic: mic[0]= 0x%.2x , mic[1]= 0x%.2x , mic[2]= 0x%.2x , mic[3]= 0x%.2x\n\
  mic[4]= 0x%.2x , mic[5]= 0x%.2x , mic[6]= 0x%.2x , mic[7]= 0x%.2x !!!!\n",
				mic[0], mic[1], mic[2], mic[3], mic[4], mic[5], mic[6], mic[7]));
			/* add mic code  and add the mic code length in last_txcmdsz */

			memcpy(payload, &(mic[0]), 8);
			pattrib->last_txcmdsz += 8;

			RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_, ("\n ========last pkt ========\n"));
			payload = payload-pattrib->last_txcmdsz+8;
			for (curfragnum = 0; curfragnum < pattrib->last_txcmdsz; curfragnum = curfragnum+8)
					RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_, (" %.2x,  %.2x,  %.2x,  %.2x,  %.2x,  %.2x,  %.2x,  %.2x ",
					*(payload+curfragnum), *(payload+curfragnum+1), *(payload+curfragnum+2), *(payload+curfragnum+3),
					*(payload+curfragnum+4), *(payload+curfragnum+5), *(payload+curfragnum+6), *(payload+curfragnum+7)));
			}
/*
			else {
				RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("xmitframe_addmic: rtw_get_stainfo == NULL!!!\n"));
			}
*/
	}
	return _SUCCESS;
}