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
struct rx_pkt_attrib {scalar_t__ encrypt; int hdrlen; size_t key_index; int iv_len; int /*<<< orphan*/  ra; } ;
struct TYPE_5__ {int len; scalar_t__ rx_data; struct rx_pkt_attrib attrib; } ;
struct TYPE_6__ {TYPE_2__ hdr; } ;
union recv_frame {TYPE_3__ u; } ;
typedef  size_t u8 ;
typedef  int u32 ;
struct security_priv {int* dot11DefKeylen; TYPE_1__* dot11DefKey; } ;
struct arc4context {int dummy; } ;
struct adapter {struct security_priv securitypriv; } ;
typedef  int sint ;
struct TYPE_4__ {size_t* skey; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WEP_SW_DEC_CNT_INC (struct security_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ _WEP104_ ; 
 scalar_t__ _WEP40_ ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_security_c_ ; 
 int /*<<< orphan*/  arcfour_encrypt (struct arc4context*,size_t*,size_t*,int) ; 
 int /*<<< orphan*/  arcfour_init (struct arc4context*,size_t*,int) ; 
 int /*<<< orphan*/  getcrc32 (size_t*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 

void rtw_wep_decrypt(struct adapter  *padapter, u8 *precvframe)
{
	/*  exclude ICV */
	u8 crc[4];
	struct arc4context	 mycontext;
	sint	length;
	u32 keylength;
	u8 *pframe, *payload, *iv, wepkey[16];
	u8  keyindex;
	struct	rx_pkt_attrib	 *prxattrib = &(((union recv_frame *)precvframe)->u.hdr.attrib);
	struct	security_priv *psecuritypriv = &padapter->securitypriv;

	pframe = (unsigned char *)((union recv_frame *)precvframe)->u.hdr.rx_data;

	/* start to decrypt recvframe */
	if ((prxattrib->encrypt == _WEP40_) || (prxattrib->encrypt == _WEP104_)) {
		iv = pframe+prxattrib->hdrlen;
		/* keyindex =(iv[3]&0x3); */
		keyindex = prxattrib->key_index;
		keylength = psecuritypriv->dot11DefKeylen[keyindex];
		memcpy(&wepkey[0], iv, 3);
		/* memcpy(&wepkey[3], &psecuritypriv->dot11DefKey[psecuritypriv->dot11PrivacyKeyIndex].skey[0], keylength); */
		memcpy(&wepkey[3], &psecuritypriv->dot11DefKey[keyindex].skey[0], keylength);
		length = ((union recv_frame *)precvframe)->u.hdr.len-prxattrib->hdrlen-prxattrib->iv_len;

		payload = pframe+prxattrib->iv_len+prxattrib->hdrlen;

		/* decrypt payload include icv */
		arcfour_init(&mycontext, wepkey, 3+keylength);
		arcfour_encrypt(&mycontext, payload, payload,  length);

		/* calculate icv and compare the icv */
		*((u32 *)crc) = le32_to_cpu(getcrc32(payload, length-4));

		if (crc[3] != payload[length-1] || crc[2] != payload[length-2] || crc[1] != payload[length-3] || crc[0] != payload[length-4]) {
			RT_TRACE(_module_rtl871x_security_c_, _drv_err_, ("rtw_wep_decrypt:icv error crc[3](%x)!=payload[length-1](%x) || crc[2](%x)!=payload[length-2](%x) || crc[1](%x)!=payload[length-3](%x) || crc[0](%x)!=payload[length-4](%x)\n",
						crc[3], payload[length-1], crc[2], payload[length-2], crc[1], payload[length-3], crc[0], payload[length-4]));
		}

		WEP_SW_DEC_CNT_INC(psecuritypriv, prxattrib->ra);
	}
	return;
}