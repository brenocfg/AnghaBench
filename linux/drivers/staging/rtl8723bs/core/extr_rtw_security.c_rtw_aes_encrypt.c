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
typedef  int u32 ;
struct xmit_priv {scalar_t__ frag_len; } ;
struct TYPE_4__ {int* skey; } ;
struct pkt_attrib {scalar_t__ encrypt; scalar_t__ nr_frags; scalar_t__ last_txcmdsz; scalar_t__ hdrlen; scalar_t__ iv_len; scalar_t__ icv_len; int /*<<< orphan*/  ra; TYPE_2__ dot118021x_UncstKey; } ;
struct xmit_frame {int* buf_addr; struct pkt_attrib attrib; } ;
struct security_priv {size_t dot118021XGrpKeyid; TYPE_1__* dot118021XGrpKey; } ;
struct adapter {struct xmit_priv xmitpriv; struct security_priv securitypriv; } ;
typedef  scalar_t__ sint ;
struct TYPE_3__ {int* skey; } ;
typedef  int /*<<< orphan*/  SIZE_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  AES_SW_ENC_CNT_INC (struct security_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_MCAST (int /*<<< orphan*/ ) ; 
 scalar_t__ RND4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int TXDESC_OFFSET ; 
 scalar_t__ _AES_ ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_security_c_ ; 
 int /*<<< orphan*/  aes_cipher (int*,scalar_t__,int*,scalar_t__) ; 

u32 rtw_aes_encrypt(struct adapter *padapter, u8 *pxmitframe)
{	/*  exclude ICV */


	/*static*/
/* 	unsigned char message[MAX_MSG_SIZE]; */

	/* Intermediate Buffers */
	sint	curfragnum, length;
	u32 prwskeylen;
	u8 *pframe, *prwskey;	/*  *payload,*iv */
	u8   hw_hdr_offset = 0;
	/* struct	sta_info 	*stainfo = NULL; */
	struct	pkt_attrib	 *pattrib = &((struct xmit_frame *)pxmitframe)->attrib;
	struct	security_priv *psecuritypriv = &padapter->securitypriv;
	struct	xmit_priv 	*pxmitpriv = &padapter->xmitpriv;

/* 	uint	offset = 0; */
	u32 res = _SUCCESS;

	if (((struct xmit_frame *)pxmitframe)->buf_addr == NULL)
		return _FAIL;

	hw_hdr_offset = TXDESC_OFFSET;
	pframe = ((struct xmit_frame *)pxmitframe)->buf_addr + hw_hdr_offset;

	/* 4 start to encrypt each fragment */
	if (pattrib->encrypt == _AES_) {
		RT_TRACE(_module_rtl871x_security_c_, _drv_err_, ("rtw_aes_encrypt: stainfo!= NULL!!!\n"));

		if (IS_MCAST(pattrib->ra))
			prwskey = psecuritypriv->dot118021XGrpKey[psecuritypriv->dot118021XGrpKeyid].skey;
		else
			/* prwskey =&stainfo->dot118021x_UncstKey.skey[0]; */
			prwskey = pattrib->dot118021x_UncstKey.skey;

		prwskeylen = 16;

		for (curfragnum = 0; curfragnum < pattrib->nr_frags; curfragnum++) {
			if ((curfragnum+1) == pattrib->nr_frags) {	/* 4 the last fragment */
				length = pattrib->last_txcmdsz-pattrib->hdrlen-pattrib->iv_len-pattrib->icv_len;

				aes_cipher(prwskey, pattrib->hdrlen, pframe, length);
			} else {
				length = pxmitpriv->frag_len-pattrib->hdrlen-pattrib->iv_len-pattrib->icv_len;

				aes_cipher(prwskey, pattrib->hdrlen, pframe, length);
				pframe += pxmitpriv->frag_len;
				pframe = (u8 *)RND4((SIZE_PTR)(pframe));
			}
		}

		AES_SW_ENC_CNT_INC(psecuritypriv, pattrib->ra);
	}
	return res;
}