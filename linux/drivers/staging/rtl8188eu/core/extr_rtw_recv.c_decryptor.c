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
typedef  scalar_t__ u32 ;
struct security_priv {int dot11PrivacyKeyIndex; int dot118021XGrpKeyid; int hw_decrypted; int busetkipkey; } ;
struct rx_pkt_attrib {int bdecrypted; int encrypt; int hdrlen; int key_index; } ;
struct recv_frame {TYPE_1__* pkt; struct rx_pkt_attrib attrib; } ;
struct TYPE_4__ {int /*<<< orphan*/  free_recv_queue; } ;
struct adapter {TYPE_2__ recvpriv; struct security_priv securitypriv; } ;
struct TYPE_3__ {int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*,int) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int WEP_KEYS ; 
#define  _AES_ 131 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
#define  _TKIP_ 130 
#define  _WEP104_ 129 
#define  _WEP40_ 128 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 scalar_t__ rtw_aes_decrypt (struct adapter*,int*) ; 
 int /*<<< orphan*/  rtw_free_recvframe (struct recv_frame*,int /*<<< orphan*/ *) ; 
 scalar_t__ rtw_tkip_decrypt (struct adapter*,int*) ; 
 scalar_t__ rtw_wep_decrypt (struct adapter*,int*) ; 

__attribute__((used)) static struct recv_frame *decryptor(struct adapter *padapter,
				    struct recv_frame *precv_frame)
{
	struct rx_pkt_attrib *prxattrib = &precv_frame->attrib;
	struct security_priv *psecuritypriv = &padapter->securitypriv;
	struct recv_frame *return_packet = precv_frame;
	u32	 res = _SUCCESS;

	RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("prxstat->decrypted=%x prxattrib->encrypt=0x%03x\n", prxattrib->bdecrypted, prxattrib->encrypt));

	if (prxattrib->encrypt > 0) {
		u8 *iv = precv_frame->pkt->data + prxattrib->hdrlen;

		prxattrib->key_index = (((iv[3]) >> 6) & 0x3);

		if (prxattrib->key_index > WEP_KEYS) {
			DBG_88E("prxattrib->key_index(%d)>WEP_KEYS\n", prxattrib->key_index);

			switch (prxattrib->encrypt) {
			case _WEP40_:
			case _WEP104_:
				prxattrib->key_index = psecuritypriv->dot11PrivacyKeyIndex;
				break;
			case _TKIP_:
			case _AES_:
			default:
				prxattrib->key_index = psecuritypriv->dot118021XGrpKeyid;
				break;
			}
		}
	}

	if ((prxattrib->encrypt > 0) && (prxattrib->bdecrypted == 0)) {
		psecuritypriv->hw_decrypted = false;

		switch (prxattrib->encrypt) {
		case _WEP40_:
		case _WEP104_:
			res = rtw_wep_decrypt(padapter, (u8 *)precv_frame);
			break;
		case _TKIP_:
			res = rtw_tkip_decrypt(padapter, (u8 *)precv_frame);
			break;
		case _AES_:
			res = rtw_aes_decrypt(padapter, (u8 *)precv_frame);
			break;
		default:
			break;
		}
	} else if (prxattrib->bdecrypted == 1 && prxattrib->encrypt > 0 &&
		   (psecuritypriv->busetkipkey == 1 || prxattrib->encrypt != _TKIP_))
			psecuritypriv->hw_decrypted = true;

	if (res == _FAIL) {
		rtw_free_recvframe(return_packet, &padapter->recvpriv.free_recv_queue);
		return_packet = NULL;
	}

	return return_packet;
}