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
typedef  unsigned char u8 ;
typedef  size_t u32 ;
struct xmit_priv {size_t frag_len; } ;
struct pkt_attrib {scalar_t__ encrypt; size_t nr_frags; int hdrlen; int iv_len; size_t last_txcmdsz; size_t icv_len; } ;
struct xmit_frame {unsigned char* buf_addr; struct pkt_attrib attrib; } ;
struct security_priv {size_t PrivacyKeyIndex; size_t* DefKeylen; TYPE_1__* DefKey; } ;
struct arc4context {int dummy; } ;
struct _adapter {struct xmit_priv xmitpriv; struct security_priv securitypriv; } ;
typedef  int /*<<< orphan*/  addr_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {unsigned char* skey; } ;

/* Variables and functions */
 scalar_t__ RND4 (int /*<<< orphan*/ ) ; 
 int TXDESC_OFFSET ; 
 scalar_t__ _WEP104_ ; 
 scalar_t__ _WEP40_ ; 
 int /*<<< orphan*/  arcfour_encrypt (struct arc4context*,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  arcfour_init (struct arc4context*,unsigned char*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getcrc32 (unsigned char*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

void r8712_wep_encrypt(struct _adapter *padapter, u8 *pxmitframe)
{	/* exclude ICV */
	unsigned char	crc[4];
	struct arc4context  mycontext;
	u32 curfragnum, length, keylength, pki;
	u8 *pframe, *payload, *iv;    /*,*wepkey*/
	u8 wepkey[16];
	struct	pkt_attrib  *pattrib = &((struct xmit_frame *)
				       pxmitframe)->attrib;
	struct	security_priv *psecuritypriv = &padapter->securitypriv;
	struct	xmit_priv *pxmitpriv = &padapter->xmitpriv;

	if (((struct xmit_frame *)pxmitframe)->buf_addr == NULL)
		return;
	pframe = ((struct xmit_frame *)pxmitframe)->buf_addr + TXDESC_OFFSET;
	/*start to encrypt each fragment*/
	if ((pattrib->encrypt == _WEP40_) || (pattrib->encrypt == _WEP104_)) {
		pki = psecuritypriv->PrivacyKeyIndex;
		keylength = psecuritypriv->DefKeylen[pki];
		for (curfragnum = 0; curfragnum < pattrib->nr_frags;
		     curfragnum++) {
			iv = pframe + pattrib->hdrlen;
			memcpy(&wepkey[0], iv, 3);
			memcpy(&wepkey[3], &psecuritypriv->DefKey[
				psecuritypriv->PrivacyKeyIndex].skey[0],
				keylength);
			payload = pframe + pattrib->iv_len + pattrib->hdrlen;
			if ((curfragnum + 1) == pattrib->nr_frags) {
				length = pattrib->last_txcmdsz -
					pattrib->hdrlen -
					pattrib->iv_len -
					pattrib->icv_len;
				*((__le32 *)crc) = cpu_to_le32(getcrc32(
						payload, length));
				arcfour_init(&mycontext, wepkey, 3 + keylength);
				arcfour_encrypt(&mycontext, payload, payload,
						length);
				arcfour_encrypt(&mycontext, payload + length,
						crc, 4);
			} else {
				length = pxmitpriv->frag_len -
					 pattrib->hdrlen - pattrib->iv_len -
					 pattrib->icv_len;
				*((__le32 *)crc) = cpu_to_le32(getcrc32(
						payload, length));
				arcfour_init(&mycontext, wepkey, 3 + keylength);
				arcfour_encrypt(&mycontext, payload, payload,
						length);
				arcfour_encrypt(&mycontext, payload + length,
						crc, 4);
				pframe += pxmitpriv->frag_len;
				pframe = (u8 *)RND4((addr_t)(pframe));
			}
		}
	}
}